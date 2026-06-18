#include "bot.hpp"
#include "random"

int EasyBot::move() const
{
   std::random_device rd;
   std::mt19937 gen(rd());

   std::uniform_int_distribution<int> distrib(0, 8);

   int random_number = distrib(gen);

   return random_number;
}

int HardBot::move() const
{
}