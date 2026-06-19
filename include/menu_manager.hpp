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

   int getNumber();
} // namespace MenuManager
