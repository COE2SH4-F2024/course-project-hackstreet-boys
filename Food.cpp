#include "Food.h"

Food::Food() //does NOT generate coordinates until generateFood is called
{
    foodPos.symbol = 'o'; 
}

Food::~Food()
{
    //nothing on heap
}

Food::Food(const Food& other)
{
    foodPos.symbol = other.foodPos.symbol;
    foodPos.pos->x = other.foodPos.pos->x;
    foodPos.pos->y = other.foodPos.pos->y;
}

Food &Food::operator=(const Food &other)
{
    foodPos.symbol = other.foodPos.symbol;
    foodPos.pos->x = other.foodPos.pos->x;
    foodPos.pos->y = other.foodPos.pos->y;
    return *this;
}

void Food::generateFood(objPos blockOff, GameMechs myGM)
{
    srand(time(NULL));

    do
    {
        int X,Y, xRange, yRange;
        xRange = myGM.getBoardSizeX();
        yRange = myGM.getBoardSizeY();

        X = (rand() % (xRange-2)) + 1; //make the range each blank space then add 1 to align coordinates
        Y = (rand() % (yRange-2)) + 1; //make the range each blank space then add 1 to align coordinates

        foodPos.pos->x = X;
        foodPos.pos->y = Y;
    } while (foodPos.isPosEqual(&blockOff));
    
}

objPos Food::getFoodPos() const
{
    return foodPos;
}
