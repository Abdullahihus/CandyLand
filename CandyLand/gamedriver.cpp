#include "Game.h"
#include <iostream> 
#include <cstdlib> 
#include <ctime>
using namespace std; 

int main()
{
    srand(time(0)); 
    Game candylandGame;

    candylandGame.startGame();

    return 0;
}
