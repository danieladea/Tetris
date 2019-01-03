#include "Well.h"
#include "UserInterface.h"
#include "Piece.h"

Well::Well()
{
}

Well::Well(int x, int y)
	:myWell(x,vector<char> (y,' ')), rowsLeft(5), m_score(0)
{
	setWalls(x,y);
}

void Well::foamBombExplode(Screen& screen, int wellWidth, int wellHeight, Piecetype& piece)
{
	int x = piece.getX();
	int y = piece.getY();
	string s = piece.getCurrentPieceAndOrientation();
	foam(screen, wellWidth, wellHeight, x, y, x, y, s);
	
}

void Well::foam(Screen& screen, int wellWidth, int wellHeight, int x_coordinate, int y_coordinate, int x0, int y0, string pieceString) 
{	
	if (x_coordinate > x0 + 2 || x_coordinate < x0 - 2 || y_coordinate > y0 + 2 || y_coordinate < y0 - 2)
		return;

	if (canPlacePiece(x_coordinate, wellHeight - y_coordinate, pieceString))
	{
		placeFoam(x_coordinate, wellHeight - y_coordinate, pieceString);
		foam(screen, wellWidth, wellHeight, x_coordinate + 1, y_coordinate, x0, y0, pieceString);
		foam(screen, wellWidth, wellHeight, x_coordinate - 1, y_coordinate, x0, y0, pieceString);
		foam(screen, wellWidth, wellHeight, x_coordinate, y_coordinate + 1, x0, y0, pieceString);
		foam(screen, wellWidth, wellHeight, x_coordinate, y_coordinate - 1, x0, y0, pieceString);

	}
	else
		return;


}

void Well::placeFoam(int x, int y, string s)
{
	int boundingBox[4][4];
	stringToBox(boundingBox, s);

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (boundingBox[i][j] == 49) //equals char 1, so we want #
			{
				if (i + x < 0)
				{
				}
				else
					myWell[i + x][y - j - 1] = '*';
			}
			else     //don't need #
			{
			}
		}
	}
}

//bool Well::pathExists(char maze[5][5], int sr, int sc, int er, int ec)
//{
//	if()
//	if (sr == er && sc == ec)
//		return true;
//	maze[sr][sc] = '1';
//	if (maze[sr - 1][sc] == ' ' )
//	{
//		if (pathExists(maze, sr - 1, sc, er, ec))
//			return true;
//	}
//
//	if (maze[sr][sc - 1] == '.')
//	{
//		if (pathExists(maze, sr, sc - 1, er, ec))
//			return true;
//	}
//
//	if (maze[sr + 1][sc] == '.')
//	{
//		if (pathExists(maze, sr + 1, sc, er, ec))
//			return true;
//	}
//
//	if (maze[sr][sc + 1] == '.')
//	{
//		if (pathExists(maze, sr, sc + 1, er, ec))
//			return true;
//	}
//	return false;
//}

void Well::vaporBombExplode(Screen& screen, int wellWidth, int wellHeight, Piecetype& piece)
{
	//move piece down two and up two and place them all and then clear them
	piece.moveUp();
	piece.moveUp();
	for (int i = 0; i < 5; i++)
	{
		int x = piece.getX();
		int y = piece.getY();
		string s = piece.getCurrentPieceAndOrientation();
		if (piece.getY() < wellHeight - 1)
		{
			placePiece(x, wellHeight - y, s);
			piece.moveDown();
		}
	}
	clearPreviousFalling(wellWidth, wellHeight);
}

void Well::display(Screen& screen, int x, int y)
{
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			screen.gotoXY(i, j);
			char input = myWell[i][y-j-1];
			screen.printChar(input);
		}
	}
	screen.refresh();
}

void Well::setWalls(int x, int y)
{
	for (int i = 0; i < x; i++)
	{
		myWell[i][0] = '@';
	}
	for (int j = 0; j < y; j++)
	{
		myWell[0][j] = '@';
		myWell[x - 1][j] = '@';
	}
}

