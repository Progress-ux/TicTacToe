#include "game_modes.hpp"
#include "config_manager.hpp"

int main(int argc, const char** argv) 
{
   ConfigManager::getInstance().load();
   GameMode::runMultiplayerGame();
   return 0;
}