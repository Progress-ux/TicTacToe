#include "config_manager.hpp"

#include <nlohmann/json.hpp>
#include <fstream>
#include <regex>

using json = nlohmann::json;

ConfigManager &ConfigManager::getInstance()
{
   static ConfigManager instance;
   return instance;
}

bool ConfigManager::validationServerIp(const std::string& ip)
{
   std::regex ip_regex(R"(\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3})");
   return std::regex_match(ip, ip_regex);
}

bool ConfigManager::validationServerPort(int port)
{
   return port > 0 && port <= 65535; 
}


void ConfigManager::load()
{
   std::ifstream file("config.json");
   if (!file.is_open())
   {
      resetToDefault();
      save();
      return;
   }

   json data;
   try 
   {
      data = json::parse(file);
   }
   catch (json::parse_error& e)
   {
      file.close();
      resetToDefault();
      save();
      return;
   }

   if(!data.contains("network") || !data["network"].is_object())
   {
      resetToDefault();
      return;
   }

   const auto& network = data["network"];

   std::string tempServerIp = network.value("serverIp", "127.0.0.1");
   int tempServerPort = network.value("serverPort", 53000);

   if (!validationServerIp(tempServerIp))
   {
      resetToDefault();
      save();
      throw std::runtime_error("Incorrect server IP, please check config");
   }

   if (!validationServerPort(tempServerPort))
   {
      resetToDefault();
      save();
      throw std::runtime_error("Incorrect server Port, please check config");
   }

   serverIp = tempServerIp;
   serverPort = static_cast<unsigned short>(tempServerPort);
   timeout = network.value("timeout", 15.0);

}

void ConfigManager::save()
{
   std::ofstream file("config.json");
   if (!file.is_open())
   {
      throw std::runtime_error("Error: Could not save config");
   }

   if (!validationServerIp(serverIp))
   {
      throw std::runtime_error("Incorrect server IP");
   }

   if (!validationServerPort(serverPort))
   {
      throw std::runtime_error("Incorrect server Port");
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