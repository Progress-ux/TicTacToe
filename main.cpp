#include <iostream>
#include <vector>
#include <string>

void field_rendering(std::vector<char>& cells) 
{
   std::cout << cells[0] << " | " << cells[1] << " | " << cells[2] << "\n";   
   std::cout << "---+---+---\n";
   std::cout << cells[3] << " | " << cells[4] << " | " << cells[5] << "\n";   
   std::cout << "---+---+---\n";
   std::cout << cells[6] << " | " << cells[7] << " | " << cells[8] << "\n";   
}

char enter_cell()
{
   char number_cell;

   std::cout << "Enter number cell: ";
   std::cin >> number_cell;

   return number_cell;
}

int main(int argc, const char** argv) {
   
   std::vector<char> cells = { '0', '1', '2', '3', '4', '5', '6', '7', '8' };
   char number_cell;
   
   field_rendering(cells);
   number_cell = enter_cell();

   return 0;
}