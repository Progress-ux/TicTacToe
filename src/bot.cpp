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

int HardBot::minimax(TicTacToe& game, bool isMax, int depth, int alpha, int beta)
{
   if (game.checkWin())
   {
      return isMax ? -10 + depth : 10 - depth;
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

            int score = minimax(simGame, false, depth+1, alpha, beta);
            bestScore = std::max(bestScore, score);

            alpha = std::max(alpha, bestScore);
            if (beta <= alpha)
            {
               break;
            }
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

            int score = minimax(simGame, true, depth+1, alpha, beta);
            bestScore = std::min(bestScore, score);

            beta = std::min(beta, bestScore);
            if (beta <= alpha)
            {
               break;
            }
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

         int score = minimax(simGame, false, 1, INT_MIN, INT_MAX);
         
         if (score > bestScore) 
         {
            bestScore = score;
            bestMove = i;
         }
      }
   }
   return bestMove;
}
