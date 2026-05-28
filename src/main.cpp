#include <iostream>
#include "game.hpp"

int main(int argc, const char** argv) 
{
   TicTacToe game;
   int number_cell;

   while (true)
   {
      game.field_rendering();

      if (game.checkDraw())
      {
         std::cout << "Draw! All moves are over.\n";
         break;
      }

      std::cout << "Player [" << game.getCurrentPlayer() << "] enter cell(0-8): ";
      
      if (!(std::cin >> number_cell) || number_cell < 0 || number_cell > 8) 
      {
         system("clear");
         std::cout << "--- Invalid input! Please enter a number between 0 and 8.\n";
         std::cin.clear();
         std::cin.ignore(10000, '\n');
         continue;
      }
      
      if (!game.canMove(number_cell))
      {
         system("clear");
         std::cout << "--- Cell " << number_cell << " is already taken!\n";
         continue;
      }
      
      game.move(number_cell);

      if (game.checkWin()) 
      {
         system("clear");
         game.field_rendering();
         std::cout << "You [" << game.getCurrentPlayer() << "] won!\n";
         break;
      }

      game.switchPlayer();
      system("clear");
   }

   return 0;
}