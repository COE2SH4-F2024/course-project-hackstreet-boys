#include "Food.h"

Food::Food() //does NOT generate coordinates until generateFood is called
{
    foodPos.symbol = 'o'; 
}

Food::Food(GameMechs* GM) 
{
    foodPos.symbol = 'o';
    myGM = GM;
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
    if (this != nullptr) 
    {
    foodPos.symbol = other.foodPos.symbol;
    foodPos.pos->x = other.foodPos.pos->x;
    foodPos.pos->y = other.foodPos.pos->y;
    }
    return *this;
}

void Food::generateFood(objPosArrayList* blockOff)
{
    srand(time(NULL));
    
    int i = 0;
    int X,Y, xRange, yRange;
    xRange = myGM->getBoardSizeX();
    yRange = myGM->getBoardSizeY();
    bool valid = true;
    int size = blockOff->getSize();

    //generate random coordinates
    //iterate through each player semgment
    //check to see if generated coordinates intersect
    

    do
    {
        valid = true; //assume coordinates are valid until proven otherwise
        
        X = (rand() % (xRange-2)) + 1; //make the range each blank space then add 1 to align coordinates
        Y = (rand() % (yRange-2)) + 1; //make the range each blank space then add 1 to align coordinates


        for (i = 0; i < size; i++)
        {
            objPos *tempPos = new objPos(X, Y, 0);
            if(blockOff->getElement(i).isPosEqual(tempPos)){
                valid = false;
                break;
            }
            delete tempPos;
        }

    } while (!valid);
        
    foodPos.pos->x = X;
    foodPos.pos->y = Y;
}


objPos Food::getFoodPos() const
{
    return foodPos;
}
