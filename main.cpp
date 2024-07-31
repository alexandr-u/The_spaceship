#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "windows.h"

#include "Spaceship.h"
#include "GameSpaceship.h"

int Spaceship::location = 0;

int main()
{
    Game game;
    game.run();
    return 0;
}