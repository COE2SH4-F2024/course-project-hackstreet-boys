#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h" //implicitly calls #include "Food.h"

using namespace std;

#define DELAY_CONST 100000

Player *myPlayer;
GameMechs *myGM;
Food *myFood;
objPosArrayList *playerPos;

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
    myFood = new Food(myGM);
    myPlayer = new Player(myGM, myFood);
    playerPos = myPlayer->getPlayerPosList();
    myFood->generateFood(playerPos);
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
        
        myPlayer->incrementPlayerLength();
    }

    else if (myGM->getInput() == 'l') //FOR DEBUGGING: test to see if lose state works
    {
        myGM->setLoseFlag();
    }

    else if (myGM->getInput() == 'f') //FOR DEBUGGING: test food generation
    {
        myFood->generateFood(playerPos);
    }

    else
    {
        myPlayer-> updatePlayerDir();
    }

    if(myPlayer->checkFoodConsumption())
    {
        myFood->generateFood(playerPos);
        //myPlayer->incrementPlayerLength();
    }

    myPlayer-> movePlayer();
    
    myGM->clearInput(); //reset the input so that it is not double processed
}

void DrawScreen(void)
{
    MacUILib_clearScreen();
    objPosArrayList *foodPos = myFood->getFoodPos();
    bool playerFound = false, foodFound = false;
    int elementCount = 0;
    
    
    int boardX = myGM->getBoardSizeX();
    int boardY = myGM->getBoardSizeY();
    if (myGM->getExitFlagStatus() == false)
    {
        for (int row = 0; row < boardY; row++)
        {
            for (int col = 0; col < boardX; col++)
            {
                playerFound = false;
                foodFound = false;
                for(int i = 0 ; i < playerPos->getSize() ; i++)
                {
                    objPos *tempPos = new objPos(col, row, 0);
                    if(playerPos->getElement(i).isPosEqual(tempPos)){
                        playerFound = true;
                    }
                    delete tempPos;
                }
                for(int i = 0 ; i < foodPos->getSize() ; i++)
                {
                    objPos *tempPos = new objPos(col, row, 0);
                    if(foodPos->getElement(i).isPosEqual(tempPos)){
                        foodFound = true;
                    }
                    delete tempPos;
                }
                if (row == 0 || row == boardY-1 || col == 0 || col ==  boardX-1)   {
                    MacUILib_printf("%c", '#');  // print a border character
                }
                else if(playerFound) {
                    MacUILib_printf("%c", playerPos->getHeadElement().getSymbol());
                }
                else if(foodFound) {
                    MacUILib_printf("%c", foodPos->getElement(elementCount).getSymbol());
                    elementCount++;
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
    MacUILib_printf("Player Position: (%d, %d), %c\n", playerPos->getHeadElement().pos->x, playerPos->getHeadElement().pos->y, playerPos->getHeadElement().getSymbol());
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
