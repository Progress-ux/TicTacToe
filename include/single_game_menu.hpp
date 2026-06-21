#pragma once

#include "bot.hpp"

class SingleGameMenu
{
private:
   char player;   
   BotDifficulty difficulty;

   void showSelectDifficultyMenu() const;
   void showSelectPlayerMenu() const;
   void runSelectPlayerMenu();
   void runGame();
public:
   void runPlayMenu();
};