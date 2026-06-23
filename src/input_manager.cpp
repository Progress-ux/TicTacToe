#include "input_manager.hpp"

#include "language_manager.hpp"

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
   std::cout << "\n" << Loc::get("input.wait_enter");
   std::cin.get();
}

int InputManager::getNumber()
{
   std::string line;
   while (true) 
   {
      getUserInput(line, Loc::get("errors.invalid_arguments"));
      try
      {
         size_t pos;
         int number = std::stoi(line, &pos);
         
         if (!(pos == line.length()))
         {
            std::cout << Loc::get("errors.invalid_characters") <<" '" << line.substr(pos) << "'\n";
            continue;
         }

         return number;

      } catch(const std::invalid_argument& e) {
         std::cout << Loc::get("errors.invalid_arguments") << "\n";
      } catch(const std::out_of_range& e) {
         std::cout << Loc::get("errors.out_of_range") << "\n";
      } catch(const std::exception& e) {
         std::cout << Loc::get("errors.exception") << " " << e.what() << "\n";
      }
   }
}

char InputManager::getYesOrNot()
{
   std::string line;
   if(!std::getline(std::cin, line))
   {
      return 'n';
   }

   line.erase(0, line.find_first_not_of(" \t\n\r"));
   line.erase(line.find_last_not_of(" \t\n\r") + 1);

   if (line.empty()) return 'n';

   char first = std::tolower(line[0]);
   return (first == 'y') ? 'y' : 'n';
}

void InputManager::getUserInput(std::string& line, const std::string &invalid_input_message)
{
   while (true)
   {
      if (!std::getline(std::cin, line))
      {
         std::cout << invalid_input_message << "\n";
         continue;
      }
      
      line.erase(0, line.find_first_not_of(" \t\n\r"));
      line.erase(line.find_last_not_of(" \t\n\r") + 1);
      
      if(line.empty())
      {
         std::cout << Loc::get("errors.empty_input") << "\n";
         continue;
      }
      break;
   }
}

int InputManager::getNextMove(TicTacToe &game)
{
   std::string line;
   while (true)
   {
      std::cout << Loc::get("input.turn") << " [" << game.getCurrentPlayer() << "].\n"; std::cout << Loc::get("input.enter_cell") << " ";
      if (!std::getline(std::cin, line))
      {
         return -1;
      }

      line.erase(0, line.find_first_not_of(" \t\n\r"));
      line.erase(line.find_last_not_of(" \t\n\r") + 1);
      
      if(line.empty())
      {
         std::cout << Loc::get("errors.empty_input") << "\n";
         continue;
      }

      try
      {
         size_t pos;
         int number = std::stoi(line, &pos);

         if (!(pos == line.length())) 
         {
            std::cout << Loc::get("errors.invalid_characters") << " '" << line.substr(pos) << "'\t" << Loc::get("errors.enter_only_number") << "\n";
            continue;
         }

         if (number < 0 || number > 8) 
         {
            std::cout << Loc::get("errors.game_range_number") << "\n";
            continue;
         }

         if (!game.canMove(number))
         {
            std::cout << Loc::get("errors.cell_taken") << "\n";
            continue;
         }

         return number;
      } catch(const std::invalid_argument& e) {
         std::cout << Loc::get("errors.enter_only_number") << "\n";
      } catch(const std::out_of_range& e) {
         std::cout << Loc::get("errors.out_of_range") << "\n";
      } catch(const std::exception& e) {
         std::cout << Loc::get("errors.exception") << " " << e.what() << "\n";
      }
   }
}
