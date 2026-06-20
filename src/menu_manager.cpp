#include "menu_manager.hpp"

#include "config_manager.hpp"
#include "input_manager.hpp"
#include "game_modes.hpp"

#include <iostream>
#include <limits>

namespace 
{
   char getYesOrNot()
   {
      std::string line;
      if(!std::getline(std::cin, line))
      {
         return 'n';
      }

      line.erase(0, line.find_first_not_of(" \t\n\r"));
      line.erase(line.find_last_not_of(" \t\n\r") + 1);

      if (line.empty()) return 'n';

      char first = std::tolower(line[0]);
      return (first == 'y') ? 'y' : 'n';
   }
}

namespace MenuManager
{
   void showMainMenu()
   {
      std::cout << "=== Tic Tac Toe ===\n";
      std::cout << "1. Play Single Player\n";
      std::cout << "2. Play Multi Player\n";
      std::cout << "3. Settings\n";
      std::cout << "0. Exit\n";
   }
   
   void showSettingsMenu(const std::string& serverIp, unsigned short serverPort)
   {
      std::cout << "=== Settings ===\n\n";
   
      std::cout << "Address(IP): " << serverIp << "\n";
      std::cout << "Port: " << serverPort << "\n";
   
      std::cout << "Name user profile: " << "-- under development --\n";
      std::cout << "Language: " << "-- under development --\n\n";
   
      std::cout << "1. Change address\n";
      std::cout << "2. Change port\n\n";
   
      std::cout << "3. Change Username\n";
      std::cout << "4. Change language\n\n";
   
      std::cout << "5. Save settings\n";
      std::cout << "6. Reset changes\n";
      std::cout << "7. Reset settings to default\n\n";
      std::cout << "0. Back\n";
   }

   void showSinglePlayMenu()
   {
      std::cout << "=== Single Player ===\n\n";

      std::cout << "Select bot difficulty:\n";
      std::cout << "1. Easy bot\n";
      std::cout << "2. Hard bot\n";
      
      std::cout << "\n0. Back\n";
   }

   void runSinglePlayMenu()
   {
      bool isRunningSinglePlayMenu = true;

      while (isRunningSinglePlayMenu)
      {
         InputManager::clearScreen();

         showSinglePlayMenu();
         int number = getNumber();

         switch (number)
         {
         case 1:
            GameMode::runSingleGame(BotDifficulty::Easy);
            break;
         
         case 2:
            GameMode::runSingleGame(BotDifficulty::Hard);
            break;

         case 0: 
            isRunningSinglePlayMenu = false;
            break;
         
         default:
            break;
         }   
      }
      
   }

   void showSetCurrentPlayerMenu()
   {
      std::cout << "=== Select a player ===\n\n";
      std::cout << "1. Player - [x]\n";
      std::cout << "2. Player - [o]\n";
      std::cout << "0. Back\n\n";
   }

   char runSetCurrentPlayerMenu()
   {
      bool isRunningSetCurrentPlayerMenu = true;

      while (isRunningSetCurrentPlayerMenu)
      {
         InputManager::clearScreen();
         
         showSetCurrentPlayerMenu();
         int number = getNumber();

         switch (number)
         {
         case 1: return 'x';
         
         case 2: return 'o';

         case 0: return 'e';

         default: 
            std::cout << "Choose one of the options!\n";
            InputManager::waitForEnter();
            continue;
         }
      }
      return 'e';
   }

   int getNumber()
   {

      std::string line;
      while (true) 
      {
         std::cout << "Enter choice: ";
         if (!std::getline(std::cin, line))
         {
            std::cout << "--- Invalid input! Please enter a valid number!\n";
            continue;
         }

         line.erase(0, line.find_first_not_of(" \t\n\r"));
         line.erase(line.find_last_not_of(" \t\n\r") + 1);

         if (line.empty())
         {
            std::cout << "--- Input cannot be empty!\n";
            continue;
         }

         try
         {
            size_t pos;
            int number = std::stoi(line, &pos);
            
            if (!(pos == line.length()))
            {
               std::cout << "--- Invalid characters after number: '" << line.substr(pos) << "'\n";
               continue;
            }

            return number;

         } catch(const std::invalid_argument& e) {
            std::cout << "--- Not a number! Please enter a number from the menu list.\n";
         } catch(const std::out_of_range& e) {
            std::cout << "--- Number is too large!\n";
         } catch(const std::exception& e) {
            std::cout << "--- Unexpected error: " << e.what() << "\n";
         }
      }
   }

   void showGetModeMenu()
   {
      std::cout << "=== Server or Client mode ===\n\n";

      std::cout << "Select mode:\n";
      std::cout << "1. Server\n";
      std::cout << "2. Client\n";
      
      std::cout << "\n0. Back\n";
   }

   char runGetModeMenu()
   {
      bool isRunningGetModeMenu = true;

      while (isRunningGetModeMenu)
      {
         InputManager::clearScreen();
         
         showGetModeMenu();
         int number = getNumber();

         switch (number)
         {
         case 1: return 's';
         
         case 2: return 'c';

         case 0: return 'e';

         default: 
            std::cout << "Choose one of the options!\n";
            InputManager::waitForEnter();
            continue;
         }
      }
      return 'e';
   }

