#pragma once 
#include <SFML/Network.hpp>
#include <string>
#include <optional>
#include <memory>

class Server;
class Client;

enum class NetworkStatus
{
   Success,
   Error_PortBlocked,
   Error_Disconnected,
   Error_ServerUnavailable,
   Error_InvalidAddress
};

enum class NetworkMode 
{
   Server,
   Client,
   None
};

class NetworkManager 
{
protected: 
   sf::TcpSocket socket;
public:
   virtual ~NetworkManager() = default;

   static std::unique_ptr<NetworkManager> createNetworkManager(NetworkMode mode);

   bool sendMove(int index) 
   {
      sf::Packet packet;
      packet << index;
      return socket.send(packet) == sf::Socket::Status::Done;
   }

   std::optional<int> receiveMove()
   {
      sf::Packet packet;
      if (socket.receive(packet) == sf::Socket::Status::Done) 
      {
         int index;
         packet >> index;
         return index;
      }
      return std::nullopt;
   }
};

class Server : public NetworkManager
{
private:
   sf::TcpListener listener;
public:
   NetworkStatus start(unsigned short port)
   {
      if (listener.listen(port) != sf::Socket::Status::Done) 
      {
         return NetworkStatus::Error_PortBlocked;
      }
      if (listener.accept(socket) != sf::Socket::Status::Done)
      {
         return NetworkStatus::Error_Disconnected;
      }
      return NetworkStatus::Success;
   }

};

class Client : public NetworkManager
{
public:
   NetworkStatus connect(const std::string& ipString, unsigned short port, float timeout) 
   {
      auto listIP = sf::Dns::resolve(ipString);

      if (!listIP.has_value() || listIP->empty())
      {
         return NetworkStatus::Error_InvalidAddress;
      }

      sf::IpAddress ip = listIP->front();
      auto status = socket.connect(ip, port, sf::seconds(timeout));

      if (status == sf::Socket::Status::Done) 
      {
         return NetworkStatus::Success;
      }
      if (status == sf::Socket::Status::Error)
      {
         return NetworkStatus::Error_ServerUnavailable;
      }
      
      return NetworkStatus::Error_Disconnected;
   }
};
