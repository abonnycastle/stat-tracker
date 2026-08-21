#include <iostream>
#include <vector>
#include <nlohmann/json.hpp>
#include <fstream>

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
            std::cout << "\nYour stats:\n";
            std::cout << "Champion: "
                    << match["info"]["participants"][participant]["championName"]
                    << "\n";
            std::cout << "Kills: "
                    << match["info"]["participants"][participant]["kills"]
                    << "\n";
            std::cout << "Deaths: "
                    << match["info"]["participants"][participant]["deaths"]
                    << "\n";
            std::cout << "Assists: "
                    << match["info"]["participants"][participant]["assists"]
                    << "\n";
            break;
        }
    }
    return 0;
}