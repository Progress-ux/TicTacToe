#include "config_manager.hpp"

ConfigManager &ConfigManager::getInstance()
{
   static ConfigManager instance;
   return instance;
}

ConfigManager::~ConfigManager()
{
}
