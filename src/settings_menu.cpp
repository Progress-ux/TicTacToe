#include "settings_menu.hpp"

#include "config_manager.hpp"
#include "input_manager.hpp"
#include "language_manager.hpp"

#include <string>
#include <iostream>

void SettingsMenu::show() const
{
   std::cout << Loc::get("settings_menu.title") << "\n\n";
   
   std::cout << Loc::get("settings_menu.address") << " " << serverIp << "\n";
   std::cout << Loc::get("settings_menu.port") << " " << serverPort << "\n";

   std::cout << Loc::get("settings_menu.username") << " -- under development --\n";
   std::cout << Loc::get("settings_menu.language") << " " << "\n\n";

   std::cout << Loc::get("settings_menu.change_addr") << "\n";
   std::cout << Loc::get("settings_menu.change_port") << "\n\n";

   std::cout << Loc::get("settings_menu.change_username") << "\n";
   std::cout << Loc::get("settings_menu.change_lang") << "\n\n";

   std::cout << Loc::get("settings_menu.save") << "\n";
   std::cout << Loc::get("settings_menu.reset_changes_menu") << "\n";
   std::cout << Loc::get("settings_menu.reset_to_def_menu") << "\n\n";
   std::cout << Loc::get("settings_menu.back") << "\n";
}

void SettingsMenu::changeAddress()
{
   std::string new_address;
   while(true)
   {
      std::cout << Loc::get("settings_menu.new_addr") << " ";
      InputManager::getUserInput(new_address, Loc::get("errors.addr_error_input"));

      if (!ConfigManager::validationServerIp(new_address))
      {
         std::cout << "\n" << Loc::get("errors.addr_error_input") << "\n\n";
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
      std::cout << Loc::get("settings_menu.new_port") << " ";
      int value = InputManager::getNumber();

      if (!ConfigManager::getInstance().validationServerPort(value))
      {
         std::cout << Loc::get("errors.port_error_input") << "\n";
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

SettingsMenu::SettingsMenu() : isChanged{false}
{
}

void SettingsMenu::run()
{
   getSettingsFromConfig();
   while (true)
   {
      InputManager::clearScreen();
      show();

      std::cout << Loc::get("input.enter_choice") << " ";
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
         
         std::cout << Loc::get("settings_menu.save_setting") << " ";
         
         if(InputManager::getYesOrNot() != 'y')
         {
            std::cout << Loc::get("settings_menu.settings_not_saved") << "\n";
            InputManager::waitForEnter();
            break;
         }
         applyChanges();
         
         std::cout << Loc::get("settings_menu.saved_success") << "\n";
         isChanged = false;
         InputManager::waitForEnter();

         break;
      }

      case 6: // Reset changes
      {
         if(!isChanged)
            break;
         
         std::cout << Loc::get("settings_menu.reset_changes_mes") << " ";
         if(InputManager::getYesOrNot() != 'y')
            break;
         
         getSettingsFromConfig();

         isChanged = false;

         std::cout << Loc::get("settings_menu.changes_reset_success") << "\n";
         InputManager::waitForEnter();

         break;
      }

      case 7: // Reset settings to default
      {
         std::cout << Loc::get("settings_menu.reset_to_def_mes") << " ";
         if(InputManager::getYesOrNot() != 'y')
            break;
         
         ConfigManager::getInstance().resetToDefault();

         getSettingsFromConfig();

         isChanged = false;

         std::cout << Loc::get("settings_menu.reset_to_def_success") << "\n";
         InputManager::waitForEnter();

         break;
      }

      case 0:
      {
         if(isChanged)
         {
            std::cout << Loc::get("settings_menu.unsaved_settings") << " ";
            if(InputManager::getYesOrNot() != 'y')
               break;
         }
         return;
      }
      default:
         std::cout << Loc::get("errors.enter_number_from_list") << "\n";
         break;
      }
   }
}