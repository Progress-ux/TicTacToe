#include "config_manager.hpp"

#include <nlohmann/json.hpp>
#include <fstream>
#include <regex>
#include <filesystem>

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

std::string ConfigManager::getLang() const
{
   return languageFilename;
}

void ConfigManager::setLang(const std::string& filename) 
{
   languageFilename = filename;
}

void ConfigManager::load()
{
   std::filesystem::path configPath = "data/config.json";

   if (!std::filesystem::exists(configPath))
   {
      resetToDefault();

      std::error_code ec;
      std::filesystem::create_directories(configPath.parent_path(), ec);

      if (!ec) 
      {
         save();
      }
      return;
   }

   std::ifstream file(configPath);
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

   if(!data.contains("network") || !data["network"].is_object() ||
      !data.contains("language") || !data["language"].is_object())
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

   languageFilename = data["language"];
}

void ConfigManager::save()
{
   std::filesystem::path configPath = "data/config.json";

   if (!std::filesystem::exists(configPath))
   {
      std::error_code ec;
      std::filesystem::create_directories(configPath.parent_path(), ec);
   }

   std::ofstream file(configPath);
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
   
   data["language"] = languageFilename;

   file << data.dump(4) << std::endl;
}

void ConfigManager::resetToDefault()
{
   serverIp = "127.0.0.1";
   serverPort = 53000;
   timeout = 15.0;

   languageFilename = "lang/eng.json";
}