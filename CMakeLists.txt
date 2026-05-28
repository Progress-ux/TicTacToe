cmake_minimum_required(VERSION 3.10)

project(TicTacToe VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(game src/main.cpp src/game.cpp)

target_include_directories(game PUBLIC include)