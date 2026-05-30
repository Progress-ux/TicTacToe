#include "config_manager.hpp"

#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

ConfigManager &ConfigManager::getInstance()
{
   static ConfigManager instance;
   return instance;
}

void ConfigManager::load()
{
   std::fstream file("config.json");
   if (!file.is_open())
   {
      resetToDefault();
      return;
   }
   json data = json::parse(file);
   
   serverIp = data.value("serverIp", "127.0.0.1");
   serverPort = data.value("serverPort", 53000);
   timeout = data.value("timeout", 15);
}

void ConfigManager::save()
{
}

void ConfigManager::resetToDefault()
{
   serverIp = "127.0.0.1";
   serverPort = 53000;
   timeout = 15;
}