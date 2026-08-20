#ifndef RIOT_API_H
#define RIOT_API_H

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

class RiotAPI {
public:
    RiotAPI();

    std::string getPUUID(const std::string& gameName,
                         const std::string& tagLine);

    std::vector<std::string> getMatchHistory(const std::string& puuid);

    nlohmann::json getMatch(const std::string& matchId);

private:
    std::string apiKey;
};

#endif