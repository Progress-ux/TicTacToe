#include <string>
#include <vector>

#include "network.hpp"

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
   NetworkMode runGetModeMenu();

} // namespace MenuManager
