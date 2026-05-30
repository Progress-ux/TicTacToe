#pragma once

#include <string>

class ConfigManager
{
private:
   std::string serverIp;
   unsigned short serverPort;

   ConfigManager() = default;
public:
   ConfigManager(const ConfigManager&) = delete;
   ConfigManager& operator=(const ConfigManager&) = delete;

   static ConfigManager& getInstance();

   ~ConfigManager();
};

