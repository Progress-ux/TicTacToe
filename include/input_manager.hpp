#pragma once
#include "game.hpp"

namespace InputManager
{
   void clearScreen();
   int getNextMove(TicTacToe& game);
   void waitForEnter();
   int getNumber();
   char getYesOrNot();
} // namespace InputManager

