#include "game_modes.hpp"

#include <iostream>
#include <memory>

#include "game.hpp"
#include "network.hpp"
#include "input_manager.hpp"
#include "menu_manager.hpp"

void GameMode::runMultiplayerGame()
{
   TicTacToe game;
   int move;
   std::unique_ptr<NetworkManager> network;

   NetworkMode mode = MenuManager::runGetModeMenu();

   if (mode == NetworkMode::None) return;

   try {
      network = NetworkManager::createNetworkManager(mode);
   } catch (const std::exception& e) {
      std::cerr << e.what() << std::endl;
      return;
   }

   while (true)
   {
      MenuManager::fieldRendering(game.getCells()); 

      bool isMyTurn = (mode == NetworkMode::Server && game.getCurrentPlayer() == 'x') || 
                      (mode == NetworkMode::Client && game.getCurrentPlayer() == 'o');

      if (isMyTurn) 
      {
         move = InputManager::getNextMove(game);
         network->sendMove(move);
      }
      else
      {
         std::cout << "Waiting for opponent's move...\n";
         move = network->receiveMove();
      }

      if (move < 0) 
      {
         std::cerr << "The connection was broken." << std::endl;
         InputManager::waitForEnter();
         break;
      }
      
      if (!game.canMove(move))
      {
         std::cerr << "Cheat detected! Invalid move." << std::endl;
         InputManager::waitForEnter();
         break;
      }
      game.move(move);

      if (game.checkWin()) 
      {
         InputManager::clearScreen();
         MenuManager::fieldRendering(game.getCells());
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
         MenuManager::fieldRendering(game.getCells());
         std::cout << "It's a draw! No more moves left.\n";
         InputManager::waitForEnter();
         break;
      }

      game.switchPlayer();
      InputManager::clearScreen();
   }
}

void GameMode::runSingleGame(BotDifficulty difficulty)
{
   TicTacToe game;
   int move;

   std::unique_ptr<Bot> bot;

   if (difficulty == BotDifficulty::Easy) 
      bot = std::make_unique<EasyBot>();
   else if (difficulty == BotDifficulty::Hard) 
      bot = std::make_unique<HardBot>();
   else return;

   char player = MenuManager::runSetCurrentPlayerMenu();  
   InputManager::clearScreen();
   if (player == 'e') return;

   while (true)
   {
      MenuManager::fieldRendering(game.getCells());

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

      if (!game.canMove(move))
      {
         std::cerr << "Cheat detected! Invalid move." << std::endl;
         InputManager::waitForEnter();
         break;
      }
      game.move(move);

      if (game.checkWin()) 
      {
         InputManager::clearScreen();
         MenuManager::fieldRendering(game.getCells());
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
         MenuManager::fieldRendering(game.getCells());
         std::cout << "It's a draw! No more moves left.\n";
         InputManager::waitForEnter();
         break;
      }

      game.switchPlayer();
      InputManager::clearScreen();
   }
}