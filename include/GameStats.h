#pragma once
#include <string>
#include <vector>

struct GameStats {
    std::string championName;
    int kills;
    int deaths;
    int assists;
    std::string item0;
    std::string item1;
    std::string item2;
    std::string item3;
    std::string item4;
    std::string item5;
    std::string item6;

    void displayStats(){
        std::cout << "\nYour stats:\n";
        std::cout << "\nChampion: " << championName;
        std::cout << "\nKills: " << kills; 
        std::cout << "\nDeaths: " << deaths;
        std::cout << "\nAssists: " << assists;
        std::cout << "\n\nItems:\n";
        std::cout << "\nItem 1: " << item0;
        std::cout << "\nItem 2: " << item1;
        std::cout << "\nItem 3: " << item2;
        std::cout << "\nItem 4: " << item3;
        std::cout << "\nItem 5: " << item4;
        std::cout << "\nItem 6: " << item5;
        std::cout << "\nTrinket: " << item6;
    };
};