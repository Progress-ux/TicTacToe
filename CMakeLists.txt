cmake_minimum_required(VERSION 3.10)

project(TicTacToe VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SFML 3.0 COMPONENTS Network REQUIRED)
find_package(nlohmann_json 3.12.0 REQUIRED)

add_executable(game 
   src/main.cpp 
   src/game.cpp 
   src/network.cpp 
   src/input_manager.cpp
   src/config_manager.cpp
   src/bot.cpp
   src/settings_menu.cpp
   src/single_game_menu.cpp
   src/multi_game_menu.cpp
   src/language_manager.cpp
   src/double_game_menu.cpp
)

add_custom_command(TARGET game POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy_directory
   "${CMAKE_CURRENT_SOURCE_DIR}/lang"
   "$<TARGET_FILE_DIR:game>/lang"
)

target_link_libraries(game 
   SFML::Network 
   nlohmann_json::nlohmann_json
)

target_include_directories(game PUBLIC include)