#include "GameMechs.h"
#include "MacUILib.h"

GameMechs::GameMechs()
{
    
    input = 0;
    exitFlag = false;
    loseFlag = false;
    score = 0;

    boardSizeX = 20;
    boardSizeY = 10;

    food.setObjPos(5,5,'o');
    
}

GameMechs::GameMechs(int boardX, int boardY)
{
    
    input = 0;
    exitFlag = false;
    loseFlag = false;
    score = 0;

    boardSizeX = boardX;
    boardSizeY = boardY;

    food.setObjPos(5,5,'o');
}

// do you need a destructor?
GameMechs::~GameMechs()
{
    //no destruction needed
}

bool GameMechs::getExitFlagStatus() const
{
   return exitFlag;
}

bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag;
}
    

char GameMechs::getInput() const
{
    
    return input;

}

int GameMechs::getScore() const
{
    return score;
}

void GameMechs::incrementScore()
{
    score++;
}

int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}


void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;
    exitFlag = true; //game ends when you lose
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;
}

// More methods should be added here
void GameMechs::collectAsyncInput()
{
    if(MacUILib_hasChar()){
        input = MacUILib_getChar();
    }
}