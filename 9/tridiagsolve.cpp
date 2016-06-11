#include <iostream>
#include <fstream>

#include "tridiag.hpp"
#include "doublesweep.cpp"
#include "instable.cpp"

#define SOLVER td::doublesweep

using namespace td;

int main(int argc, char** argv) {
  std::cout.precision(8);
  std::cout.setf(std::ios::fixed);
  std::string td_fname(argv[1]), d_fname(argv[2]);
  std::ifstream td_in(td_fname);
  std::ifstream d_in(d_fname);
  tridiag_aug<double> eqn(td_in, d_in);
  int n = eqn.size();
  bool verbose = false;
  if (std::find(argv, argv+argc, std::string("-v")) != argv+argc) verbose = true;
  SOLVER::solve(eqn, verbose);
  if (!eqn.diagonalized()) {
    std::cout << eqn;
  } else {
    std::cout << "$$\\begin{pmatrix}" << std::endl;
    for(int i = 0; i < n; ++i) {
      std::cout << eqn(i,n);
      if (i != n-1) std::cout << " \\\\";
      std::cout << std::endl;
    }
    std::cout << "\\end{pmatrix}$$" << std::endl;
  }
  return 0;
}
