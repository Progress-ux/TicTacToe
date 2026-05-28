#include <iostream>
#include <vector>
#include <string>

void field_rendering(const std::vector<char>& cells) 
{
   std::cout << cells[0] << " | " << cells[1] << " | " << cells[2] << "\n";   
   std::cout << "---+---+---\n";
   std::cout << cells[3] << " | " << cells[4] << " | " << cells[5] << "\n";   
   std::cout << "---+---+---\n";
   std::cout << cells[6] << " | " << cells[7] << " | " << cells[8] << "\n";   
}

bool victory_check(const std::vector<char>& cells) 
{
   static const std::vector<std::vector<int>> winning_combinations = { 
      {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // lines
      {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // columns
      {0, 4, 8}, {2, 4, 6}             // diagonals
   };
   
   for (const std::vector<int>& combo : winning_combinations)
   {
      if (cells[combo[0]] == cells[combo[1]] && 
          cells[combo[1]] == cells[combo[2]]) 
      {
         return true;
      }
   }

   return false;
}

int main(int argc, const char** argv) {
   
   std::vector<char> cells = { '0', '1', '2', '3', '4', '5', '6', '7', '8' };
   int number_cell;
   unsigned int i = 0;
   char currentPlayer = 'x';

   while (true)
   {
      field_rendering(cells);

      if (i > 8)
      {
         std::cout << "Draw! All moves are over.\n";
         break;
      }

      std::cout << "Player [" << currentPlayer << "] enter cell(0-8): ";

      
      if (!(std::cin >> number_cell) || number_cell < 0 || number_cell > 8) 
      {
         system("clear");
         std::cout << "--- Invalid input! Please enter a number between 0 and 8.\n";
         std::cin.clear();
         std::cin.ignore(10000, '\n');
         continue;
      }
      
      if (cells[number_cell] == 'x' || cells[number_cell] == 'o')
      {
         system("clear");
         std::cout << "--- Cell " << number_cell << " is already taken!\n";
         continue;
      }
      
      cells[number_cell] = currentPlayer;

      if (victory_check(cells)) 
      {
         system("clear");
         field_rendering(cells);
         std::cout << "You [" << currentPlayer << "] won!\n";
         break;
      }

      i++;
      currentPlayer = (currentPlayer == 'x') ? 'o' : 'x';

      system("clear");
   }

   return 0;
}