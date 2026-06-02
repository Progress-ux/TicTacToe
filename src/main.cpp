#include "game_modes.hpp"
#include "config_manager.hpp"
#include "input_manager.hpp"
#include <iostream>

void displayMenu()
{
   std::cout << "=== Tic Tac Toe ===\n";
   std::cout << "1. Play Single Player (under development)\n";
   std::cout << "2. Play Multi Player\n";
   std::cout << "3. Settings (under development)\n";
   std::cout << "0. Exit\n";
}

int getNumber()
{
   int number;
   while (true) 
   {
      if (!(std::cin >> number) || number > 3 || number < 0) 
      {
         std::cin.clear();
         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

         InputManager::clearScreen();
         std::cout << "--- Invalid input! Please enter a number from the list\n";
         displayMenu();
         continue;
      }
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      break; 
   }
   
   return number;
}

int main(int argc, const char** argv) 
{
   ConfigManager::getInstance().load();
   bool isRunningGame = true;
            

   while(isRunningGame)
   {
      InputManager::clearScreen();
      displayMenu();
      int number = getNumber();

      switch (number)
      {
      case 1: // Single game
         {
            // TODO: Create a single-player game with two difficulty levels to choose from
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
            // TODO: Create a network and profile settings menu
            break;
         }
      case 0: // Exit
         {
            isRunningGame = false;
            break;
         }
      
      default:
         break;
      }
   }

   return 0;
}