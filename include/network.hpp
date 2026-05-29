#pragma once 
#include <SFML/Network.hpp>
#include <string>

class NetworkManager 
{
protected: 
   sf::TcpSocket socket;
public:
   virtual ~NetworkManager() = default;

   void sendMove(int index) 
   {
      sf::Packet packet;
      packet << index;
      socket.send(packet);
   }
   int receiveMove()
   {
      sf::Packet packet;
      if (socket.receive(packet) == sf::Socket::Status::Done) 
      {
         int index;
         packet >> index;
         return index;
      }
      return -1;
   }
};

class Server : public NetworkManager
{
private:
   sf::TcpListener listener;
public:
   bool start(unsigned short port)
   {
      if (listener.listen(port) != sf::Socket::Status::Done) return false;
      return listener.accept(socket) == sf::Socket::Status::Done;
   }

};

class Client : public NetworkManager
{
public:
   bool connect(const std::string& ipString, unsigned short port, float timeout) 
   {
      sf::IpAddress ip = sf::IpAddress::resolve(ipString).value_or(sf::IpAddress::Any);
      return socket.connect(ip, port, sf::seconds(timeout)) == sf::Socket::Status::Done;
   }

};