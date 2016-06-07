#include <iostream>

#include "tridiag.hpp"

using namespace td;

int main() {
  int n;
  std::vector<double> sup,main,sub;
  std::cin >> n;
  main.reserve(n);
  if (n > 1) {
    sup.reserve(n-1);
    sub.reserve(n-1);
  }
  for (int i = 0; i < n - 1; ++i) {
    double v;
    std::cin >> v;
    sup.push_back(v);
  }
  for (int i = 0; i < n; ++i) {
    double v;
    std::cin >> v;
    main.push_back(v);
  }
  for (int i = 0; i < n - 1; ++i) {
    double v;
    std::cin >> v;
    sub.push_back(v);
  }
  tridiag<double> t(sup, main, sub);
  std::cout.precision(8);
  std::cout.setf(std::ios::fixed);
  std::cout << t;
  return 0;
}

