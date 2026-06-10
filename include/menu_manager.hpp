#include <string>

namespace MenuManager
{
   void showMainMenu();
   void showSettingsMenu(const std::string& serverIp, unsigned short serverPort);  

   void showSinglePlayMenu();

   void runSettingsMenu();

   int getNumber();
   void waitForEnter();
} // namespace MenuManager
