#pragma once
#include "game.hpp"

namespace InputManager
{
   void clearScreen();
   char getMode();
   int getNextMove(TicTacToe& game);
   void waitForEnter();
} // namespace InputManager

