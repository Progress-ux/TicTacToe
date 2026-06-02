#include "game_modes.hpp"
#include "config_manager.hpp"
#include "input_manager.hpp"
#include <limits>
#include <iostream>

void displayMainMenu()
{
   std::cout << "=== Tic Tac Toe ===\n";
   std::cout << "1. Play Single Player (under development)\n";
   std::cout << "2. Play Multi Player\n";
   std::cout << "3. Settings\n";
   std::cout << "0. Exit\n";
}

void displaySettingsMenu(const std::string& serverIp, unsigned short serverPort)
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

int getNumber()
{
   int number;
   while (true) 
   {
      if (std::cin >> number) 
      {
         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
         return number;
      }

      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "--- Invalid input! Please enter a valid number: ";
   }
   
   return number;
}

char getYesOrNot()
{
   char result;
   
   std::cin.get(result);

   if (result == '\n') {
      return 'n'; 
   }

   if (result != '\n') {
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
   }

   if (result == 'y' || result == 'Y') {
      return 'y';
   }
   
   return 'n';
}

void waitForEnter()
{
   std::cout << "\nPress Enter to continue...";
   std::cin.get();
}

void settingsMenu()
{
   bool isRunningSettingsMenu = true;

   bool isChanged = false;

   std::string address = ConfigManager::getInstance().getServerIp();
   unsigned short port = ConfigManager::getInstance().getServerPort();

   while (isRunningSettingsMenu)
   {
      InputManager::clearScreen();

      displaySettingsMenu(address, port);

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
         std::cout << "New address: ";
         std::cin >> address;
         isChanged = true;
         break;
      }
         
      case 2:
      {
         while (true)
         {
            std::cout << "New port: ";
            if (!(std::cin >> port))
            {
               std::cin.clear();
               std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
               std::cout << "\n--- Invalid input! Please enter new port\n\n";
               continue;
            }
            break;
         }
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
            waitForEnter();
            break;
         }

         ConfigManager::getInstance().setServerIp(address);
         ConfigManager::getInstance().setServerPort(port);
         ConfigManager::getInstance().save();

         std::cout << "Settings saved successfully!\n";
         isChanged = false;
         waitForEnter();

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
         waitForEnter();

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
         waitForEnter();

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

int main(int argc, const char** argv) 
{
   ConfigManager::getInstance().load();
   bool isRunningGame = true;
            

   while(isRunningGame)
   {
      InputManager::clearScreen();
      displayMainMenu();
      int number = getNumber();

      if (number > 3 || number < 0)
      {
         std::cout << "--- Invalid input! Please enter a number from the list\n";
         waitForEnter();
         continue;
      }

      switch (number)
      {
      case 1: // Single game
         {
            // TODO: Create a single-player game with two difficulty levels to choose from
            break;
         }
      case 2: // Multiplayer game
         {
            InputManager::clearScreen();
            GameMode::runMultiplayerGame();
            break;
         }
      case 3: // Settings menu
         {
            settingsMenu();
            break;
         }
      case 0: // Exit
         {
            isRunningGame = false;
            break;
         }
      
      default:
         break;
      }
   }

   return 0;
}