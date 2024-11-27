#include <cstdlib>
#include <time.h>
#include "objPos.h"
#include "GameMechs.h"
//might need #include "MacUILib.h"

using namespace std;

class Food
{
    private:
        objPos foodPos;

    public:
        Food();
        ~Food();
        Food(const Food& other); //copy constructor
        Food& operator=(const Food& other); //assignment constructor

        void generateFood(objPosArrayList blockOff, GameMechs myGM);
        objPos getFoodPos() const;



};