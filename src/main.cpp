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

int getNextMove(TicTacToe& game)
{
   int number_cell;
   while (true) 
   {
      std::cout << "Your turn [" << game.getCurrentPlayer() << "].\nEnter cell (0-8): ";
      
      if (!(std::cin >> number_cell) || number_cell < 0 || number_cell > 8) 
      {
         system("clear");
         game.field_rendering();
         std::cout << "--- Invalid input! Please enter a number between 0 and 8.\n";
         std::cin.clear();
         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
         continue;
      }
      
      if (!game.canMove(number_cell)) 
      {
         system("clear");
         game.field_rendering();
         std::cout << "--- Cell " << number_cell << " is already taken!\n";
         continue;
      }
      
      break; 
   }
   
   return number_cell;
}

int main(int argc, const char** argv) 
{
   TicTacToe game;
   int move;
   int number_cell;
   std::unique_ptr<NetworkManager> network = std::unique_ptr<NetworkManager>();

   char mode = getMode();
   try {
      network = NetworkManager::createNetworkManager(mode);
   } catch (const std::exception& e) {
      std::cerr << e.what() << std::endl;
      return -1;
   }

   while (true)
   {
      game.field_rendering();

      bool isMyTurn = (mode == 's' && game.getCurrentPlayer() == 'x') || 
                      (mode == 'c' && game.getCurrentPlayer() == 'o');

      if (isMyTurn) 
      {
         move = getNextMove(game);
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

      if (game.checkDraw()) 
      {
         system("clear");
         game.field_rendering();
         std::cout << "It's a draw! No more moves left.\n";
         break;
      }

      game.switchPlayer();
      system("clear");
   }
   return 0;
}