   void runSettingsMenu()
   {
      bool isRunningSettingsMenu = true;

      bool isChanged = false;

      std::string address = ConfigManager::getInstance().getServerIp();
      unsigned short port = ConfigManager::getInstance().getServerPort();

      while (isRunningSettingsMenu)
      {
         InputManager::clearScreen();

         showSettingsMenu(address, port);

         int number = getNumber();
         if (number > 7 || number < 0)
         {
            std::cout << "--- Invalid input! Please enter a number from the list\n";
            continue;
         }

         switch (number)
         {
         case 1:
         {
            std::string new_address;
            while(true)
            {
               std::cout << "New address: ";

               if (!std::getline(std::cin, new_address))
               {
                  std::cout << "--- Invalid input! Please enter new IP\n";
                  continue;
               }

               new_address.erase(0, new_address.find_first_not_of(" \t\n\r"));
               new_address.erase(new_address.find_last_not_of(" \t\n\r") + 1);
               
               if(new_address.empty())
               {
                  std::cout << "--- Input cannot be empty!\n";
                  continue;
               }

               if (!ConfigManager::validationServerIp(new_address))
               {
                  std::cout << "\n--- Invalid input! Please enter new IP\n\n";
                  continue;
               }
               break;
            }

            address = new_address;
            isChanged = true;
            break;
         }
            
         case 2:
         {
            std::string line;
            unsigned short new_port;
            while (true)
            {
               std::cout << "New port: ";
               if(!std::getline(std::cin, line))
               {
                  std::cout << "--- Invalid input! Please enter new port\n";
                  continue;
               }
               
               line.erase(0, line.find_first_not_of(" \t\n\r"));
               line.erase(line.find_last_not_of(" \t\n\r") + 1);

               if (line.empty())
               {
                  std::cout << "--- Input cannot be empty!\n";
                  continue;
               }

               try
               {
                  size_t pos;
                  int value = std::stoi(line, &pos);
                  
                  if (!(pos == line.length()))
                  {
                     std::cout << "--- Invalid characters after number: '" << line.substr(pos) << "'\n";
                     continue;
                  }

                  if (value < 0 || value > 65535)
                  {
                     std::cout << "--- Port must be between 0 and 65535!\n";
                     continue;
                  }

                  new_port = static_cast<unsigned short>(value);

               } catch(const std::invalid_argument& e) {
                  std::cout << "--- Not a number! Please enter a number from the menu list.\n";
                  continue;
               } catch(const std::out_of_range& e) {
                  std::cout << "--- Number is too large!\n";
                  continue;
               } catch(const std::exception& e) {
                  std::cout << "--- Unexpected error: " << e.what() << "\n";
                  continue;
               }
               break;
            }
            port = new_port;
            isChanged = true;
            break;
         }

         case 3:
         {
            // TODO: Add new parameter to ConfigManager: username
            break;
         }

         case 4:
         {
            // TODO: Add new parameter to ConfigManager: language
            break;
         }

         case 5:
         {
            if(!isChanged)
               break;
            
            std::cout << "Are you sure you want to save the settings? [y/N]: ";
            
            if(getYesOrNot() != 'y')
            {
               std::cout << "Settings not saved!\n";
               InputManager::waitForEnter();
               break;
            }

            ConfigManager::getInstance().setServerIp(address);
            ConfigManager::getInstance().setServerPort(port);
            ConfigManager::getInstance().save();

            std::cout << "Settings saved successfully!\n";
            isChanged = false;
            InputManager::waitForEnter();

            break;
         }

         case 6:
         {
            if(!isChanged)
               break;
            
            std::cout << "Are you sure you want to reset the changes? [y/N]: ";
            if(getYesOrNot() != 'y')
               break;
            
            address = ConfigManager::getInstance().getServerIp();
            port = ConfigManager::getInstance().getServerPort();

            isChanged = false;

            std::cout << "Settings changes reset\n";
            InputManager::waitForEnter();

            break;
         }

         case 7:
         {
            std::cout << "Are you sure you want to reset your settings to default values? [y/N]: ";
            if(getYesOrNot() != 'y')
               break;
            
            ConfigManager::getInstance().resetToDefault();

            address = ConfigManager::getInstance().getServerIp();
            port = ConfigManager::getInstance().getServerPort();
            isChanged = false;

            std::cout << "Settings reset to default\n";
            InputManager::waitForEnter();

            break;
         }

         case 0:
         {
            if(isChanged)
            {
               std::cout << "All unsaved settings will be reset. Are you sure you want to exit? [y/N]: ";
               if(getYesOrNot() != 'y')
                  break;
            }
            isRunningSettingsMenu = false;
            break;
         }
         default:
            break;
         }
      }
      
   }
   
   void fieldRendering(std::vector<char>& cells)
   {
      std::cout << " " << cells[0] << " | " << cells[1] << " | " << cells[2] << "\n";   
      std::cout << "---+---+---\n";
      std::cout << " "  << cells[3] << " | " << cells[4] << " | " << cells[5] << "\n";   
      std::cout << "---+---+---\n";
      std::cout << " "  << cells[6] << " | " << cells[7] << " | " << cells[8] << "\n"; 
   }

} // namespace MenuManager


