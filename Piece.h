#ifndef PIECE_INCLUDED
#define PIECE_INCLUDED
#include<string>
#include<vector>
using namespace std; 

class Piecetype  
{
public:
	Piecetype();
	//setting placeboard
	//pass in a string and mutate into an array
	void setboundingBox(string s);
	int boundingBox[4][4]; //holds locations of #s
	void setCoordinate(int a, int b); 
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	int getX();
	int getY();
	void setWhichPiece(int x);
	void changeOrientation();
	string myPieces[10][4] = { { "1100110000000000", "1100110000000000",  "1100110000000000",  "1100110000000000" }, //o
	{ "0100010001000100", "0000111100000000",  "0100010001000100",  "0000111100000000" },//i
	{ "0100110001000000", "0000111001000000",  "0100011001000000",  "0100111000000000" }, //t
	{ "0110010001000000", "0000100011100000",  "0010001001100000",  "0000011100010000" }, //l
	{ "0000010001000110", "0000000101110000",  "0000011000100010",  "0000111010000000" }, //j
	{ "0010011001000000", "0000110001100000",  "0010011001000000",  "0000110001100000" }, //s
	{ "0100011000100000", "0000011011000000",  "0100011000100000",  "0000011011000000" }, //z
	{ "0000100010000000", "0000100010000000",  "0000100010000000",  "0000100010000000" }, //vapor
	{ "0000010000000000", "0000010000000000",  "0000010000000000",  "0000010000000000" }, //foam
	{ "1000010001001000", "0000000001101001",  "0001001000100001",  "1001011000000000" } }; //crazy
	int getOrientation();
	int getWhichPiece();
	string getCurrentPieceAndOrientation();
	//string orientation0 = "1100110000000000";
	~Piecetype();

private:
	int orientation = 4;
	int whichPiece;
	int m_x;  //coordinates on my board of the top left corner
	int m_y;
	string currentPieceAndOrientation = myPieces[getOrientation()][getWhichPiece()];
};


enum PieceType {
    PIECE_I, PIECE_L, PIECE_J, PIECE_T, PIECE_O, PIECE_S, PIECE_Z,
    PIECE_VAPOR, PIECE_FOAM, PIECE_CRAZY, NUM_PIECE_TYPES
};



PieceType chooseRandomPieceType();

#endif //PIECE_INCLUDED
