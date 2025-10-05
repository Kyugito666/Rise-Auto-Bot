cmake_minimum_required(VERSION 3.10)
project(RiseAutoBot-CPP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find necessary packages using vcpkg
find_package(nlohmann_json REQUIRED)
find_package(cpr REQUIRED)
find_package(PDCurses REQUIRED)
find_package(fmt REQUIRED)

add_executable(RiseAutoBot-CPP src/main.cpp src/ui.cpp src/wallet.cpp src/blockchain.cpp)

target_link_libraries(RiseAutoBot-CPP PRIVATE
    nlohmann_json::nlohmann_json
    cpr::cpr
    PDCurses::pdcurses
    fmt::fmt
)
