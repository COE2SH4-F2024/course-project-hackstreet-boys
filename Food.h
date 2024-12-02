#include <cstdlib>
#include <time.h>
#include "objPos.h"
#include "GameMechs.h"
//might need #include "MacUILib.h"

using namespace std;

class Food
{
    private:
        //objPos foodPos;
        objPosArrayList* foodBucket;
        GameMechs* myGM;
        

    public:
        Food();
        Food(GameMechs* GM);
        ~Food();
        Food(const Food& other); //copy constructor
        Food& operator=(const Food& other); //assignment constructor

        void generateFood(objPosArrayList* playerPos);
        objPosArrayList* getFoodPos() const;



};