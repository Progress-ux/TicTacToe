#include <iostream>
#include <memory>
#include "game.hpp"
#include "network.hpp"

char getMode() 
{
   char mode;
   while (true) 
   {
      std::cout << "Select mode: (s)erver or (c)lient: ";
      std::cin >> mode;
      if (mode == 's' || mode == 'c') return mode;
      std::cout << "--- Invalid input! Please enter 's' for server or 'c' for client.\n";
   }
}

int main(int argc, const char** argv) 
{
   TicTacToe game;
   std::unique_ptr<NetworkManager> network = nullptr;
   int number_cell;

   char mode = getMode();
   if (mode == 's') 
   {
      std::unique_ptr<Server> s = std::make_unique<Server>();
      s->start(53000);
      network = std::move(s);
   } 
   else 
   {
      std::unique_ptr<Client> c = std::make_unique<Client>();
      c->connect("127.0.0.1", 53000);
      network = std::move(c);
   }

   while (true)
   {
      game.field_rendering();

      if (game.checkDraw())
      {
         std::cout << "Draw! All moves are over.\n";
         break;
      }

      bool isMyTurn = (mode == 's' && game.getCurrentPlayer() == 'x') || 
                      (mode == 'c' && game.getCurrentPlayer() == 'o');

      if (isMyTurn)
      {
         std::cout << "Your turn [" << game.getCurrentPlayer() << "].\n";
         std::cout << "Enter cell (0-8): ";
         
         if (!(std::cin >> number_cell) || number_cell < 0 || number_cell > 8) 
         {
            system("clear");
            std::cout << "--- Invalid input! Please enter a number between 0 and 8.\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
         }
         
         if (!game.canMove(number_cell))
         {
            system("clear");
            std::cout << "--- Cell " << number_cell << " is already taken!\n";
            continue;
         }
         
         game.move(number_cell);
         network->sendMove(number_cell);
      } 
      else 
      {
         std::cout << "Waiting for opponent's move...\n";
         int opponentMove = network->receiveMove();
         if (opponentMove >= 0) 
         {
            game.move(opponentMove);
         } 
         else 
         {
            system("clear");
            std::cout << "--- Failed to receive opponent's move. Please check your connection.\n";
            break;
         }
      }

      if (game.checkWin()) 
      {
         system("clear");
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

      game.switchPlayer();
      system("clear");
   }
   return 0;
}