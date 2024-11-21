#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"

using namespace std;

#define DELAY_CONST 100000

Player *myPlayer;
GameMechs *myGM;
bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(exitFlag == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();
    myGM = new GameMechs();
    myPlayer = new Player(myGM);

    exitFlag = false;
}

void GetInput(void)
{
    myPlayer-> updatePlayerDir();
}

void RunLogic(void)
{
    myPlayer-> movePlayer();
    exitFlag = myGM->getExitFlagStatus();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();    
    objPos playerPos = myPlayer->getPlayerPos();
    
    int boardX = myGM->getBoardSizeX();
    int boardY = myGM->getBoardSizeY();

    for (int row = 0; row < boardY; row++)
    {
        for (int col = 0; col < boardX; col++)
        {
            if (row == 0 || row == boardY-1 || col == 0 || col ==  boardX-1)   {
                MacUILib_printf("%c", '#');  // print a border character
            }
            else if(col == playerPos.pos->x &&  row == playerPos.pos->y) {
                MacUILib_printf("%c", playerPos.symbol);
            }
            else {
                MacUILib_printf("%c", ' ');  // print a space character
            }
        }
        MacUILib_printf("\n");
    }
    MacUILib_printf("Player Position: (%d, %d), %c", playerPos.pos->x, playerPos.pos->y, playerPos.symbol);
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    delete myPlayer;
    delete myGM;
    MacUILib_clearScreen();    

    MacUILib_uninit();
}
