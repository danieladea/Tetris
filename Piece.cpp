#include "Piece.h"
#include <cstdlib>
Piecetype::Piecetype()
	: orientation(0), whichPiece(9)
{
}

void Piecetype::setboundingBox(string s)
{
	int k = 0;
	for (int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			boundingBox[i][j] = s.at(k);
			k++;
		}
	}
}

void Piecetype::setCoordinate(int a, int b)
{
	m_x = a;
	m_y = b;
}

void Piecetype::moveUp()
{
	m_y--;
}

void Piecetype::moveDown()
{
	m_y++;
}

void Piecetype::moveLeft()
{
	m_x--;
}

void Piecetype::moveRight()
{
	m_x++;
}

int Piecetype::getX()
{
	return m_x;
}

int Piecetype::getY()
{
	return m_y;
}

void Piecetype::setWhichPiece(int x)
{
	whichPiece = x;
}


void Piecetype::changeOrientation()
{
	if (orientation < 3)
		orientation++;
	else
		orientation = 0;
}

int Piecetype::getOrientation()
{
	return orientation;
}

int Piecetype::getWhichPiece()
{
	return whichPiece;
}

string Piecetype::getCurrentPieceAndOrientation()
{
	return myPieces[whichPiece][orientation];
}

Piecetype::~Piecetype()
{
}
