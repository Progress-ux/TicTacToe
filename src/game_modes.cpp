#include "game_modes.hpp"

#include <iostream>
#include <memory>
#include "game.hpp"
#include "network.hpp"
#include "input_manager.hpp"

void GameMode::runMultiplayerGame()
{
   TicTacToe game;
   int move;
   int number_cell;
   std::unique_ptr<NetworkManager> network = std::unique_ptr<NetworkManager>();

   char mode = InputManager::getMode();
   try {
      network = NetworkManager::createNetworkManager(mode);
   } catch (const std::exception& e) {
      std::cerr << e.what() << std::endl;
      return;
   }

   while (true)
   {
      game.field_rendering();

      bool isMyTurn = (mode == 's' && game.getCurrentPlayer() == 'x') || 
                      (mode == 'c' && game.getCurrentPlayer() == 'o');

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
         break;
      }
      
      game.move(move);

      if (game.checkWin()) 
      {
         InputManager::clearScreen();
         game.field_rendering();
         if (isMyTurn) 
         {
            std::cout << "Congratulations! You [" << game.getCurrentPlayer() << "] won!\n";
         } 
         else 
         {
            std::cout << "Opponent [" << game.getCurrentPlayer() << "] won. Better luck next time!\n";
         }
         break;
      }

      if (game.checkDraw()) 
      {
         InputManager::clearScreen();
         game.field_rendering();
         std::cout << "It's a draw! No more moves left.\n";
         break;
      }

      game.switchPlayer();
      InputManager::clearScreen();
   }
}