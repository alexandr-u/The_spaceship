#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "windows.h"
#include "GameSpaseship.h"

int Spaceship::location = 0;

int main()
{
    srand(time(0)); //rand()

    Game game;
    game.run();
    return 0;
}