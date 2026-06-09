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
      save();
      return;
   }
   json data = json::parse(file);

   if(!data.contains("network") || !data["network"].is_object())
   {
      resetToDefault();
      return;
   }

   const auto& network = data["network"];

   serverIp = network.value("serverIp", "127.0.0.1");
   serverPort = network.value("serverPort", 53000);
   timeout = network.value("timeout", 15.0);
}

void ConfigManager::save()
{
   std::ofstream file("config.json");
   if (!file.is_open())
   {
      throw std::runtime_error("Error: Could not save config");
   }

   json data;
   data["network"]["serverIp"] = serverIp;
   data["network"]["serverPort"] = serverPort;
   data["network"]["timeout"] = timeout;

   file << data.dump(4) << std::endl;
}

void ConfigManager::resetToDefault()
{
   serverIp = "127.0.0.1";
   serverPort = 53000;
   timeout = 15.0;
}