#include "input_manager.hpp"
#include <iostream>

char InputManager::getMode()
{
   char mode;
   while (true) 
   {
      std::cout << "Select mode: (s)erver or (c)lient: ";
      std::cin >> mode;
      if (mode == 's' || mode == 'c') return mode;
      std::cout << "--- Invalid input! Please enter 's' for server or 'c' for client.\n";
   }
}

int InputManager::getNextMove(TicTacToe &game)
{
   int number_cell;
   while (true) 
   {
      std::cout << "Your turn [" << game.getCurrentPlayer() << "].\nEnter cell (0-8): ";
      
      if (!(std::cin >> number_cell) || number_cell < 0 || number_cell > 8) 
      {
         system("clear");
         game.field_rendering();
         std::cout << "--- Invalid input! Please enter a number between 0 and 8.\n";
         std::cin.clear();
         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
         continue;
      }
      
      if (!game.canMove(number_cell)) 
      {
         system("clear");
         game.field_rendering();
         std::cout << "--- Cell " << number_cell << " is already taken!\n";
         continue;
      }
      
      break; 
   }
   
   return number_cell;
}
