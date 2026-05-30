#include "network.hpp"

#include "config_manager.hpp"

std::unique_ptr<NetworkManager> NetworkManager::createNetworkManager(char mode)
{
   if (mode == 's') 
   {
      std::unique_ptr<Server> s = std::make_unique<Server>();
      s->start(ConfigManager::getInstance().getServerPort());
      return s;
   } 
   else 
   {
      std::unique_ptr<Client> c = std::make_unique<Client>();
      const int max_attempts = 5;
      bool connected = false;

      for (int i = 0; i < max_attempts; ++i)
      {
         if (c->connect(
            ConfigManager::getInstance().getServerIp(), 
            ConfigManager::getInstance().getServerPort(), 
            ConfigManager::getInstance().getTimeout()
         ))
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
