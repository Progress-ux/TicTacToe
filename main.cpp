#include <iostream>
#include <vector>
#include <string>

void field_rendering() 
{
   std::vector<char> cells = { '1', '2', '3', '4', '5', '6', '7', '8', '9', };

   std::cout << cells[0] << " | " << cells[1] << " | " << cells[2] << "\n";   
   std::cout << "---+---+---\n";
   std::cout << cells[3] << " | " << cells[4] << " | " << cells[5] << "\n";   
   std::cout << "---+---+---\n";
   std::cout << cells[6] << " | " << cells[7] << " | " << cells[8] << "\n";   
}

int main(int argc, const char** argv) {
   
   field_rendering();
   
   return 0;
}