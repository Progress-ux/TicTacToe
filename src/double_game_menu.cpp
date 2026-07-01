#include "double_game_menu.hpp"

#include "input_manager.hpp"
#include "game.hpp"
#include "language_manager.hpp"
#include "config_manager.hpp"

#include <iostream>

void DoubleGameMenu::runPlayGame()
{
   InputManager::clearScreen();
   TicTacToe game;

   while (true)
   {
      InputManager::clearScreen();
      game.fieldRendering(); 

      int move = InputManager::getNextMove(game);
      game.move(move);

      if (game.checkWin()) 
      {
         InputManager::clearScreen();
         game.fieldRendering();
         std::cout << Loc::get("game.win") << " [" << game.getCurrentPlayer() << "]" << "\n";
         InputManager::waitForEnter();
         break;
      }

      if (game.checkDraw()) 
      {
         InputManager::clearScreen();
         game.fieldRendering(); 
         std::cout << Loc::get("game.draw") << "\n";
         InputManager::waitForEnter();
         break;
      }

      game.switchPlayer();
   }
}