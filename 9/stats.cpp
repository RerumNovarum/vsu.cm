#include <iostream>
#include <fstream>
#include <numeric>
#include <random>

#include "tridiag.hpp"
#include "doublesweep.cpp"
#include "instable.cpp"

#define SOLVER td::doublesweep

struct testpair {
  testpair() {}
  explicit testpair(td::tridiag_aug<double>& eqn, std::vector<double>& sol) {
    this->eqn = eqn;
    this->sol = sol;
  }
  td::tridiag_aug<double> eqn;
  std::vector<double> sol;
};

testpair random_eqn(int n) {
  static std::default_random_engine rng;
  std::bernoulli_distribution bern(0.5);
  std::uniform_int_distribution<int> dd(0, n);
  std::uniform_real_distribution<double> dcont(-1.0, 1.0);

  td::tridiag_aug<double> t(n);
  std::vector<double> sol(n);
  for (int i = 0; i < n; ++i) { 
    t(i,i) = 1;
    t(i,n) = dcont(rng);
    sol[i] = t(i,n);
  }
  if (n < 2) return testpair(t,sol);

  for (int iter = 0; iter < n; ++iter) {
    for (int s = 0; s < n; ++s) {
      int i1 = dd(rng);
      bool up = bern(rng);
      int i2 = up ? i1 - 1 : i1 + 1;
      double alpha = dcont(rng);
      t.row_try_add(i1, i2, alpha);
    }
  }
  return testpair(t,sol);
}

int main(int argc, char** argv) {
  std::cout << std::fixed;
  std::cout.precision(32);
  int n = std::stoi(argv[1]);
  int k = std::stoi(argv[2]);
  for (int i = 0; i < k; ++i) {
    testpair tp = random_eqn(n);
    SOLVER::solve(tp.eqn);
    for(int i = 0; i < n; ++i) {
      double d = tp.eqn(i,n) - tp.sol[i];
      if (d < 0) d *= -1;
      std::cout << d;
      if (i != n-1) std::cout << ", ";
    }
    std::cout << std::endl;
  }
  return 0;
}
