#include "game_modes.hpp"
#include "config_manager.hpp"
#include "input_manager.hpp"
#include "menu_manager.hpp"
#include "settings_menu.hpp"

#include <limits>
#include <iostream>

int main(int argc, const char** argv) 
{
   try
   {
      ConfigManager::getInstance().load();
   }
   catch(const std::runtime_error& e)
   {
      std::cerr << e.what() << '\n';
      InputManager::waitForEnter();
   }
   catch(const std::exception& e)
   {
      std::cerr << e.what() << '\n';
      InputManager::waitForEnter();
   }
   
   bool isRunningGame = true;

   while(isRunningGame)
   {
      InputManager::clearScreen();
      MenuManager::showMainMenu();
      std::cout << "Enter choice: ";
      int number = InputManager::getNumber();

      switch (number)
      {
      case 1: // Single game
         {
            MenuManager::runSinglePlayMenu();
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
            SettingsMenu menu;
            menu.run();
            break;
         }
      case 0: // Exit
         {
            InputManager::clearScreen();
            isRunningGame = false;
            break;
         }
      
      default:
         std::cout << "--- Invalid input! Please enter a number from the list\n";
         InputManager::waitForEnter();
         break;
      }
   }

   return 0;
}