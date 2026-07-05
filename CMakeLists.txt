cmake_minimum_required(VERSION 3.10)

project(TicTacToe VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SFML 3.0 COMPONENTS Network Graphics REQUIRED)
find_package(nlohmann_json 3.12.0 REQUIRED)

set(ULTRALIGHT_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/libs/ultralight-sdk")

add_executable(game 
   src/main.cpp 
   src/game.cpp 
   src/network.cpp 
   src/config_manager.cpp
   src/bot.cpp
   src/language_manager.cpp
)

target_include_directories(game PRIVATE 
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${ULTRALIGHT_ROOT}/include"
)

target_link_directories(game PRIVATE "${ULTRALIGHT_ROOT}/bin")

target_link_libraries(game PRIVATE
   SFML::Network
   SFML::Graphics
   nlohmann_json::nlohmann_json
   AppCore 
   Ultralight
   UltralightCore
   WebCore
)

set_target_properties(game PROPERTIES
   SKIP_BUILD_RPATH FALSE
   BUILD_WITH_INSTALL_RPATH FALSE
   INSTALL_RPATH "."
   LINK_FLAGS "-Wl,-rpath,'$ORIGIN'"
)

add_custom_command(TARGET game POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy_directory
   "${CMAKE_CURRENT_SOURCE_DIR}/lang"
   "$<TARGET_FILE_DIR:game>/lang"
   COMMENT "Copying language files..."
)

file(GLOB_RECURSE UI_FILES "${CMAKE_CURRENT_SOURCE_DIR}/ui/*")

add_custom_target(copy_ui_assets ALL
   COMMAND ${CMAKE_COMMAND} -E copy_directory
   "${CMAKE_CURRENT_SOURCE_DIR}/ui"
   "$<TARGET_FILE_DIR:game>/assets"
   DEPENDS ${UI_FILES}
   COMMENT "Copying assets files..."
)

add_custom_command(TARGET game POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy_directory
   "${ULTRALIGHT_ROOT}/bin/"
   "$<TARGET_FILE_DIR:game>"
   COMMENT "Copying Ultralight binaries and assets..."
)

add_custom_command(TARGET game POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy_directory
   "${ULTRALIGHT_ROOT}/resources/"
   "$<TARGET_FILE_DIR:game>/assets/resources"
   COMMENT "Copying Ultralight resources into assets..."
)

