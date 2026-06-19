#include <string>
#include <vector>

namespace MenuManager
{
   void showMainMenu();
   void showSettingsMenu(const std::string& serverIp, unsigned short serverPort);  

   void showSinglePlayMenu();
   void runSinglePlayMenu();

   void showSetCurrentPlayerMenu();
   char runSetCurrentPlayerMenu();

   void runSettingsMenu();

   void fieldRendering(std::vector<char>& cells);
   void showGetModeMenu();
   char runGetModeMenu();

   int getNumber();
} // namespace MenuManager
