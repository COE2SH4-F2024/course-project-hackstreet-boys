#include "Player.h"



Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    playerPosList = new objPosArrayList();
    // more actions to be included
    //myFood = thisFood;
    
    playerPos.pos->x = mainGameMechsRef->getBoardSizeX()/2;
    playerPos.pos->y = mainGameMechsRef->getBoardSizeY()/2;
    playerPos.symbol = '@';

    playerPosList->insertHead(playerPos);
}


Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}

objPos Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    return playerPosList->getHeadElement();
}

objPosArrayList* Player::getPlayerPosList() const    
{
    return playerPosList;
}

void Player::updatePlayerDir()
{
    
        // PPA3 input processing logic  
        char input = mainGameMechsRef->getInput();
        //use switch case
        switch(input)
        {                      
            case 'W':
            case 'w': 
                if (myDir != DOWN){
                    myDir = UP;
                }
                break;
            case 'A':
            case 'a': 
                if (myDir != RIGHT){
                    myDir = LEFT;
                }
                break;
            case 'S':
            case 's': 
                if (myDir != UP){
                    myDir = DOWN;
                }
                break;
            case 'D':
            case 'd': 
                if (myDir != LEFT){
                    myDir = RIGHT;
                }
                break;
            default:
                break;
        }

}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    switch (myDir)
    {
        case UP:
        playerPos.pos->y--;
        playerPosList->insertHead(playerPos);
        playerPosList->removeTail();
        break;
        case DOWN:
        playerPos.pos->y++;
        playerPosList->insertHead(playerPos);
        playerPosList->removeTail();
        break;
        case LEFT:
        playerPos.pos->x--;
        playerPosList->insertHead(playerPos);
        playerPosList->removeTail();
        break;
        case RIGHT:
        playerPos.pos->x++;
        playerPosList->insertHead(playerPos);
        playerPosList->removeTail();
        break;
        default:
        break;
    }

    if (playerPos.pos->x < 1) {
        playerPos.pos->x = mainGameMechsRef->getBoardSizeX() - 2;
        playerPosList->insertHead(playerPos);
        playerPosList->removeTail();
    }
    else if (playerPos.pos->x > mainGameMechsRef->getBoardSizeX() - 2) {
        playerPos.pos->x = 1;
        playerPosList->insertHead(playerPos);
        playerPosList->removeTail();
    }
    else if (playerPos.pos->y < 1) {
        playerPos.pos->y = mainGameMechsRef->getBoardSizeY() - 2;
        playerPosList->insertHead(playerPos);
        playerPosList->removeTail();
    }
    else if (playerPos.pos->y > mainGameMechsRef->getBoardSizeY() - 2) {
        playerPos.pos->y = 1;
        playerPosList->insertHead(playerPos);
        playerPosList->removeTail();
    }

    
}

// More methods to be added

bool Player::checkFoodConsumption(Food myFood)
{
    if(playerPosList->getHeadElement().pos->x == myFood.getFoodPos().pos->x)
    {
        if(playerPosList->getHeadElement().pos->y == myFood.getFoodPos().pos->y)
        {
            myFood.generateFood(*playerPosList, *mainGameMechsRef);
            return true;
        }   
    }
    return false;
}

void Player::incrementPlayerLength()
{
    mainGameMechsRef->incrementScore();
    playerPosList->insertTail(playerPosList->getTailElement());
}