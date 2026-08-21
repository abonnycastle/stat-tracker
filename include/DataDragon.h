#pragma once

#include <string>
#include <nlohmann/json.hpp>

class DataDragon{
public:
    DataDragon();
    std::string getItemName(int itemID);

};