void Well::placePiece(int x, int y, string s) 
{
	int boundingBox[4][4];
	stringToBox(boundingBox, s);

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (boundingBox[i][j] == 49) //equals char 1, so we want #
			{
				if (i + x < 0)
				{}
				else
					myWell[i + x][y-j-1] = '#';  
			}
			else     //don't need #
			{
			}
		}
	}
}

bool Well::canMoveRight(int wellWidth, int wellHeight, Piecetype& piece) //x is the coordinate y is well y - y coord is what is passed in
{
	int x = piece.getX();
	int y = piece.getY();
	string s = piece.getCurrentPieceAndOrientation();
	if (canPlacePiece(x+1, wellHeight - y, s))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Well::canMoveLeft(int wellWidth, int wellHeight, Piecetype& piece) //x is the coordinate y is well y - y coord is what is passed in
{
	int x = piece.getX();
	int y = piece.getY();
	string s = piece.getCurrentPieceAndOrientation();
	if (canPlacePiece(x-1 , wellHeight - y, s))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Well::clearLine(Screen& screen, int wellWidth, int wellHeight)
{
	int timesScored = 0;
	for (int j = wellHeight; j>0; j--)
	{
		int k = 0;
		for (int i = 0; i < wellWidth; i++)
		{
			if (myWell[i][j] == '$' || myWell[i][j] == '*')
			{
				k++;
				if (k == wellWidth - 2)
				{
					timesScored++;
					decrementRowsLeft();
					for (int l = 1; l < wellWidth-1; l++)
					{
						myWell[l][j] = ' ';                  //clear line 
					}
					moveAllDown(screen, wellWidth, wellHeight, j); //move all from the line we cleared
				}
			}
		}
	}
	if (timesScored == 1)
		addScore(100);
	if (timesScored == 2)
		addScore(200);
	if (timesScored == 3)
		addScore(400);
	if (timesScored == 4)
		addScore(800);
	if (timesScored == 5)
		addScore(1600);		                                  
}

void Well::clearWell(Screen & screen, int wellWidth, int wellHeight)
{
	for (int i = 0; i < wellWidth; i++)
	{
		for (int j = 0; j < wellHeight; j++)
		{
			if (myWell[i][j] == '$')
			{
				myWell[i][j] = ' ';
			}
		}
	}
}

void Well::moveAllDown(Screen& screen, int wellWidth, int wellHeight,int heightToStart) //move everything above cleared line down
{
	for (int i = 1; i < wellWidth - 1; i++)
	{
		for (int j = heightToStart+1; j < wellHeight; j++)
		{
			myWell[i][j - 1] = myWell[i][j];
		}
	}
}

bool Well::canMoveDown(int wellWidth, int wellHeight, Piecetype& piece) //x is the coordinate y is well y - y coord is what is passed in
{
	int x = piece.getX();
	int y = piece.getY();
	string s = piece.getCurrentPieceAndOrientation();
	if (canPlacePiece(x, wellHeight-y - 1, s))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Well::canRotate(int wellWidth, int wellHeight, Piecetype& piece) //x is the coordinate y is well y - y coord is what is passed in
{
	int x = piece.getX();
	int y = piece.getY();
	piece.changeOrientation();
	string s = piece.getCurrentPieceAndOrientation();
	if (canPlacePiece(x, wellHeight - y, s))
	{
		piece.changeOrientation();
		piece.changeOrientation();
		piece.changeOrientation();
		return true;
	}
	else
	{
		piece.changeOrientation();
		piece.changeOrientation();
		piece.changeOrientation();
		return false;
	}
}

void Well::moveToBottom(Screen& screen, int wellWidth, int wellHeight, Piecetype& piece)
{
	while (canMoveDown(wellWidth, wellHeight, piece))
	{
		piece.moveDown();
		clearPreviousFalling(wellWidth, wellHeight);
		int x = piece.getX();
		int y = piece.getY();
		string s = piece.getCurrentPieceAndOrientation();
		placePiece(x, wellHeight - y, s);
		display(screen, wellWidth, wellHeight);
		screen.refresh();
	}
}

void Well::moveDown(Screen& screen, int wellWidth, int wellHeight, Piecetype& piece)
{

	piece.moveDown();
	clearPreviousFalling(wellWidth, wellHeight);
	int x = piece.getX();
	int y = piece.getY();
	string s = piece.getCurrentPieceAndOrientation();
	placePiece(x, wellHeight - y, s);
	display(screen, wellWidth, wellHeight);
	screen.refresh();
}

void Well::moveRight(Screen& screen, int wellWidth, int wellHeight, Piecetype& piece)
{
	piece.moveRight();
	clearPreviousFalling(wellWidth, wellHeight);
	int x = piece.getX();
	int y = piece.getY();
	string s = piece.getCurrentPieceAndOrientation();
	placePiece(x, wellHeight - y, s);
	display(screen, wellWidth, wellHeight);
	screen.refresh();
}

void Well::rotate(Screen& screen, int wellWidth, int wellHeight, Piecetype& piece)
{
	piece.changeOrientation();
	clearPreviousFalling(wellWidth, wellHeight);
	int x = piece.getX();
	int y = piece.getY();
	string s = piece.getCurrentPieceAndOrientation();
	placePiece(x, wellHeight - y, s);
	display(screen, wellWidth, wellHeight);
	screen.refresh();
}


void Well::moveLeft(Screen& screen, int wellWidth, int wellHeight, Piecetype& piece)
{
	piece.moveLeft();
	clearPreviousFalling(wellWidth, wellHeight);
	int x = piece.getX();
	int y = piece.getY();
	string s = piece.getCurrentPieceAndOrientation();
	placePiece(x, wellHeight - y, s);
	display(screen, wellWidth, wellHeight);
	screen.refresh();

}


bool Well::canPlacePiece(int x, int y, string s) //x  is the coordinate well y - ycoordinate is what is passed in
{
	bool canPlace = true;
	int boundingBox[4][4];
	stringToBox(boundingBox, s);

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (boundingBox[i][j] == 49) //equals char 1, so we want #
			{
				if (i + x < 0)
				{}
				else
				{
					if (myWell[i + x][y - j - 1] == '$' || myWell[i + x][y - j - 1] == '@' || myWell[i + x][y - j - 1] == '*')
					{
						canPlace = false;
						goto fail;
					}
				}
			}
		}
	}
fail: return canPlace;
}

bool Well::canStartPiece(Screen& screen, int x, int y, Piecetype& piece)
{
	bool canStart = true;
	piece.setCoordinate(4, 0);
	if (canPlacePiece(piece.getX(), y - piece.getY(), piece.getCurrentPieceAndOrientation()))
	{}
	else
	{
		canStart = false;
	}
	return canStart;
}




void Well::startPiece(Screen& screen, int x, int y, Piecetype& piece) //where x and y are size of well
{
	piece.setCoordinate(4,0);
	placePiece(piece.getX(), y - piece.getY(), piece.getCurrentPieceAndOrientation());
	display(screen, x, y);
}

void Well::clearPreviousFalling(int x, int y)
{
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			if (myWell[i][j] == '#')
			{
				myWell[i][j] = ' ';
			}
		}
	}
}


void Well::stringToBox(int boundingBoxSetter[4][4], string s)
{
	int k = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			boundingBoxSetter[i][j] = s.at(k);
			k++;
		}
	}
}


void Well::makeMoney(int width, int height)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (myWell[i][j] == '#')
			{
				myWell[i][j] = '$';
			}
		}
	}
}

void Well::setRowsLeft(int rowstimeslevels)
{
	rowsLeft = rowstimeslevels;
}

void Well::decrementRowsLeft()
{
	rowsLeft--;
}

int Well::getRowsLeft()
{
	return rowsLeft;
}

void Well::addScore(int addThis)
{
	m_score += addThis;
}

int Well::getScore()
{
	return m_score;
}

