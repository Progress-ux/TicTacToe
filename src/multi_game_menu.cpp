#include "multi_game_menu.hpp"

#include "input_manager.hpp"
#include "game.hpp"

#include <iostream>
#include <memory>

void MultiGameMenu::runGame()
{
   TicTacToe game;
   int move;
   std::unique_ptr<NetworkManager> network;

   if (mode == NetworkMode::None) return;

   try {
      network = NetworkManager::createNetworkManager(mode);
   } catch (const std::exception& e) {
      std::cerr << e.what() << std::endl;
      return;
   }

   while (true)
   {
      game.fieldRendering(); 

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

void MultiGameMenu::showSelectNetworkModeMenu()
{
   std::cout << "=== Server or Client mode ===\n\n";

   std::cout << "Select mode:\n";
   std::cout << "1. Server\n";
   std::cout << "2. Client\n";
   
   std::cout << "\n0. Back\n";
}

void MultiGameMenu::runPlayMenu()
{
   while (true)
   {
      InputManager::clearScreen();

      showSelectNetworkModeMenu();
      std::cout << "Enter choice: ";
      int number = InputManager::getNumber();

      switch (number)
      {
      case 1:
         mode = NetworkMode::Server;
         break;
      
      case 2:
         mode = NetworkMode::Client;
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