#pragma once

#include <string>

class ConfigManager
{
private:
   std::string serverIp;
   unsigned short serverPort;
   float timeout;

   ConfigManager() = default;
public:
   ConfigManager(const ConfigManager&) = delete;
   ConfigManager& operator=(const ConfigManager&) = delete;
   ~ConfigManager();

   static ConfigManager& getInstance();

   std::string getServerIp() const { return serverIp; }
   void setServerIp(const std::string& ip) { serverIp = ip; }

   unsigned short getServerPort() const { return serverPort; }
   void setServerPort(unsigned short port) { serverPort = port; }

   float getTimeout() const { return timeout; }
   void setTimeout(float timeout) { this->timeout = timeout; }
};

