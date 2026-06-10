#include "game_modes.hpp"
#include "config_manager.hpp"
#include "input_manager.hpp"
#include "menu_manager.hpp"
#include <limits>
#include <iostream>

int main(int argc, const char** argv) 
{
   ConfigManager::getInstance().load();
   bool isRunningGame = true;
            

   while(isRunningGame)
   {
      InputManager::clearScreen();
      MenuManager::showMainMenu();
      int number = MenuManager::getNumber();

      if (number > 3 || number < 0)
      {
         std::cout << "--- Invalid input! Please enter a number from the list\n";
         MenuManager::waitForEnter();
         continue;
      }

      switch (number)
      {
      case 1: // Single game
         {
            
            break;
         }
      case 2: // Multiplayer game
         {
            InputManager::clearScreen();
            GameMode::runMultiplayerGame();
            break;
         }
      case 3: // Settings menu
         {
            MenuManager::runSettingsMenu();
            break;
         }
      case 0: // Exit
         {
            InputManager::clearScreen();
            isRunningGame = false;
            break;
         }
      
      default:
         break;
      }
   }

   return 0;
}