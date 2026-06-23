#include "single_game_menu.hpp"

#include "input_manager.hpp"
#include "language_manager.hpp"

#include <iostream>
#include <memory>

void SingleGameMenu::showSelectDifficultyMenu() const
{
   std::cout << Loc::get("difficulty_menu.title") << "\n\n";

   std::cout << Loc::get("difficulty_menu.select_difficulty") << "\n";
   std::cout << Loc::get("difficulty_menu.easy") << "\n";
   std::cout << Loc::get("difficulty_menu.hard") << "\n\n";
   
   std::cout << Loc::get("difficulty_menu.back") << "\n\n";
}

void SingleGameMenu::showSelectPlayerMenu() const
{
   std::cout << Loc::get("player_menu.title") << "\n\n";

   std::cout << Loc::get("player_menu.player_x") << "\n";
   std::cout << Loc::get("player_menu.player_o") << "\n\n";
   
   std::cout << Loc::get("player_menu.back") << "\n\n";
}

void SingleGameMenu::runPlayMenu()
{
   while (true)
   {
      InputManager::clearScreen();

      showSelectDifficultyMenu();
      std::cout << Loc::get("input.enter_choice") << " ";
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
         std::cout << Loc::get("errors.enter_number_from_list") << "\n";
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
      std::cout << Loc::get("input.enter_choice") << " ";
      int number = InputManager::getNumber();

      switch (number)
      {
      case 1: 
         player = 'x'; 
         return;
      
      case 2: 
         player = 'o'; 
         return;

      case 0: 
         difficulty = BotDifficulty::None;
         return;

      default: 
         std::cout << Loc::get("errors.enter_number_from_list") << "\n";
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
   
   runSelectPlayerMenu();  

   if (difficulty == BotDifficulty::Easy) 
      bot = std::make_unique<EasyBot>();
   else if (difficulty == BotDifficulty::Hard) 
      bot = std::make_unique<HardBot>();
   else return;


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
            std::cout << Loc::get("game.win") << " [" << game.getCurrentPlayer() << "]" << "\n";
         } 
         else 
         {
            std::cout << Loc::get("game.defeat") << "\n";
         }
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
      InputManager::clearScreen();
   }
}
