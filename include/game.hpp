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

   bool checkWin();
   bool checkDraw();

   bool canMove(int index);
   void move(int index);

   char getCurrentPlayer();
   void setCurrentPlayer(char currentPlayer);

   void switchPlayer();

   std::vector<char>& getCells();
};