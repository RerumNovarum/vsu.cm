#include "tridiag.hpp"

namespace td {
  namespace instable {
    struct unsolvable {};

    template<typename V>
      void solve(tridiag_aug<V>& eqn, bool verbose) {
        if (verbose) std::cout << eqn;
        int n = eqn.size();
        if (n == 1 && eqn(0,0) != 0) eqn.mul_row(0, 1/eqn(0,0));
        if (n < 2) return;
        for (int i = 0; i < n - 1; ++i)
          if (eqn(i, i+1) == 0) throw unsolvable();
        std::vector<V> y(n);
        std::vector<V> z(n);

        y[0] = 0;
        if (n > 1)
          y[1] = eqn(0,n)/eqn(0,1);
        for (int i = 1; i < n - 1; ++i) {
          V d_i = eqn(i, n);
          V a_i = eqn(i,i-1);
          V b_i = eqn(i,i);
          V c_i = eqn(i,i+1);
          y[i+1] = (d_i - a_i*y[i-1] - b_i*y[i])/c_i;
        }

        z[0] = 1;
        if (n > 1)
          z[1] = - eqn(0,0)/eqn(0,1);
        for (int i = 1; i < n - 1; ++i) {
          V a_i = eqn(i,i-1);
          V z_pp = z[i-1];
          V b_i = eqn(i,i);
          V z_i = z[i];
          V c_i = eqn(i,i+1);
          z[i+1] = - (a_i*z_pp + b_i*z_i)/c_i;
        }

        V d = eqn(n-1,n);
        V a = eqn(n-1,n-2);
        V b = eqn(n-1,n-1);
        V K = (d  - a * y[n-2] - b * y[n-1]) / (a * z[n-2] + b * z[n-1]);

        for (int i = 0; i < n; ++i) {
          eqn(i,i) = 1;
          eqn(i,n) = y[i] + K*z[i];
        }
        for (int i = 0; i < n-1; ++i) {
          eqn(i+1,i) = 0;
          eqn(i,i+1) = 0;
        }

        if (verbose) {
          print_vector(std::cout, y, "y");
          print_vector(std::cout, z, "z");
          std::cout << "K=" << K << std::endl;
          std::cout << eqn;
        }
      }
  }
}
