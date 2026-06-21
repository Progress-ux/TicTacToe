#include <string>
#include <vector>

#include "network.hpp"

namespace MenuManager
{
   void showMainMenu();
   
   void showSinglePlayMenu();
   void runSinglePlayMenu();

   void showSetCurrentPlayerMenu();
   char runSetCurrentPlayerMenu();

   void fieldRendering(std::vector<char>& cells);
   void showGetModeMenu();
   NetworkMode runGetModeMenu();

} // namespace MenuManager
