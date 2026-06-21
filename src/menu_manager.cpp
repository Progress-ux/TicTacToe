#include "menu_manager.hpp"

#include "config_manager.hpp"
#include "input_manager.hpp"
#include "game_modes.hpp"

#include <iostream>
#include <limits>

namespace MenuManager
{
   void showMainMenu()
   {
      std::cout << "=== Tic Tac Toe ===\n";
      std::cout << "1. Play Single Player\n";
      std::cout << "2. Play Multi Player\n";
      std::cout << "3. Settings\n";
      std::cout << "0. Exit\n";
   }
   
   void showSinglePlayMenu()
   {
      std::cout << "=== Single Player ===\n\n";

      std::cout << "Select bot difficulty:\n";
      std::cout << "1. Easy bot\n";
      std::cout << "2. Hard bot\n";
      
      std::cout << "\n0. Back\n";
   }

   void runSinglePlayMenu()
   {
      bool isRunningSinglePlayMenu = true;

      while (isRunningSinglePlayMenu)
      {
         InputManager::clearScreen();

         showSinglePlayMenu();
         int number = InputManager::getNumber();

         switch (number)
         {
         case 1:
            GameMode::runSingleGame(BotDifficulty::Easy);
            break;
         
         case 2:
            GameMode::runSingleGame(BotDifficulty::Hard);
            break;

         case 0: 
            isRunningSinglePlayMenu = false;
            break;
         
         default:
            break;
         }   
      }
      
   }

   void showSetCurrentPlayerMenu()
   {
      std::cout << "=== Select a player ===\n\n";
      std::cout << "1. Player - [x]\n";
      std::cout << "2. Player - [o]\n";
      std::cout << "0. Back\n\n";
   }

   char runSetCurrentPlayerMenu()
   {
      bool isRunningSetCurrentPlayerMenu = true;

      while (isRunningSetCurrentPlayerMenu)
      {
         InputManager::clearScreen();
         
         showSetCurrentPlayerMenu();
         int number = InputManager::getNumber();

         switch (number)
         {
         case 1: return 'x';
         
         case 2: return 'o';

         case 0: return 'e';

         default: 
            std::cout << "Choose one of the options!\n";
            InputManager::waitForEnter();
            continue;
         }
      }
      return 'e';
   }

   

   void showGetModeMenu()
   {
      std::cout << "=== Server or Client mode ===\n\n";

      std::cout << "Select mode:\n";
      std::cout << "1. Server\n";
      std::cout << "2. Client\n";
      
      std::cout << "\n0. Back\n";
   }

   NetworkMode runGetModeMenu()
   {
      bool isRunningGetModeMenu = true;

      while (isRunningGetModeMenu)
      {
         InputManager::clearScreen();
         
         showGetModeMenu();
         int number = InputManager::getNumber();

         switch (number)
         {
         case 1: return NetworkMode::Server;
         
         case 2: return NetworkMode::Client;

         case 0: return NetworkMode::None;

         default: 
            std::cout << "Choose one of the options!\n";
            InputManager::waitForEnter();
            continue;
         }
      }
      return NetworkMode::None;
   }

   void fieldRendering(std::vector<char>& cells)
   {
      std::cout << " " << cells[0] << " | " << cells[1] << " | " << cells[2] << "\n";   
      std::cout << "---+---+---\n";
      std::cout << " "  << cells[3] << " | " << cells[4] << " | " << cells[5] << "\n";   
      std::cout << "---+---+---\n";
      std::cout << " "  << cells[6] << " | " << cells[7] << " | " << cells[8] << "\n"; 
   }

} // namespace MenuManager


