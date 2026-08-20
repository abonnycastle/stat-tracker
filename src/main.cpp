#include <iostream>
#include "../include/GameStats.h"

int main() {
    GameStats game;

    game.kills = 10;
    game.deaths = 3;
    game.assists = 7;

    std::cout << "Kills: " << game.kills << std::endl;
    std::cout << "Deaths: " << game.deaths << std::endl;
    std::cout << "Assists: " << game.assists << std::endl;

    return 0;
}