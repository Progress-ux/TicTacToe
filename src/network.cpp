#include "network.hpp"

std::unique_ptr<NetworkManager> NetworkManager::createNetworkManager(char mode)
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

      for (int i = 0; i < max_attempts; ++i)
      {
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
