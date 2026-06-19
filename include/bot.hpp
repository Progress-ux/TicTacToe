#include <random>
#include "game.hpp"

class EasyBot;
class HardBot;

class Bot {
public:
   virtual ~Bot() = default;

   virtual int move(TicTacToe game) = 0;
};

class EasyBot : public Bot {
private: 
   std::uniform_int_distribution<int> distrib;
   std::mt19937 gen;

public:
   EasyBot() : gen(std::random_device{}()), distrib(0, 8) {}

   int move(TicTacToe game) override;
};

class HardBot : public Bot {
public:
   int move(TicTacToe game) override;

};