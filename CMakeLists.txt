cmake_minimum_required(VERSION 3.16)
project(imgw_fetch)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)

add_executable(cli-weather-app main.cpp)

target_link_libraries(cli-weather-app PRIVATE CURL::libcurl nlohmann_json::nlohmann_json)

