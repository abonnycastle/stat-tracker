cmake_minimum_required(VERSION 3.20)

project(StatTracker)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(nlohmann_json REQUIRED)
find_package(CURL REQUIRED)

add_executable(tracker
    src/main.cpp
    src/RiotAPI.cpp
    src/DataDragon.cpp
)

target_include_directories(tracker PRIVATE
    include
)

target_link_libraries(tracker PRIVATE
    nlohmann_json::nlohmann_json
    CURL::libcurl
)