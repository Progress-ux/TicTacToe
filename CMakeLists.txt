cmake_minimum_required(VERSION 3.10)

project(TicTacToe VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SFML 3.0 COMPONENTS Network REQUIRED)

add_executable(game 
   src/main.cpp 
   src/game.cpp 
   src/network.cpp 
   src/input_manager.cpp
   src/game_modes.cpp
)

target_link_libraries(game SFML::Network)
target_include_directories(game PUBLIC include)