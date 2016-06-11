#include <iostream>
#include <fstream>

#include "tridiag.hpp"

int main(int argc, char** argv) {
  std::cout.precision(8);
  std::cout.setf(std::ios::fixed);
  std::string td_fname(argv[1]);
  std::ifstream td_in(td_fname);
  td::tridiag<double> td(td_in);
  int i = std::stoi(std::string(argv[2]));
  double row[3];
  td.copy_row(i, row);
  for (int i = 0; i < 3; ++i) std::cout << row[i] << " ";
  std::cout << std::endl;
}
