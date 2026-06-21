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
   void getUserInput(std::string& line, const std::string& invalid_input_message);
} // namespace InputManager

