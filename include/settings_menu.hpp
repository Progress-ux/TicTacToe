#pragma once
#include <string>

class SettingsMenu
{
private:
   std::string serverIp;
   unsigned short serverPort;
   bool isChanged;

   void show() const;
   void changeAddress();
   void changePort();
   void getSettingsFromConfig();
   void applyChanges();

public:
   SettingsMenu();
   void run();
};