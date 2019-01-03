#ifndef WELL_INCLUDED
#define WELL_INCLUDED
#include <vector>
#include<string>
using namespace std;
class Screen;
class Piecetype;

class Well
{
  public:
	Well();
	Well(int x, int y);
	void vaporBombExplode(Screen & screen, int wellWidth, int wellHeight, Piecetype & piece);
	void foamBombExplode(Screen & screen, int wellWidth, int wellHeight, Piecetype & piece);
	void foam(Screen & screen, int wellWidth, int wellHeight, int x_coordinate, int y_coordinate, int x0, int y0, string pieceString);
	void placeFoam(int x, int y, string s);
    void display(Screen& screen, int x, int y);
	void setWalls(int x, int y);
	void placePiece(int x, int y, string s);
	bool canMoveRight(int wellWidth, int wellHeight, Piecetype & piece);
	bool canMoveLeft(int wellWidth, int wellHeight, Piecetype & piece);
	void clearLine(Screen& screen, int wellWidth, int wellHeight);
	void clearWell(Screen& screen, int wellWidth, int wellHeight);
	void startPiece(Screen& screen, int x , int y, Piecetype& piece); //drops one
	void clearPreviousFalling(int x, int y); //want the dimensions
	void stringToBox(int boundingBoxSetter[4][4], string s);
	bool canPlacePiece(int x, int y, string s); //coordinates....
	bool canStartPiece(Screen& screen, int x, int y, Piecetype& piece);
	void moveAllDown(Screen& screen, int column, int wellHeight, int heightToStart);
	bool canMoveDown(int wellWidth, int wellHeight, Piecetype& piece);
	bool canRotate(int wellWidth, int wellHeight, Piecetype & piece);
	void moveToBottom(Screen & screen, int wellWidth, int wellHeight, Piecetype & piece);
	void moveDown(Screen& screen, int wellWidth, int wellHeight, Piecetype& piece);
	void moveRight(Screen& screen, int wellWidth, int wellHeight, Piecetype & piece);
	void rotate(Screen & screen, int wellWidth, int wellHeight, Piecetype & piece);
	void moveLeft(Screen& screen, int wellWidth, int wellHeight, Piecetype & piece);
	void makeMoney(int width, int height);
	void setRowsLeft(int rowstimeslevels);
	void decrementRowsLeft();
	int getRowsLeft();
	void addScore(int addThis);
	int getScore();
private:
	vector<vector<char> > myWell;
	int rowsLeft;
	int m_score; 
};

#endif // WELL_INCLUDED
