#include <iostream>
#include <fstream>
#include <numeric>

#include "tridiag.hpp"
#include "doublesweep.cpp"
#include "instable.cpp"

#define SOLVER td::doublesweep

int main(int argc, char** argv) {
  bool verbose = false;
  if (std::find(argv, argv+argc, std::string("-v")) != argv+argc) verbose = true;
  std::cout.precision(8);
  std::cout.setf(std::ios::fixed);
  std::string td_fname(argv[1]), d_fname(argv[2]);
  std::ifstream td_in(td_fname);
  std::ifstream d_in(d_fname);
  td::tridiag_aug<double> eqn(td_in, d_in);
  int n = eqn.size();
  std::vector<double> ans;
  ans.reserve(n);
  for (int i = 0; i < n; ++i) {
    double v;
    std::cin >> v;
    ans.push_back(v);
  }
  SOLVER::solve(eqn, verbose);
  std::vector<double> d(n);
  for (int i = 0; i < n; ++i) {
    d[i] = ans[i] - eqn(i,n);
    if (d[i] < 0) d[i] *= -1;
  }
  td::print_vector(std::cout, d, "d");
  std::cout << "$$\\sum_{j=1}^n d_j^2 = "\
     << std::accumulate(d.begin(), d.end(), .0, [](double x, double y){ return x + y*y; }) \
     << "$$" << std::endl;
  return 0;
}
