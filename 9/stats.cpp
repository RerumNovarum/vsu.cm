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

testpair random_well_eqn(int n) {
  static std::default_random_engine rng;
  std::bernoulli_distribution bern(0.5);
  std::uniform_int_distribution<int> dd(0, n);
  std::uniform_real_distribution<double> dcont(-1.0, 1.0);

  td::tridiag_aug<double> t(n);
  std::vector<double> sol(n);
  for (int i = 0; i < n; ++i) { 
    t(i,i) = dcont(rng);
    double tii = t(i,i)*1e-6;
    if (tii < 0) tii *= -1;
    std::uniform_real_distribution<double> sec(-tii, tii);
    if (i > 0) {
      t(i,i-1) = sec(rng);
      tii -= (t(i,i-1) > 0 ? t(i, i-1) : -t(i, i-1)) * 1e-6;
      sec = std::uniform_real_distribution<double>(-tii, tii);
    }
    if (i < n-1) t(i,i+1) = sec(rng);
    t(i,n) = t(i,i-1) + t(i,i) + t(i,i+1);
    sol[i] = 1;
  }
  if (n < 2) return testpair(t,sol);
  return testpair(t,sol);
}
testpair random_bad_eqn(int n, bool well=true) {
  static std::default_random_engine rng;
  std::bernoulli_distribution bern(0.5);
  std::uniform_int_distribution<int> dd(0, n);
  std::uniform_real_distribution<double> dcont(0, 1.0);

  td::tridiag_aug<double> t(n);
  std::vector<double> sol(n);
  for (int i = 0; i < n-1; ++i) { 
    t(i,i+1) = dcont(rng);
    double tii = t(i,i+1)*1e-6;
    std::uniform_real_distribution<double> sec(tii);
    t(i,i) = sec(rng);
    tii -= t(i, i)*1e-6;
    sec = std::uniform_real_distribution<double>(0, tii);
    if (i > 0) {
      t(i,i-1) = sec(rng);
      t(i,n) = t(i,i-1) + t(i,i) + t(i,i+1);
    }
    sol[i] = 1;
  }
  if (n < 2) return testpair(t,sol);
  return testpair(t,sol);
}

int main(int argc, char** argv) {
  std::cout << std::fixed;
  std::cout.precision(32);
  int n = std::stoi(argv[1]);
  int k = std::stoi(argv[2]);
  bool verbose = std::find(argv, argv+argc, std::string("-v")) != argv+argc;
  bool well = std::find(argv, argv+argc, std::string("-w")) != argv+argc;
  bool bad = std::find(argv, argv+argc, std::string("-b")) != argv+argc;
  if(well)std::cout << std::endl;
#ifdef DEBUG
  if (verbose) std::cout << "verbose" << std::endl;
  if (well) std::cout << "well" << std::endl;
#endif
  for (int i = 0; i < k; ++i) {
    testpair tp;
    if (well) tp = random_well_eqn(n);
    else if (bad) tp = random_bad_eqn(n);
    else tp = random_eqn(n);
    SOLVER::solve(tp.eqn, verbose);
    if (verbose) {
      std::cout << tp.eqn;
      std::cout << "correct solution: " << std::endl;
      std::for_each(tp.sol.begin(), tp.sol.end(), [](double v) {std::cout << v << " "; });
      std::cout << std::endl << std::endl;
    }
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
