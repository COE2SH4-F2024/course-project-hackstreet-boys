#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 100000

Player *myPlayer;
GameMechs *myGM;
Food *myFood;
//objPosArrayList* playerPos;

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
    myFood = new Food();
    myFood->generateFood(myPlayer->getPlayerPos(), *myGM);
    //playerPos = myPlayer->getPlayerPosList();

    
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
        //playerPos->insertTail(playerPos->getTailElement());
    }

    else if (myGM->getInput() == 'l') //FOR DEBUGGING: test to see if lose state works
    {
        myGM->setLoseFlag();
    }

    else if (myGM->getInput() == 'f') //FOR DEBUGGING: test food generation
    {
        myFood->generateFood(myPlayer->getPlayerPos(), *myGM);
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
    //objPos playerPos = myPlayer->getPlayerPos();
    objPosArrayList* playerPos = myPlayer->getPlayerPosList();
    objPos* playerLoc = new objPos[playerPos->getSize()];
    for(int i = 0 ; i < playerPos->getSize() ; i++)
    {
        playerLoc[i] = playerPos->getElement(i);

    }
    bool found = false;
    //objPos foodPos = myGM->getFoodPos();
    
    int boardX = myGM->getBoardSizeX();
    int boardY = myGM->getBoardSizeY();
    if (myGM->getExitFlagStatus() == false)
    {
        for (int row = 0; row < boardY; row++)
        {
            for (int col = 0; col < boardX; col++)
            {
                found = false;
                for(int i = 0 ; i < playerPos->getSize() ; i++)
                {
                    if(col == playerLoc[i].pos->x &&  row == playerLoc[i].pos->y){
                        found = true;
                    }

                }
                if (row == 0 || row == boardY-1 || col == 0 || col ==  boardX-1)   {
                    MacUILib_printf("%c", '#');  // print a border character
                }
                else if(found) {
                    MacUILib_printf("%c", playerLoc[0].symbol);
                }
                else if(col == myFood->getFoodPos().pos->x &&  row == myFood->getFoodPos().pos->y) {
                    MacUILib_printf("%c", myFood->getFoodPos().getSymbol());
                }
                
                else {
                    MacUILib_printf("%c", ' ');  // print a space character
                }
            }
            MacUILib_printf("\n");
        }

    //UI messages
    MacUILib_printf("Your current score is: %d.\n", myGM->getScore());
    //Debugging Messages
    MacUILib_printf("Player Position: (%d, %d), %c\n", playerLoc[0].pos->x, playerLoc[0].pos->y, playerLoc[0].symbol);
    MacUILib_printf("DEBUGGING: Increment Score with 'p'.\n");
    MacUILib_printf("DEBUGGING: Trigger lose state with 'l'.\n");
    MacUILib_printf("DEBUGGING: Generate new food with 'f'.\n");
    
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
    delete myFood;

    MacUILib_uninit();
}
