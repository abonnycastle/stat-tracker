#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <cstdlib>
#include <iostream>
#include <string>
#include "DataDragon.h"
#include <fstream>
#include <map>

DataDragon::DataDragon() {

    std::ifstream itemFile("data/12.6.1/data/en_US/item.json");
    

    if (!itemFile.is_open()) {
        std::cerr << "Could not open item.json\n";
        return;
    }
    
    itemFile >> items;

    std::cout << "Successfully loaded item data!\n";

    std::ifstream runeFile("data/perks.json");
    if (!runeFile.is_open()) {
        std::cerr << "Could not open perks.json";
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

std::string DataDragon::getRuneName(int runeID){
    if (runeHashmap[runeID]){
        std::cout << "Rune ID found in hashmap: " << runeID << std::endl;
        return runes[runeHashmap[runeID]]["name"].get<std::string>();
    }
    else{
        int i = 0;
        while (runes[i]["id"] != runeID) {
            std::cout << runes[i]["id"] << " != " << runeID << std::endl;
            runeHashmap[runeID] = i;
            i++;
            if (i >= runes.size()) {
                std::cerr << "Rune ID not found: " << runeID << std::endl;
                return "Unknown Rune";
            }
        }
        std::cout << "Rune ID not found in hashmap, adding: " << runeID << std::endl;
        return runes[runeHashmap[runeID]+1]["name"].get<std::string>();
    }
    
}