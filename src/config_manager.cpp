#include "config_manager.hpp"

ConfigManager &ConfigManager::getInstance()
{
   static ConfigManager instance;
   return instance;
}

ConfigManager::~ConfigManager()
{
}

void ConfigManager::load()
{
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