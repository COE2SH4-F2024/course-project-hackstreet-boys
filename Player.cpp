#include "Player.h"
#include "objPos.h"
#include "GameMechs.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    //playerPosList = 

    // more actions to be included
    playerPos.pos->x = mainGameMechsRef->getBoardSizeX()/2;
    playerPos.pos->y = mainGameMechsRef->getBoardSizeY()/2;
    playerPos.symbol = '@';

    //playerPosList->insertHead(headPos);
}


Player::~Player()
{
    // delete any heap members here
    //delete playerPosList;
}

objPos Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    return playerPos;
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
        break;
        case DOWN:
        playerPos.pos->y++;
        break;
        case LEFT:
        playerPos.pos->x--;
        break;
        case RIGHT:
        playerPos.pos->x++;
        break;
        default:
        break;
    }

    if (playerPos.pos->x < 1) {
            playerPos.pos->x = mainGameMechsRef->getBoardSizeX() - 2;
    }
    else if (playerPos.pos->x > mainGameMechsRef->getBoardSizeX() - 2) {
        playerPos.pos->x = 1;
    }
    else if (playerPos.pos->y < 1) {
        playerPos.pos->y = mainGameMechsRef->getBoardSizeY() - 2;
    }
    else if (playerPos.pos->y > mainGameMechsRef->getBoardSizeY() - 2) {
        playerPos.pos->y = 1;
    }

    
}

// More methods to be added