#include <iostream>
#include <fstream>

#include "tridiag.hpp"

int main(int argc, char** argv) {
  std::cout.precision(8);
  std::cout.setf(std::ios::fixed);
  std::string td_fname(argv[1]);
  std::ifstream td_in(td_fname);
  td::tridiag<double> td(td_in);
  for (int i = 2; i < argc; i += 3) {
    int
      i1 = std::stoi(std::string(argv[i])),
      i2 = std::stoi(std::string(argv[i+1]));
    double alpha = std::stof(std::string(argv[i+2]));
    td.row_try_add(i1, i2, alpha);
  }
  std::cout << td;
}
