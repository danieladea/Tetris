#include "Game.h"
#include "Well.h"
#include "UserInterface.h"
#include <string>
#include "Piece.h"

using namespace std;

const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 25;

const int WELL_X = 12;
const int WELL_Y = 18;

const int PROMPT_Y = 20;
const int PROMPT_X = 0;

const int SCORE_X = 16;
const int SCORE_Y = 8;

const int ROWS_LEFT_X = 16;
const int ROWS_LEFT_Y = 9;

const int LEVEL_X = 16;
const int LEVEL_Y = 10;

const int NEXT_PIECE_TITLE_X = 16;
const int NEXT_PIECE_TITLE_Y = 3;

const int NEXT_PIECE_X = 16;
const int NEXT_PIECE_Y = 4;



Game::Game(int width, int height)
 : m_screen(SCREEN_WIDTH, SCREEN_HEIGHT), m_level(1), m_well(width+2,height+1)
{
}

void Game::play()
{
	
    m_well.display(m_screen, WELL_X, WELL_Y);
	m_well.setRowsLeft(m_level*5);
    displayStatus();  //  score, rows left, level
    displayPrompt("Press the Enter key to begin playing Chetyris!");
    waitForEnter();  // [in UserInterface.h]
	string blank = "";
	displayPrompt(blank);
    for(;;)
    {
		if (!playOneLevel())
		{
			break;
		}
        displayPrompt("Good job!  Press the Enter key to start next level!");
        waitForEnter();
		m_well.clearWell(m_screen, WELL_X, WELL_Y);
        m_level++;
		m_well.setRowsLeft(m_level*5);
    }
    displayPrompt("Game Over!  Press the Enter key to exit!");
    waitForEnter();
}

void Game::displayPrompt(std::string s)     
{
    m_screen.gotoXY(PROMPT_X, PROMPT_Y);
    m_screen.printStringClearLine(s);   // overwrites previous text
    m_screen.refresh();
}

void Game::randomizePiece(Piecetype& newPiece)
{
	int i = chooseRandomPieceType();
	switch (i)
	{
	case PIECE_I:
		newPiece.setWhichPiece(1);
		break;
	case PIECE_L:
		newPiece.setWhichPiece(3);
		break;
	case PIECE_J:
		newPiece.setWhichPiece(4);
		break;
	case PIECE_T:
		newPiece.setWhichPiece(2);
		break;
	case PIECE_O:
		newPiece.setWhichPiece(0);
		break;
	case PIECE_S:
		newPiece.setWhichPiece(5);
		break;
	case PIECE_Z:
		newPiece.setWhichPiece(6);
		break;
	case PIECE_VAPOR:
		newPiece.setWhichPiece(7);
		break;
	case PIECE_FOAM:
		newPiece.setWhichPiece(8);
		break;
	case PIECE_CRAZY:
		newPiece.setWhichPiece(9);
		break;
	case NUM_PIECE_TYPES:
		newPiece.setWhichPiece(5);
		break;
	default:
		newPiece.setWhichPiece(0);
		break;
	}
}

void Game::displayStatus()
{
	m_screen.gotoXY(NEXT_PIECE_TITLE_X, NEXT_PIECE_TITLE_Y);
	m_screen.printString("Next piece:");

	//put next piece here
	m_screen.gotoXY(SCORE_X, SCORE_Y);
	m_screen.printString("Score: ");

	m_screen.gotoXY(14 + SCORE_X, SCORE_Y);
	m_screen.printString(" " + to_string(m_well.getScore()));

	m_screen.gotoXY(ROWS_LEFT_X, ROWS_LEFT_Y);
	m_screen.printString("Rows Left: ");

	m_screen.gotoXY(14 + ROWS_LEFT_X, ROWS_LEFT_Y);
	m_screen.printString(" " + to_string(m_well.getRowsLeft()));

	m_screen.gotoXY(LEVEL_X, LEVEL_Y);
	m_screen.printString("Level:     " );

	m_screen.gotoXY(14+ LEVEL_X, LEVEL_Y);
	m_screen.printString(" " + to_string(m_level));
	m_screen.refresh();
}

void Game::displayNextPiece(string nextString)
{
	int k = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (nextString.at(k)==48)
			{
				m_screen.gotoXY(i + NEXT_PIECE_X, j + NEXT_PIECE_Y);
				m_screen.printChar(' ');
				k++; 
			}
			else
			{
				m_screen.gotoXY(i + NEXT_PIECE_X, j + NEXT_PIECE_Y);
				m_screen.printChar('#');
				k++;
			}
		}
	}
}

int Game::getTime(int whatLevel)
{
	return max(1000 - 100 * (whatLevel - 1), 100);
}



