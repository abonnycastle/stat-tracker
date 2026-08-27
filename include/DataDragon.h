#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include <map>

class DataDragon{
public:
    DataDragon();
    std::string getItemName(int itemID);
    std::string getRuneName(int runeID);
    
private:
    nlohmann::json items;
    nlohmann::json runes;
    std::map<int , int> runeHashmap;
};