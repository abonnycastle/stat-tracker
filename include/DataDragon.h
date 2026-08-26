#pragma once

#include <string>
#include <nlohmann/json.hpp>

class DataDragon{
public:
    DataDragon();
    std::string getItemName(int itemID);
    std::string getRuneName(int runeID, int styleID);
    nlohmann::json runes;
private:
    nlohmann::json items;
};