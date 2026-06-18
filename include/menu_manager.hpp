#include <string>

namespace MenuManager
{
   void showMainMenu();
   void showSettingsMenu(const std::string& serverIp, unsigned short serverPort);  

   void showSinglePlayMenu();
   void runSinglePlayMenu();

   void showSetCurrentPlayerMenu();

   void runSettingsMenu();

   int getNumber();
} // namespace MenuManager
