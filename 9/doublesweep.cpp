#include <algorithm>

#include "tridiag.hpp"

namespace td {
  namespace doublesweep {
    template<typename V>
      void twodiagonalize(tridiag_aug<V>& eqn, bool verbose=false);
    template<typename V>
      void sweepback(tridiag_aug<V>& eqn, bool verbose=false);
    template<typename V>
      void solve(tridiag_aug<V>& eqn, bool verbose=false);
    template<typename V>
      void relax(tridiag_aug<V>& eqn, int i1, int i2, bool verbose=false);
    template<typename V>
      void relax_forward(tridiag_aug<V>& eqn, int i1, int i2, bool verbose=false);
    template<typename V>
      void relax_backward(tridiag_aug<V>& eqn, int i1, int i2, bool verbose=false);

    template<typename V>
      void twodiagonalize(tridiag_aug<V>& eqn, bool verbose) { // particular case
        int n = eqn.size();
        if (eqn(0,0) != 0) {
          eqn.mul_row(0, 1/eqn(0,0));
          if (verbose)
            std::cout << eqn;
        }
        for (int i = 1; i < n; ++i) {
          if (eqn(i-1,i-1) != 0) {
            relax_forward(eqn, i-1, i, verbose);
          }
          if (eqn(i,i) != 0) {
            eqn.mul_row(i, 1/eqn(i,i));
            if (verbose)
              std::cout << eqn;
          }
        }
      }

    template<typename V>
      void sweepback(tridiag_aug<V>& eqn, bool verbose) {
        int n = eqn.size();
        int base;
        for (base = 0; base < n; ++base)
          if (eqn.row_vars_no(base) == 1) break;
        if (base == n) {
          std::cerr << "cannot solve via doublesweep" << std::endl;
        }
        --base;
        for (int i = base; i < n - 1; ++i)
          relax_forward(eqn, i, i+1, verbose);
        for (int i = base; i >= 0; --i)
          relax_backward(eqn, i, i+1, verbose);
      }

    template<typename V>
      void solve(tridiag_aug<V>& eqn, bool verbose) {
        if (verbose)
          std::cout << eqn;
        size_t n = eqn.size();
        if (n == 1 && eqn(0,0) != 0) eqn.mul_row(0, 1/eqn(0,0));
        if (n < 2) return;
        twodiagonalize(eqn, verbose);
        if (verbose)
          std::cout << eqn;
        sweepback(eqn, verbose);
        // if the input is trivial, we're happy
        //
        // but it can happen
        // that there were zeroes on main diagonal
        // which resulted in inability
        // to cancel interfering variables
        // in trivial way 
        // (i.e. by reducing coefficients only
        //  in adjacent rows
        //  and only in a single direction)
        //if (!eqn.diagonalized()) {
        //  for (int i = 0; i < n - 1; ++i)
        //    relax(t, d, i, i+1);
        //}
        if (verbose)
          std::cout << eqn;
        for (int i = 0; i < n; ++i) {
          if (eqn(i,i) != 0) {
            eqn.mul_row(i, 1/eqn(i,i));
          }
        }
        if (verbose)
          std::cout << eqn;
      }

    template<typename V>
      void relax(tridiag_aug<V>& eqn, int i1, int i2, bool verbose) {
        if (i1 == i2) return;
        if (i1 > i2) {
          int t = i1;
          i1 = i2;
          i2 = i1;
        }
        relax_forward(eqn, i1, i2);
        relax_backward(eqn, i1, i2);
      }

    template<typename V>
      void relax_forward(tridiag_aug<V>& eqn, int i1, int i2, bool verbose) {
        assert(i1 < i2);
        if (eqn(i2, i2-1) != 0) {
          if (eqn(i1, i1) != 0) {
            double alpha = -eqn(i2,i2-1)/eqn(i1,i1);
            if (verbose)
              std::cout << i1 << " " << i2 << " " << alpha << std::endl;
            eqn.row_try_add(i1, i2, alpha);
            if(verbose)
              std::cout << eqn;
          }
        }
      }

    template<typename V>
      void relax_backward(tridiag_aug<V>& eqn, int i1, int i2, bool verbose) {
        assert(i1 < i2);
        if (eqn(i1, i1+1) != 0) {
          if (eqn(i2,i2) != 0) {
            double alpha = -eqn(i1,i1+1)/eqn(i2, i2);
            if (verbose)
              std::cout << i2 << " " << i1 << " " << alpha << std::endl;
            eqn.row_try_add(i2, i1, alpha);
            if (verbose)
              std::cout << eqn;
          }
        }
      }
  }
}
