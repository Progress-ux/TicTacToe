#include "menu_manager.hpp"

#include <iostream>
#include <limits>

namespace 
{
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
}

namespace MenuManager
{
   void showMainMenu()
   {
      std::cout << "=== Tic Tac Toe ===\n";
      std::cout << "1. Play Single Player (under development)\n";
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
   
   void runSettingsMenu()
   {
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
   
   void waitForEnter()
   {
   }
} // namespace MenuManager


