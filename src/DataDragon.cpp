#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <cstdlib>
#include <iostream>
#include <string>
#include "DataDragon.h"
#include <fstream>

DataDragon::DataDragon() {

    std::ifstream itemFile("data/12.6.1/data/en_US/item.json");
    

    if (!itemFile.is_open()) {
        std::cerr << "Could not open item.json\n";
        return;
    }
    
    itemFile >> items;

    std::cout << "Successfully loaded item data!\n";

    std::ifstream runeFile("data/12.6.1/data/en_US/runesReforged.json");
    if (!runeFile.is_open()) {
        std::cerr << "Could not open runesReforged.json";
        return;
    }
    runeFile >> runes;

    std::cout << "Successfully loaded rune data!\n";
};

std::string DataDragon::getItemName(int itemID)
{
    if (itemID == 0) {
        return "Empty";
    }

    std::string id = std::to_string(itemID);

    if (!items["data"].contains(id)) {
        return "Unknown Item";
    }

    return items["data"][id]["name"].get<std::string>();
}

std::string DataDragon::getRuneName(int runeID, int styleID){
    int i = 0;
    while (runes[i]["id"] != styleID){
        std::cout << runes[i]["id"] << "\n";
        i++;
        if (i > 20){
            break;
        }
    }
    int j = 0;
    std::string id = std::to_string(runeID);
    while (!runes[i]["slots"][j]["runes"].contains(id)){
        j++;
        if (j > 20){
            break;
        }
    }
    return runes[i]["slots"][j]["runes"]["name"].get<std::string>();
}