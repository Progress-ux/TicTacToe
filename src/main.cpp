#include "config_manager.hpp"
#include "input_manager.hpp"
#include "settings_menu.hpp"
#include "language_manager.hpp"

#include "single_game_menu.hpp"
#include "double_game_menu.hpp"
#include "multi_game_menu.hpp"

#include <limits>
#include <iostream>

#if defined(_WIN32)
#include <windows.h>
#endif

void showMainMenu()
{
   std::cout << Loc::get("main_menu.title") << "\n\n";
   std::cout << Loc::get("main_menu.single") << "\n";
   std::cout << Loc::get("main_menu.double") << "\n";
   std::cout << Loc::get("main_menu.multi") << "\n\n";
   std::cout << Loc::get("main_menu.settings") << "\n\n";
   std::cout << Loc::get("main_menu.exit") << "\n";
}

int main(int argc, const char** argv) 
{
   try
   {
      ConfigManager::getInstance().load();
      if (!Loc::load(ConfigManager::getInstance().getLangFolder() / ConfigManager::getInstance().getLang()))
      {
         std::cerr << "Failed to download language pack\n";
         return 0;
      }
   }
   catch(const std::runtime_error& e)
   {
      std::cerr << e.what() << '\n';
      return 0;
   }
   catch(const std::exception& e)
   {
      std::cerr << e.what() << '\n';
      InputManager::waitForEnter();
   }

#if defined(_WIN32)
   SetConsoleCP(65001);
   SetConsoleOutputCP(65001);
#endif

   while(true)
   {
      InputManager::clearScreen();
      showMainMenu();
      std::cout << Loc::get("input.enter_choice") << " ";
      int number = InputManager::getNumber();

      switch (number)
      {
      case 1: // Single game
         {
            SingleGameMenu menu;
            menu.runPlayMenu();
            break;
         }
      case 2: // Double game
         {
            DoubleGameMenu menu;
            menu.runPlayGame();
            break;
         }
      case 3: // Multiplayer game
         {
            MultiGameMenu menu;
            menu.runPlayMenu();
            break;
         }
      case 4: // Settings menu
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
         std::cout << Loc::get("errors.enter_number_from_list") << "\n";
         InputManager::waitForEnter();
         break;
      }
   }

   return 0;
}