bool Game::playOneLevel()
{
	displayStatus();
	Piecetype currentPiece;
	randomizePiece(currentPiece);
	Piecetype nextPiece;
	randomizePiece(nextPiece);
	displayNextPiece(nextPiece.getCurrentPieceAndOrientation());
	
	while(m_well.canStartPiece(m_screen, WELL_X, WELL_Y, currentPiece))
	{
		m_well.startPiece(m_screen, WELL_X, WELL_Y, currentPiece);
		m_well.display(m_screen, WELL_X, WELL_Y);
		while (m_well.canMoveDown(WELL_X, WELL_Y, currentPiece))
		{
			//oneUserMove()
			//oneUserMove(m_screen, WELL_X, WELL_Y, currentPiece);

			Timer T;
			while (T.elapsed() < getTime(m_level))
			{
				char userinput;
				if (getCharIfAny(userinput))
				{
					switch (userinput)
					{
					case ARROW_RIGHT:
						if (currentPiece.getWhichPiece() == 9)
						{
							if (m_well.canMoveLeft(WELL_X, WELL_Y, currentPiece))
								m_well.moveLeft(m_screen, WELL_X, WELL_Y, currentPiece);
						}
						else
						{
							if (m_well.canMoveRight(WELL_X, WELL_Y, currentPiece))
								m_well.moveRight(m_screen, WELL_X, WELL_Y, currentPiece);
						}
						break;
					case ARROW_DOWN:
						if (m_well.canMoveDown(WELL_X, WELL_Y, currentPiece))
							m_well.moveDown(m_screen, WELL_X, WELL_Y, currentPiece);
						if (!m_well.canMoveDown(WELL_X, WELL_Y, currentPiece))
							goto pushedToBottom;
						break;
					case ARROW_LEFT:
						if (currentPiece.getWhichPiece() == 9)
						{
							if (m_well.canMoveRight(WELL_X, WELL_Y, currentPiece))
								m_well.moveRight(m_screen, WELL_X, WELL_Y, currentPiece);
						}
						else
						{
							if (m_well.canMoveLeft(WELL_X, WELL_Y, currentPiece))
								m_well.moveLeft(m_screen, WELL_X, WELL_Y, currentPiece);
						}
						break;
					case ARROW_UP:
						if (m_well.canRotate(WELL_X, WELL_Y, currentPiece))
							m_well.rotate(m_screen, WELL_X, WELL_Y, currentPiece);
						break;
					case 32:
						m_well.moveToBottom(m_screen, WELL_X, WELL_Y, currentPiece);
						goto pushedDown;
						break;
					default:
						break;
					}
				}
			}
		pushedToBottom:;
			if (m_well.canMoveDown(WELL_X, WELL_Y, currentPiece))
			{
				m_well.moveDown(m_screen, WELL_X, WELL_Y, currentPiece);
			}
	
				T.start();
				while (T.elapsed() < getTime(m_level) && !m_well.canMoveDown(WELL_X, WELL_Y, currentPiece))
				{
					char userinput;
					if (getCharIfAny(userinput))
					{
						switch (userinput)
						{
						case ARROW_RIGHT:
							if (currentPiece.getWhichPiece() == 9)
							{
								if (m_well.canMoveLeft(WELL_X, WELL_Y, currentPiece))
									m_well.moveLeft(m_screen, WELL_X, WELL_Y, currentPiece);
							}
							else
							{
								if (m_well.canMoveRight(WELL_X, WELL_Y, currentPiece))
									m_well.moveRight(m_screen, WELL_X, WELL_Y, currentPiece);
							}
							break;
						case ARROW_DOWN:
							if (m_well.canMoveDown(WELL_X, WELL_Y, currentPiece))
								m_well.moveDown(m_screen, WELL_X, WELL_Y, currentPiece);
							if (!m_well.canMoveDown(WELL_X, WELL_Y, currentPiece))
								goto pushedDown;
							break;
						case ARROW_LEFT:
							if (currentPiece.getWhichPiece() == 9)
							{
								if (m_well.canMoveRight(WELL_X, WELL_Y, currentPiece))
									m_well.moveRight(m_screen, WELL_X, WELL_Y, currentPiece);
							}
							else
							{
								if (m_well.canMoveLeft(WELL_X, WELL_Y, currentPiece))
									m_well.moveLeft(m_screen, WELL_X, WELL_Y, currentPiece);
							}
							break;
						case ARROW_UP:
							if (m_well.canRotate(WELL_X, WELL_Y, currentPiece))
								m_well.rotate(m_screen, WELL_X, WELL_Y, currentPiece);
							break;
						case 32:
							m_well.moveToBottom(m_screen, WELL_X, WELL_Y, currentPiece);
							goto pushedDown;
							break;
						case 'q':
						case 'Q':
							return false;
						default:
							break;
						}
					}
				}
			pushedDown:;
			
			m_well.display(m_screen, WELL_X, WELL_Y);
		}

		if (currentPiece.getWhichPiece() == 7 && !m_well.canMoveDown(WELL_X, WELL_Y, currentPiece))
		{
			m_well.display(m_screen, WELL_X, WELL_Y);
			m_well.vaporBombExplode(m_screen, WELL_X, WELL_Y, currentPiece);
		}
		if (currentPiece.getWhichPiece() == 8 && !m_well.canMoveDown(WELL_X, WELL_Y, currentPiece))
		{
			m_well.display(m_screen, WELL_X, WELL_Y);
			m_well.foamBombExplode(m_screen, WELL_X, WELL_Y, currentPiece);
		}

		m_well.makeMoney(WELL_X, WELL_Y);
		m_well.clearLine(m_screen, WELL_X, WELL_Y);
		if (m_well.getRowsLeft() == 0)
		{
			m_well.setRowsLeft(0);
		}
		m_well.display(m_screen, WELL_X, WELL_Y);
		displayStatus();
		if (m_well.getRowsLeft() == 0)
			return true;
		currentPiece = nextPiece;
		randomizePiece(nextPiece);
		displayNextPiece(nextPiece.getCurrentPieceAndOrientation());
	}
	m_well.display(m_screen, WELL_X, WELL_Y);
	m_well.display(m_screen, WELL_X, WELL_Y);
	m_screen.refresh();
    return false;  // [Replace this with the code to play a level.]
}



