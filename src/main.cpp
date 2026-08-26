#include <iostream>
#include <vector>
#include <nlohmann/json.hpp>
#include <fstream>

#include "RiotAPI.h"
#include "GameStats.h"
#include "DataDragon.h"

int main() {

    RiotAPI riot;
    DataDragon data;
    GameStats stats;

    std::string gameName;
    std::string tagLine;

    std::cout << "Enter your Riot ID name: ";
    std::getline(std::cin, gameName);

    std::cout << "Enter your Riot ID tag: ";
    std::getline(std::cin, tagLine);

    std::string puuid = riot.getPUUID(gameName, tagLine);

    if (puuid.empty()) {
        std::cout << "Failed to get PUUID.\n";
        return 1;
    }

    std::cout << "\nPUUID successfully found!\n";

    std::vector<std::string> matches =
        riot.getMatchHistory(puuid);

    if (matches.empty()) {
        std::cout << "No matches found.\n";
        return 1;
    }

    std::cout << "\nRecent matches:\n";

    for (const std::string& matchId : matches) {
        std::cout << matchId << "\n";
    }

    std::string matchId = matches[0];

    std::cout << "\nGetting match: "
              << matchId << "\n";

    nlohmann::json match = riot.getMatch(matchId);

    std::ofstream file("match.json");
    file << match.dump(4);
    file.close();

    std::cout << "Match ID: "
            << match["metadata"]["matchId"]
            << "\n";

    std::cout << "Game mode: "
            << match["info"]["gameMode"]
            << "\n";

    std::cout << "Game duration: "
            << match["info"]["gameDuration"]
            << " seconds\n";

    std::cout << "Number of participants: "
            << match["info"]["participants"].size()
            << "\n";

    for(int participant = 0; participant < match["info"]["participants"].size(); ++participant) {
        if (match["info"]["participants"][participant]["puuid"] == puuid) {
                stats.championName = match["info"]["participants"][participant]["championName"];
                stats.kills = match["info"]["participants"][participant]["kills"];
                stats.deaths = match["info"]["participants"][participant]["deaths"];
                stats.assists = match["info"]["participants"][participant]["assists"];
                stats.item0 = data.getItemName(match["info"]["participants"][participant]["item0"]);
                stats.item1 = data.getItemName(match["info"]["participants"][participant]["item1"]);
                stats.item2 = data.getItemName(match["info"]["participants"][participant]["item2"]);
                stats.item3 = data.getItemName(match["info"]["participants"][participant]["item3"]);
                stats.item4 = data.getItemName(match["info"]["participants"][participant]["item4"]);
                stats.item5 = data.getItemName(match["info"]["participants"][participant]["item5"]);
                stats.item6 = data.getItemName(match["info"]["participants"][participant]["item6"]);
                stats.displayStats();

                int mainRuneID = match["info"]["participants"][participant]["perks"]["styles"][0]["selections"][0]["perk"];
                int mainStyleID = match["info"]["participants"][participant]["perks"]["styles"][0]["style"];
                std::cout << mainRuneID << "\n";
                std::cout << mainStyleID << "\n";
                std::cout << data.getRuneName(mainRuneID, mainStyleID);
            break;
        }
    }

    return 0;
}