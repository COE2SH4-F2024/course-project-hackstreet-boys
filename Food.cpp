#include "Food.h"

Food::Food(GameMechs* GM) 
{
    foodPosList = new objPosArrayList();
    myGM = GM;
}

Food::~Food()
{
    delete foodPosList;
}

Food::Food(const Food& other)
{
    foodPosList = new objPosArrayList(*other.foodPosList);
    myGM = other.myGM;
}

Food &Food::operator=(const Food &other)
{
    if (this != nullptr) 
    {
        delete foodPosList;
        foodPosList = new objPosArrayList(*other.foodPosList);
        myGM = other.myGM;
    }
    return *this;
}

void Food::generateFood(objPosArrayList* blockOff)
{
    srand(time(NULL));
    
    int i = 0, j = 0;
    int X,Y, xRange, yRange, specialFood;
    xRange = myGM->getBoardSizeX();
    yRange = myGM->getBoardSizeY();
    bool valid = true;
    int size = blockOff->getSize();

    specialFood = (rand() % 3);

    //generate random coordinates
    //iterate through each player semgment
    //check to see if generated coordinates intersect
    while(foodPosList->getSize()>0){
        foodPosList->removeTail();
    }
    
    for (int k = 0 ; k < 5; k++) {

        do
        {
            valid = true; //assume coordinates are valid until proven otherwise
            
            X = (rand() % (xRange-2)) + 1; //make the range each blank space then add 1 to align coordinates
            Y = (rand() % (yRange-2)) + 1; //make the range each blank space then add 1 to align coordinates
            objPos *tempPos = new objPos(X, Y, 0);

            for (i = 0; i < size; i++) // check with player location
            {
                if(blockOff->getElement(i).isPosEqual(tempPos)){
                    valid = false;
                    break;
                }
            }
            for (j = 0; j < foodPosList->getSize(); j++) // check with current food location
            {
                if(foodPosList->getElement(j).isPosEqual(tempPos)){
                    valid = false;
                    break;
                }
            }
            delete tempPos;

        } while (!valid);
            
        if (k < specialFood)
        {
            objPos *tempPos = new objPos(X,Y,'S');
            foodPosList->insertHead(*tempPos);
            delete tempPos;
        }
        else
        {
            objPos *tempPos = new objPos(X,Y,'o');
            foodPosList->insertHead(*tempPos);
            delete tempPos;
        }
    }
}


objPosArrayList* Food::getFoodPos() const
{
    return foodPosList;
}
