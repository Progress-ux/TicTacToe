#include "menu_manager.hpp"

#include <iostream>

void MenuManager::showMainMenu()
{
   std::cout << "=== Tic Tac Toe ===\n";
   std::cout << "1. Play Single Player (under development)\n";
   std::cout << "2. Play Multi Player\n";
   std::cout << "3. Settings\n";
   std::cout << "0. Exit\n";
}

void MenuManager::showSettingsMenu()
{
}

void MenuManager::runSettingsMenu()
{
}

int MenuManager::getNumber()
{
   return 0;
}

void MenuManager::waitForEnter()
{
}
