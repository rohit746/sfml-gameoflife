cmake_minimum_required(VERSION 3.24)
project(gameoflife)

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-system sfml-network sfml-graphics sfml-window)