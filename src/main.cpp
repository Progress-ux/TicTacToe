#include "config_manager.hpp"
#include "input_manager.hpp"
#include "settings_menu.hpp"

#include "single_game_menu.hpp"
#include "multi_game_menu.hpp"

#include <limits>
#include <iostream>

void showMainMenu()
{
   std::cout << "=== Tic Tac Toe ===\n";
   std::cout << "1. Play Single Player\n";
   std::cout << "2. Play Multi Player\n";
   std::cout << "3. Settings\n";
   std::cout << "0. Exit\n";
}

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
   
   while(true)
   {
      InputManager::clearScreen();
      showMainMenu();
      std::cout << "Enter choice: ";
      int number = InputManager::getNumber();

      switch (number)
      {
      case 1: // Single game
         {
            SingleGameMenu menu;
            menu.runPlayMenu();
            break;
         }
      case 2: // Multiplayer game
         {
            MultiGameMenu menu;
            menu.runPlayMenu();
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
            return 0;
         }
      
      default:
         std::cout << "--- Invalid input! Please enter a number from the list\n";
         InputManager::waitForEnter();
         break;
      }
   }

   return 0;
}