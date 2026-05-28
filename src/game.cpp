#include "game.hpp"
#include <iostream>

TicTacToe::TicTacToe()
   : cells{ '0', '1', '2', '3', '4', '5', '6', '7', '8' },
     currentPlayer('x'),
     moveCount(0)
{
}

void TicTacToe::field_rendering()
{
   std::cout << " " << cells[0] << " | " << cells[1] << " | " << cells[2] << "\n";   
   std::cout << "---+---+---\n";
   std::cout << " "  << cells[3] << " | " << cells[4] << " | " << cells[5] << "\n";   
   std::cout << "---+---+---\n";
   std::cout << " "  << cells[6] << " | " << cells[7] << " | " << cells[8] << "\n"; 
}

bool TicTacToe::checkWin()
{
   static const std::vector<std::vector<int>> winning_combinations = { 
      {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // lines
      {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // columns
      {0, 4, 8}, {2, 4, 6}             // diagonals
   };
   
   for (const std::vector<int>& combo : winning_combinations)
   {
      if (cells[combo[0]] == cells[combo[1]] && 
          cells[combo[1]] == cells[combo[2]]) 
      {
         return true;
      }
   }

   return false;
}

bool TicTacToe::checkDraw()
{
   return moveCount > 8;
}

bool TicTacToe::canMove(int index)
{
   return !(cells[index] == 'x' || cells[index] == 'o');
}

void TicTacToe::move(int index)
{
   cells[index] = currentPlayer;
   moveCount++;
}

char TicTacToe::getCurrentPlayer()
{
   return currentPlayer;
}

void TicTacToe::switchPlayer()
{
   currentPlayer = (currentPlayer == 'x') ? 'o' : 'x';
}
