#include "multi_game_menu.hpp"

#include "input_manager.hpp"
#include "game.hpp"
#include "language_manager.hpp"

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
         std::cout << Loc::get("network_game.wait_opponent") << "\n";
         move = network->receiveMove();
      }

      if (move < 0) 
      {
         std::cout << Loc::get("network_game.connect_broken") << "\n";
         InputManager::waitForEnter();
         break;
      }
      
      if (!game.canMove(move))
      {
         std::cerr << Loc::get("network_game.cheat_detect") << "\n";
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

void MultiGameMenu::showSelectNetworkModeMenu()
{
   std::cout << Loc::get("network_menu.title") << "\n\n";

   std::cout << Loc::get("network_menu.select") << "\n";
   std::cout << Loc::get("network_menu.server") << "\n";
   std::cout << Loc::get("network_menu.client") << "\n";
   
   std::cout << Loc::get("network_menu.back") << "\n";
}

void MultiGameMenu::runPlayMenu()
{
   while (true)
   {
      InputManager::clearScreen();

      showSelectNetworkModeMenu();
      std::cout << Loc::get("input.enter_choice") << " ";
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
         std::cout << Loc::get("errors.enter_number_from_list") << "\n";
         InputManager::waitForEnter();
         continue;
      }   
      
      runGame();
   }
   
}