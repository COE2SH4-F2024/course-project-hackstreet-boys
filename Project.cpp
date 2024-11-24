#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"

using namespace std;

#define DELAY_CONST 100000

Player *myPlayer;
GameMechs *myGM;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(myGM->getExitFlagStatus() == false)  
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
    myGM = new GameMechs(); //exit flag is automatically set to false in this constructor
    myPlayer = new Player(myGM);

    
}

void GetInput(void)
{
    myGM->collectAsyncInput();
}

void RunLogic(void)
{
    if (myGM->getInput() == ' ') //key to exit program
    {
        myGM->setExitTrue();
    }

    else if (myGM->getInput() == 'p') //FOR DEBUGGING: test to see if score can be properly incremented 
    {
        myGM->incrementScore();
    }

    else if (myGM->getInput() == 'l') //FOR DEBUGGING: test to see if lose state works
    {
        myGM->setLoseFlag();
    }

    else
    {
        myPlayer-> updatePlayerDir();
    }
    myPlayer-> movePlayer();
    
    myGM->clearInput(); //reset the input so that it is not double processed
}

void DrawScreen(void)
{
    MacUILib_clearScreen();    
    objPos playerPos = myPlayer->getPlayerPos();
    //objPos foodPos = myGM->getFoodPos();
    
    int boardX = myGM->getBoardSizeX();
    int boardY = myGM->getBoardSizeY();
    if (myGM->getExitFlagStatus() == false)
    {
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
        //        else if(col == foodPos.pos->x &&  row == foodPos.pos->y) {
        //            MacUILib_printf("%c", foodPos.symbol);
        //        }
                else {
                    MacUILib_printf("%c", ' ');  // print a space character
                }
            }
            MacUILib_printf("\n");
        }

    //UI messages
    MacUILib_printf("Your current score is: %d.\n", myGM->getScore());
    //Debugging Messages
    MacUILib_printf("Player Position: (%d, %d), %c\n", playerPos.pos->x, playerPos.pos->y, playerPos.symbol);
    MacUILib_printf("DEBUGGING: Increment Score with 'p'.\n");
    MacUILib_printf("DEBUGGING: Trigger lose state with 'l'.\n");
    
    }

    else if (myGM->getLoseFlagStatus() == true)
    {
        MacUILib_clearScreen();
        MacUILib_printf("You lose! Your total score before losing was %d.\n", myGM->getScore());
    }
    
    else
    {
        MacUILib_clearScreen();
        MacUILib_printf("The game ended! Your total score is %d.\n", myGM->getScore());
    }


}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    delete myPlayer;
    delete myGM;

    MacUILib_uninit();
}
