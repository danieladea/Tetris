#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include "Well.h"
#include "UserInterface.h"
#include <string>
#include <algorithm>
// [Add other #include directives as necessary.]

class Game
{
  public:
    Game(int width, int height);
    void play();
    bool playOneLevel();
    void displayPrompt(std::string s);
	void randomizePiece(Piecetype&  newPiece);
    void displayStatus(); 
	void displayNextPiece(string nextString);
	int getTime(int whatLevel);
    // [Add other members as necessary.]

  private:
    Well    m_well;
    Screen  m_screen;
    int     m_level;
    // [Add other members as necessary.]
};

#endif //GAME_INCLUDED
