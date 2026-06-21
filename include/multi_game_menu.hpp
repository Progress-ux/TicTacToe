#pragma once

#include "network.hpp"

class MultiGameMenu
{
private:
   NetworkMode mode;
   void runGame();
   void showSelectNetworkModeMenu();
public:
   void runPlayMenu();
};