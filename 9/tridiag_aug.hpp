#ifndef TRIDIAG_EXT
#define TRIDIAG_EXT

#include <vector>
#include <algorithm>
#include <istream>
#include <stdexcept>
#include <cassert>

#include "tridiag.hpp"

using std::istream;
using std::ostream;
using std::fill_n;
using std::for_each;
using std::out_of_range;

namespace td {
  template<typename V>
    class tridiag_aug {
      public:
        typedef std::vector<V> vector;
        typedef vector& vec_ref;
        typedef const vector& vec_const_ref;
        typedef V& val_ref;
        typedef const V& val_const_ref;

        tridiag_aug() {}
        explicit tridiag_aug(int N);
        explicit tridiag_aug(vector& sup, vector& main, vector& sub, vector& d);
        explicit tridiag_aug(istream& td_in, istream& d_in);

        val_const_ref operator()(int i, int j) const;
        val_ref operator()(int i, int j);
        void mul_row(int i, V alpha);
        bool row_try_add(int from, int to, V alpha);
        int size() const;
        size_t row_vars_no(int row) const;
        bool diagonalized() const;
      private:
        int N;
        tridiag<V> A;
        vector d;
    };
}

#include "tridiag_aug_detail.cpp"
#endif
