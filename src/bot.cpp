#include "bot.hpp"
#include <algorithm>
#include <climits>

int EasyBot::move(TicTacToe game)
{
   while (true)
   {
      int m = distrib(gen);
      if (game.canMove(m)) return m;  
   }
}

int HardBot::minimax(TicTacToe& game, bool isMax)
{
   if (game.checkWin())
   {
      return isMax ? -10 : 10;
   }
   if (game.checkDraw())
   {
      return 0;
   }

   if (isMax) 
   {
      int bestScore = INT_MIN;

      for (int i = 0; i < 9; i++)
      {
         if (game.canMove(i))
         {
            TicTacToe simGame = game;
            simGame.move(i);
            simGame.switchPlayer();

            int score = minimax(simGame, false);
            bestScore = std::max(bestScore, score);
         }
      }
      return bestScore;
   }
   else 
   {
      int bestScore = INT_MAX;
      for (int i = 0; i < 9; i++)
      {
         if (game.canMove(i))
         {
            TicTacToe simGame = game;
            simGame.move(i);
            simGame.switchPlayer();

            int score = minimax(simGame, true);
            bestScore = std::min(bestScore, score);
         }
      }
      return bestScore;
   }
}

int HardBot::move(TicTacToe game)
{
   int bestScore = INT_MIN;
   int bestMove = -1;

   for (int i = 0; i < 9; i++)
   {
      if (game.canMove(i))
      {
         TicTacToe simGame = game;
         simGame.move(i);
         simGame.switchPlayer();

         int score = minimax(simGame, false);
         
         if (score > bestScore) 
         {
            bestScore = score;
            bestMove = i;
         }
      }
   }
   return bestMove;
}
