#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <cstdlib>
#include <iostream>
#include <string>
#include "DataDragon.h"
#include <fstream>

DataDragon::DataDragon() {

    std::ifstream itemFile("data/ddragon/item.json");

    if (!itemFile.is_open()) {
        std::cerr << "Could not open item.json\n";
        return;
    }

    itemFile >> items;

    std::cout << "Successfully loaded item data!\n";
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