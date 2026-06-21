#include "settings_menu.hpp"

#include "config_manager.hpp"
#include "input_manager.hpp"

#include <iostream>

void SettingsMenu::show() const
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

void SettingsMenu::changeAddress()
{
   std::string new_address;
   while(true)
   {
      std::cout << "New address: ";
      InputManager::getUserInput(new_address, "--- Invalid input! Please enter new IP");

      if (!ConfigManager::validationServerIp(new_address))
      {
         std::cout << "\n--- Invalid input! Please enter new IP\n\n";
         continue;
      }
      break;
   }

   serverIp = new_address;
   isChanged = true;
}

void SettingsMenu::changePort()
{
   unsigned short new_port;
   while (true)
   {
      std::cout << "New port: ";
      int value = InputManager::getNumber();

      if (!ConfigManager::getInstance().validationServerPort(value))
      {
         std::cout << "--- Port must be between 0 and 65535!\n";
         continue;
      }

      new_port = static_cast<unsigned short>(value);
      break;
   }
   serverPort = new_port;
   isChanged = true;
}

void SettingsMenu::getSettingsFromConfig() 
{
   serverIp = ConfigManager::getInstance().getServerIp();
   serverPort = ConfigManager::getInstance().getServerPort();
}

void SettingsMenu::applyChanges() 
{
   ConfigManager::getInstance().setServerIp(serverIp);
   ConfigManager::getInstance().setServerPort(serverPort);
   ConfigManager::getInstance().save();
}

void SettingsMenu::run()
{
   getSettingsFromConfig();
   while (true)
   {
      InputManager::clearScreen();
      show();

      int number = InputManager::getNumber();

      switch (number)
      {
      case 1: // Change address
         changeAddress();
         break;
         
      case 2: // Change port
         changePort();
         break;

      case 3: // Change username
      {
         // TODO: Add new parameter to ConfigManager: username
         break;
      }

      case 4: // Change language
      {
         // TODO: Add new parameter to ConfigManager: language
         break;
      }

      case 5: // Save Settings
      {
         if(!isChanged)
            break;
         
         std::cout << "Are you sure you want to save the settings? [y/N]: ";
         
         if(InputManager::getYesOrNot() != 'y')
         {
            std::cout << "Settings not saved!\n";
            InputManager::waitForEnter();
            break;
         }
         applyChanges();
         
         std::cout << "Settings saved successfully!\n";
         isChanged = false;
         InputManager::waitForEnter();

         break;
      }

      case 6: // Reset changes
      {
         if(!isChanged)
            break;
         
         std::cout << "Are you sure you want to reset the changes? [y/N]: ";
         if(InputManager::getYesOrNot() != 'y')
            break;
         
         getSettingsFromConfig();

         isChanged = false;

         std::cout << "Settings changes reset\n";
         InputManager::waitForEnter();

         break;
      }

      case 7: // Reset settings to default
      {
         std::cout << "Are you sure you want to reset your settings to default values? [y/N]: ";
         if(InputManager::getYesOrNot() != 'y')
            break;
         
         ConfigManager::getInstance().resetToDefault();

         getSettingsFromConfig();

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
            if(InputManager::getYesOrNot() != 'y')
               break;
         }
         return;
      }
      default:
         std::cout << "--- Invalid input! Please enter a number from the list\n";
         break;
      }
   }
}