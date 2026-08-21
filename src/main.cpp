#include <iostream>
#include <vector>
#include <nlohmann/json.hpp>

#include "RiotAPI.h"

int main() {

    RiotAPI riot;

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

    return 0;
}