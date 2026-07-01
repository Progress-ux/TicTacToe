#pragma once

#include <string>
#include <filesystem>
#include <vector>

class SettingsMenu
{
private:
   std::string serverIp;
   unsigned short serverPort;

   std::string language;
   std::vector<std::string> langList;

   bool isChanged;
   bool isLangChanged;
   
   void show();
   
   void changeAddress();
   void changePort();

   void loadListLang();
   void showLanguageMenu();
   void runLanguageMenu();

   void getSettingsFromConfig();
   void applyChanges();

   std::string formatLanguage(std::string filename);
   std::string formatLanguage(const std::filesystem::directory_entry& filename);
   std::string eraseLang(std::string filename);
public:
   SettingsMenu();
   void run();
};