#include "single_game_menu.hpp"

#include "input_manager.hpp"

#include <iostream>
#include <memory>

void SingleGameMenu::showSelectDifficultyMenu() const
{
   std::cout << "=== Single Player ===\n\n";

   std::cout << "Select bot difficulty:\n";
   std::cout << "1. Easy bot\n";
   std::cout << "2. Hard bot\n";
   
   std::cout << "\n0. Back\n";
}

void SingleGameMenu::showSelectPlayerMenu() const
{
   std::cout << "=== Select a player ===\n\n";
   std::cout << "1. Player - [x]\n";
   std::cout << "2. Player - [o]\n";
   std::cout << "0. Back\n\n";
}

void SingleGameMenu::runPlayMenu()
{
   while (true)
   {
      InputManager::clearScreen();

      showSelectDifficultyMenu();
      std::cout << "Enter choice: ";
      int number = InputManager::getNumber();

      switch (number)
      {
      case 1:
         difficulty = BotDifficulty::Easy;
         break;
      
      case 2:
         difficulty = BotDifficulty::Hard;
         break;

      case 0: 
         return;
      
      default:
         std::cout << "--- Invalid input! Please enter a number from the list\n";
         InputManager::waitForEnter();
         continue;
      }   
      
      runGame();
   }
   
}

void SingleGameMenu::runSelectPlayerMenu()
{
   while (true)
   {
      InputManager::clearScreen();
      
      showSelectPlayerMenu();
      int number = InputManager::getNumber();

      switch (number)
      {
      case 1: 
         player = 'x'; 
         return;
      
      case 2: 
         player = 'o'; 
         return;

      case 0: return;

      default: 
         std::cout << "--- Invalid input! Please enter a number from the list\n";
         InputManager::waitForEnter();
         continue;
      }
   }
}

void SingleGameMenu::runGame()
{
   TicTacToe game;
   int move;

   std::unique_ptr<Bot> bot;

   if (difficulty == BotDifficulty::Easy) 
      bot = std::make_unique<EasyBot>();
   else if (difficulty == BotDifficulty::Hard) 
      bot = std::make_unique<HardBot>();
   else return;

   runSelectPlayerMenu();  

   InputManager::clearScreen();
   if (player == 'e') return;

   while (true)
   {
      game.fieldRendering();

      bool isMyTurn = (player == 'x' && game.getCurrentPlayer() == 'x') || 
                      (player == 'o' && game.getCurrentPlayer() == 'o');

      if (isMyTurn) 
      {
         move = InputManager::getNextMove(game);
      }
      else
      {
         while(true)
         {
            move = bot->move(game);
            if (game.canMove(move)) break;
         }
      }

      game.move(move);

      if (game.checkWin()) 
      {
         InputManager::clearScreen();
         game.fieldRendering();
         if (isMyTurn) 
         {
            std::cout << "Congratulations! You [" << game.getCurrentPlayer() << "] won!\n";
         } 
         else 
         {
            std::cout << "Opponent [" << game.getCurrentPlayer() << "] won. Better luck next time!\n";
         }
         InputManager::waitForEnter();
         break;
      }

      if (game.checkDraw()) 
      {
         InputManager::clearScreen();
         game.fieldRendering();
         std::cout << "It's a draw! No more moves left.\n";
         InputManager::waitForEnter();
         break;
      }

      game.switchPlayer();
      InputManager::clearScreen();
   }
}
