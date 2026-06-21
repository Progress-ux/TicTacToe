#include "input_manager.hpp"

#include <iostream>
#include <limits>

void InputManager::clearScreen()
{
#ifdef _WIN32
   system("cls");
#else
   system("clear");
#endif
}
   
void InputManager::waitForEnter()
{
   std::cout << "\nPress Enter to continue...";
   std::cin.get();
}

int InputManager::getNumber()
{

   std::string line;
   while (true) 
   {
      std::cout << "Enter choice: ";
      if (!std::getline(std::cin, line))
      {
         std::cout << "--- Invalid input! Please enter a valid number!\n";
         continue;
      }

      line.erase(0, line.find_first_not_of(" \t\n\r"));
      line.erase(line.find_last_not_of(" \t\n\r") + 1);

      if (line.empty())
      {
         std::cout << "--- Input cannot be empty!\n";
         continue;
      }

      try
      {
         size_t pos;
         int number = std::stoi(line, &pos);
         
         if (!(pos == line.length()))
         {
            std::cout << "--- Invalid characters after number: '" << line.substr(pos) << "'\n";
            continue;
         }

         return number;

      } catch(const std::invalid_argument& e) {
         std::cout << "--- Not a number! Please enter a number from the menu list.\n";
      } catch(const std::out_of_range& e) {
         std::cout << "--- Number is too large!\n";
      } catch(const std::exception& e) {
         std::cout << "--- Unexpected error: " << e.what() << "\n";
      }
   }
}

int InputManager::getNextMove(TicTacToe &game)
{
   std::string line;
   while (true)
   {
      std::cout << "Your turn [" << game.getCurrentPlayer() << "].\nEnter cell (0-8): ";
      if (!std::getline(std::cin, line))
      {
         return -1;
      }

      line.erase(0, line.find_first_not_of(" \t\n\r"));
      line.erase(line.find_last_not_of(" \t\n\r") + 1);
      
      if(line.empty())
      {
         std::cout << "--- Input cannot be empty!\n";
         continue;
      }

      try
      {
         size_t pos;
         int number = std::stoi(line, &pos);

         if (!(pos == line.length())) 
         {
            std::cout << "--- Invalid characters after number: '" << line.substr(pos) << "'\tPlease enter only a number between 0 and 8.\n";
            continue;
         }

         if (number < 0 || number > 8) 
         {
            std::cout << "--- Number must be between 0 and 8!\n";
            continue;
         }

         if (!game.canMove(number))
         {
            std::cout << "--- Cell " << number << " is already taken!\n";
            continue;
         }

         return number;
      } catch(const std::invalid_argument& e) {
         std::cout << "--- Not a number! Please enter a number between 0 and 8.\n";
      } catch(const std::out_of_range& e) {
         std::cout << "--- Number is too large!\n";
      } catch(const std::exception& e) {
         std::cout << "--- Unexpected error: " << e.what() << "\n";
      }
   }
}
