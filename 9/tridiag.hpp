#ifndef TRIDIAG
#define TRIDIAG

#include <vector>
#include <algorithm>
#include <istream>
#include <stdexcept>
#include <cassert>

using std::istream;
using std::ostream;
using std::fill_n;
using std::for_each;
using std::out_of_range;

namespace td {
  template<typename V>
    class tridiag {
      public:
        typedef std::vector<V> vector;
        typedef vector& vec_ref;
        typedef const vector& vec_const_ref;
        typedef V& val_ref;
        typedef const V& val_const_ref;

        tridiag(){}
        explicit tridiag(int N);
        explicit tridiag(vec_const_ref sup, vec_const_ref main, vec_const_ref sub);
        explicit tridiag(istream& in);
        ~tridiag();
        V get(int i, int j) const;
        void set(int i, int j, V v);
        val_const_ref operator()(int i, int j) const;
        val_ref operator()(int i, int j);
        bool row_try_add(int from, int to, V alpha);
        void mul_row(int i, V alpha);
        size_t size() const;
        size_t row_vars_no(int row) const;
        bool diagonalized() const;
      private:
        vector sup, main, sub;
        int N;
        V zero = 0;

      public:
        template<typename dest_iter>
          void copy_row(int i, dest_iter dest_begin);
    };
  template<typename V>
    void print_vector(std::ostream& out, const std::vector<V>& vec, const std::string& var="");
}

#include "tridiag_detail.cpp"
#include "tridiag_aug.hpp"
#endif
