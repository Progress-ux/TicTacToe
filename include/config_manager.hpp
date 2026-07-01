#pragma once

#include <string>
#include <filesystem>

class ConfigManager
{
private:
   std::string serverIp;
   unsigned short serverPort;
   float timeout;

   std::filesystem::path languageFolder;
   std::string languageFilename;

   ConfigManager() = default;
public:
   ConfigManager(const ConfigManager&) = delete;
   ConfigManager& operator=(const ConfigManager&) = delete;

   static ConfigManager& getInstance();

   static bool validationServerIp(const std::string& ip);
   static bool validationServerPort(int port);

   std::string getServerIp() const { return serverIp; }
   void setServerIp(const std::string& ip) { serverIp = ip; }

   unsigned short getServerPort() const { return serverPort; }
   void setServerPort(unsigned short port) { serverPort = port; }

   float getTimeout() const { return timeout; }
   void setTimeout(float timeout) { this->timeout = timeout; }

   std::filesystem::path getLangFolder() const;
   void setLangFolder(const std::filesystem::path& folder);

   std::string getLang() const;
   void setLang(const std::string& filename);

   void load();
   void save();
   void resetToDefault();
};

