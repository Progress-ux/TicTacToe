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

std::unique_ptr<NetworkManager> createNetworkManager(char mode)
{
   if (mode == 's') 
   {
      std::unique_ptr<Server> s = std::make_unique<Server>();
      s->start(53000);
      return s;
   } 
   else 
   {
      std::unique_ptr<Client> c = std::make_unique<Client>();
      const int max_attempts = 5;
      bool connected = false;

      for (int i = 1; i <= max_attempts; ++i)
      {
         std::cout << "Connecting to server... Attempt " << i << "\n";
         if (c->connect("127.0.0.1", 53000, 3.0f))
         {
            connected = true;
            break;
         }
         sf::sleep(sf::seconds(1));
      }
      
      if (!connected)
      {
         throw std::runtime_error("Error: Server did not respond");
      }
      return c;
   }
}

int getNextMove(bool isMyTurn, TicTacToe& game, NetworkManager& network)
{
   if (isMyTurn)
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
      
      network.sendMove(number_cell);
      return number_cell;
   }
   else 
   {
      std::cout << "Waiting for opponent's move...\n";
      return network.receiveMove();
   }
}

int main(int argc, const char** argv) 
{
   TicTacToe game;
   int number_cell;
   std::unique_ptr<NetworkManager> network = std::unique_ptr<NetworkManager>();

   char mode = getMode();
   try {
      network = createNetworkManager(mode);
   } catch (const std::exception& e) {
      std::cerr << e.what() << std::endl;
      return -1;
   }

   while (true)
   {
      game.field_rendering();

      bool isMyTurn = (mode == 's' && game.getCurrentPlayer() == 'x') || 
                      (mode == 'c' && game.getCurrentPlayer() == 'o');

      int move = getNextMove(isMyTurn, game, *network);
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