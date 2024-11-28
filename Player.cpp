#include "Player.h"



Player::Player(GameMechs* thisGMRef, Food* thisFood)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    playerPosList = new objPosArrayList();
    // more actions to be included
    myFood = thisFood;

    objPos *headPos = new objPos(mainGameMechsRef->getBoardSizeX()/2, mainGameMechsRef->getBoardSizeY()/2, '@');

    playerPosList->insertHead(*headPos);

    delete headPos;
}


Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}

Player::Player(const Player& other) //copy constructor
{
    mainGameMechsRef = other.mainGameMechsRef;
    myDir = other.myDir;
    playerPosList = other.playerPosList;
    myFood = other.myFood;
}
Player &Player::operator=(const Player& other) //assignment constructor
{
    if (this != nullptr) {
        mainGameMechsRef = other.mainGameMechsRef;
        myDir = other.myDir;
        playerPosList = other.playerPosList;
        myFood = other.myFood;
    }
    return *this;
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
    objPos headPos = playerPosList->getHeadElement();
    switch (myDir)
    {
        case UP:
        headPos.pos->y--;
        playerPosList->insertHead(headPos);
        playerPosList->removeTail();
        break;
        case DOWN:
        headPos.pos->y++;
        playerPosList->insertHead(headPos);
        playerPosList->removeTail();
        break;
        case LEFT:
        headPos.pos->x--;
        playerPosList->insertHead(headPos);
        playerPosList->removeTail();
        break;
        case RIGHT:
        headPos.pos->x++;
        playerPosList->insertHead(headPos);
        playerPosList->removeTail();
        break;
        default:
        break;
    }

    if (headPos.pos->x < 1) {
        headPos.pos->x = mainGameMechsRef->getBoardSizeX() - 2;
        playerPosList->insertHead(headPos);
        playerPosList->removeTail();
    }
    else if (headPos.pos->x > mainGameMechsRef->getBoardSizeX() - 2) {
        headPos.pos->x = 1;
        playerPosList->insertHead(headPos);
        playerPosList->removeTail();
    }
    else if (headPos.pos->y < 1) {
        headPos.pos->y = mainGameMechsRef->getBoardSizeY() - 2;
        playerPosList->insertHead(headPos);
        playerPosList->removeTail();
    }
    else if (headPos.pos->y > mainGameMechsRef->getBoardSizeY() - 2) {
        headPos.pos->y = 1;
        playerPosList->insertHead(headPos);
        playerPosList->removeTail();
    }

    if (checkSelfCollision())
    {
        mainGameMechsRef->setLoseFlag(); //cause losing
    }

    
}

// More methods to be added

bool Player::checkFoodConsumption()
{
    objPos tempPos = myFood->getFoodPos();
    if(playerPosList->getHeadElement().isPosEqual(&tempPos))
    {
        myFood->generateFood(playerPosList);
        return true;
    }
    return false;
}

void Player::incrementPlayerLength()
{
    mainGameMechsRef->incrementScore();
    playerPosList->insertTail(playerPosList->getTailElement());
}

bool Player::checkSelfCollision()
{
    int i = 0; 
    for (i = 1 ; i < playerPosList->getSize(); i++) //set to 1 so the head does not collide with itself
    {
        objPos tempPos = playerPosList->getElement(i);
        if (playerPosList->getHeadElement().isPosEqual(&tempPos))
        {
                return true;
        }
    }

    return false;
}