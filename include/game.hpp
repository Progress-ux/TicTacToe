#pragma once

#include<vector>

class TicTacToe 
{
private:
   std::vector<char> cells;
   char currentPlayer;
   unsigned int moveCount;

public:
   TicTacToe();

   void field_rendering();

   bool checkWin();
   bool checkDraw();

   bool canMove(int index);
   void move(int index);

   char getCurrentPlayer();
   void switchPlayer();
};