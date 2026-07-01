#include "multi_game_menu.hpp"

#include "input_manager.hpp"
#include "game.hpp"
#include "language_manager.hpp"
#include "config_manager.hpp"

#include <iostream>
#include <memory>

void MultiGameMenu::runGame()
{
   InputManager::clearScreen();
   if (mode == NetworkMode::None) return;

   TicTacToe game;

   auto networkManager = NetworkManager::createNetworkManager(mode);
   if (mode == NetworkMode::Server)
   {
      std::cout << Loc::get("network_game.wait_player") << "\n";
      auto server = dynamic_cast<Server*>(networkManager.get());

      if (server->start(ConfigManager::getInstance().getServerPort(), ConfigManager::getInstance().getUsername()) != NetworkStatus::Success)
      {
         std::cout << Loc::get("errors.port_blocked") << "\n";
         InputManager::waitForEnter();
         return;
      }
   }
   else if (mode == NetworkMode::Client)
   {
      const int MAX_ATTEMPTS = 5;
      bool connected = false;

      for (int i = 0; i < MAX_ATTEMPTS; ++i)
      {
         std::cout << Loc::get("network_game.conn_attempt") << " " << (i + 1) << "...\n";
         auto client = dynamic_cast<Client*>(networkManager.get());

         auto status = client->connect(
            ConfigManager::getInstance().getServerIp(),
            ConfigManager::getInstance().getServerPort(),
            ConfigManager::getInstance().getTimeout(),
            ConfigManager::getInstance().getUsername()
         );

         if (status == NetworkStatus::Success)
         {
            connected = true;
            break;
         }
         sf::sleep(sf::seconds(1));
      }
      if (!connected)
      {
         std::cout << Loc::get("errors.server_runtime_error") << "\n";
         InputManager::waitForEnter();
         return;
      }
   }

   while (true)
   {
      InputManager::clearScreen();
      game.fieldRendering(); 

      int move = -1;

      bool isMyTurn = (mode == NetworkMode::Server && game.getCurrentPlayer() == 'x') || 
                      (mode == NetworkMode::Client && game.getCurrentPlayer() == 'o');

      if (isMyTurn) 
      {
         move = InputManager::getNextMove(game);
         if (!networkManager->sendMove(move)) 
         {
            std::cout << Loc::get("network_game.connect_broken") << "\n";
            InputManager::waitForEnter();
            break;
         }
      }
      else
      {
         std::cout << Loc::get("network_game.wait_opponent") << " '" << networkManager->getOpponentName() << "'\n";

         auto receiveMove = networkManager->receiveMove();
         if (!receiveMove.has_value())
         {
            std::cout << Loc::get("network_game.connect_broken") << "\n";
            InputManager::waitForEnter();
            break;
         }

         move = receiveMove.value();
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