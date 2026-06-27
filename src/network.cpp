#include "network.hpp"

std::unique_ptr<NetworkManager> NetworkManager::createNetworkManager(NetworkMode mode)
{
   if (mode == NetworkMode::Server) 
   {
      return std::make_unique<Server>();
   } 
   else 
   {
      return std::make_unique<Client>();
   }
   return nullptr;
}
