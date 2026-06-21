#pragma once
#include "game.hpp"
#include <string>

namespace InputManager
{
   void clearScreen();
   int getNextMove(TicTacToe& game);
   void waitForEnter();

   int getNumber();
   char getYesOrNot();
   std::string& getUserInput(const std::string& invalid_input_message);
} // namespace InputManager

