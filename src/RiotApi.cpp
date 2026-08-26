#include "RiotAPI.h"

#include <curl/curl.h>
#include <nlohmann/json.hpp>

#include <cstdlib>
#include <iostream>

using json = nlohmann::json;

// This function receives data from Riot and puts it into a string.
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t totalSize = size * nmemb;

    std::string* response = static_cast<std::string*>(userp);
    response->append(static_cast<char*>(contents), totalSize);

    return totalSize;
}

RiotAPI::RiotAPI() {
    const char* key = std::getenv("RIOT_API_KEY");

    if (key != nullptr) {
        apiKey = key;
    } else {
        std::cerr << "RIOT_API_KEY environment variable not found.\n";
    }
}

std::string RiotAPI::getPUUID(const std::string& gameName,
                              const std::string& tagLine) {

    CURL* curl = curl_easy_init();

    if (!curl) {
        std::cerr << "Failed to initialize cURL.\n";
        return "";
    }

    std::string response;

    char* encodedGameName = curl_easy_escape(
    curl,
    gameName.c_str(),
    static_cast<int>(gameName.length())
);

char* encodedTagLine = curl_easy_escape(
    curl,
    tagLine.c_str(),
    static_cast<int>(tagLine.length())
);

if (encodedGameName == nullptr || encodedTagLine == nullptr) {
    std::cerr << "Failed to encode Riot ID.\n";

    if (encodedGameName != nullptr)
        curl_free(encodedGameName);

    if (encodedTagLine != nullptr)
        curl_free(encodedTagLine);

    curl_easy_cleanup(curl);

    return "";
}

std::string url =
    "https://americas.api.riotgames.com/riot/account/v1/accounts/by-riot-id/"
    + std::string(encodedGameName)
    + "/"
    + std::string(encodedTagLine);

curl_free(encodedGameName);
curl_free(encodedTagLine);

    struct curl_slist* headers = nullptr;

    headers = curl_slist_append(
        headers,
        ("X-Riot-Token: " + apiKey).c_str()
    );

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode result = curl_easy_perform(curl);

    if (result != CURLE_OK) {
        std::cerr << "Request failed: "
                  << curl_easy_strerror(result) << "\n";

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);

        return "";
    }

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    try {
        json data = json::parse(response);

        if (data.contains("puuid")) {
            return data["puuid"].get<std::string>();
        }

        std::cerr << "Response did not contain a PUUID.\n";
        std::cerr << "Riot response: " << response << "\n";

    } catch (const json::parse_error& e) {
        std::cerr << "Failed to parse Riot's response.\n";
        std::cerr << response << "\n";
    }

    return "";
}

std::vector<std::string> RiotAPI::getMatchHistory(
    const std::string& puuid) {

    CURL* curl = curl_easy_init();

    if (!curl) {
        std::cerr << "Failed to initialize cURL.\n";
        return {};
    }

    std::string response;

    std::string url =
        "https://americas.api.riotgames.com/lol/match/v5/matches/by-puuid/"
        + puuid
        + "/ids?start=0&count=10";

    struct curl_slist* headers = nullptr;

    headers = curl_slist_append(
        headers,
        ("X-Riot-Token: " + apiKey).c_str()
    );

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode result = curl_easy_perform(curl);

    if (result != CURLE_OK) {
        std::cerr << "Request failed: "
                  << curl_easy_strerror(result) << "\n";

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);

        return {};
    }

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    try {
        json data = json::parse(response);

        std::vector<std::string> matchIds;

        for (const auto& matchId : data) {
            matchIds.push_back(matchId.get<std::string>());
        }

        return matchIds;

    } catch (const json::parse_error& e) {
        std::cerr << "Failed to parse match history.\n";
        std::cerr << response << "\n";
    }

    return {};
}

nlohmann::json RiotAPI::getMatch(const std::string& matchId) {

    CURL* curl = curl_easy_init();

    if (!curl) {
        std::cerr << "Failed to initialize cURL.\n";
        return {};
    }

    std::string response;

    std::string url =
        "https://americas.api.riotgames.com/lol/match/v5/matches/"
        + matchId;

    struct curl_slist* headers = nullptr;

    headers = curl_slist_append(
        headers,
        ("X-Riot-Token: " + apiKey).c_str()
    );

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode result = curl_easy_perform(curl);

    if (result != CURLE_OK) {
        std::cerr << "Request failed: "
                  << curl_easy_strerror(result) << "\n";

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);

        return {};
    }

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    try {
        return nlohmann::json::parse(response);

    } catch (const nlohmann::json::parse_error& e) {
        std::cerr << "Failed to parse match response.\n";
        std::cerr << response << "\n";

        return {};
    }
}