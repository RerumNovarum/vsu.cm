#define TD_T_DEC template<typename V>
#define TD_C_DEC td::tridiag<V>
#define TD_C typename TD_C_DEC

TD_T_DEC
TD_C_DEC::~tridiag() {
}

TD_T_DEC
TD_C_DEC::tridiag(int n): N(n) {
  main.resize(n);
  if (n > 1) {
    sup.resize(n-1);
    sub.resize(n-1);
  }
}

TD_T_DEC
TD_C_DEC::tridiag(vec_const_ref sup, vec_const_ref main, vec_const_ref sub) {
  N = main.size();
  if (N > 0) {
    assert(sup.size() == N-1);
    assert(sub.size() == N-1);
  }
  this->sup = sup;
  this->main = main;
  this->sub = sub;
}

TD_T_DEC
TD_C_DEC::tridiag(istream& in) {
  in >> this->N;
  sup.reserve(N);
  sub.reserve(N);
  main.reserve(N);
  for (int i = 0; i < N - 1; ++i) {
    double v;
    in >> v;
    sup.push_back(v);
  }
  for (int i = 0; i < N; ++i) {
    double v;
    in >> v;
    main.push_back(v);
  }
  for (int i = 0; i < N - 1; ++i) {
    double v;
    in >> v;
    sub.push_back(v);
  }
}

TD_T_DEC
size_t TD_C_DEC::size() const {
  return N;
}


TD_T_DEC
TD_C::val_ref TD_C_DEC::operator()(int i, int j) {
  // TODO: check bounds
  if (i == j) return main[i];
  else if (i == j + 1) return sub[j];
  else if (i == j - 1) return sup[i];
  else throw out_of_range("tridiag::operator()(i,j)");
}

TD_T_DEC
TD_C::val_const_ref TD_C_DEC::operator()(int i, int j) const {
  // TODO: check bounds
  if (i < 0 || j < 0) return zero;
  if (i == j) return main[i];
  else if (i == j + 1) return sub[j];
  else if (i == j - 1) return sup[i];
  return zero;
}

TD_T_DEC
V TD_C_DEC::get(int i, int j) const {
  return (*this)(i,j);
}

TD_T_DEC
void TD_C_DEC::set(int i, int j, V v) {
  (*this)(i,j) = v;
}

TD_T_DEC
bool TD_C_DEC::row_try_add(int from, int to, V alpha) {
  if (from < 0 || from >= N || to < 0 || to >= N) return false; 
  vector f, t;
  f.resize(5);
  t.resize(5);
  fill_n(f.begin(), zero, 5);
  fill_n(t.begin(), zero, 5);
  if (to > from) {
    copy_row(from, f.begin());
    if (from > 0)
      copy_row(to, t.begin() + (to - from));
    else
      copy_row(to, t.begin() + (to - from - 1));
  } else {
    copy_row(to, t.begin());
    if (to > 0) {
      copy_row(from, f.begin() + from - to);
    } else {
      copy_row(from, f.begin() + from - to - 1);
    }
  }
  // for_each(t, t + 5, [](V v) { std::cout << "tv=" << v << std::endl; });
  for (int i = 0; i < 5; ++i) {
    t[i] += alpha * f[i];
  }
  int j1, j2, rj1;
  j1 = 0;
  j2 = 3;
  rj1 = to - 1;
  if(to > from) {
    if (from != 0) {
      j1 = 1;
    }
  } else {
    if (to == 0) {
      rj1 = to;
      j2 = 2;
    } else if (to == N - 1) {
      j2 = 2;
    }
  }
  for (int j = 0; j < j1; ++j) if (t[j] != 0) return false;
  for (int j = j2; j < 5; ++j) if (t[j] != 0) return false;
  for (int j = j1, rj=rj1; j < j2; ++j, ++rj) {
    set(to, rj, t[j]);
  }
  return true;
}

TD_T_DEC
template<typename dest_iter>
void TD_C_DEC::copy_row(int row, dest_iter dest) {
  int j_0 = row - 1;
  int j_1 = row + 2;
  if (j_0 == -1) j_0 = 0;
  if (j_1 > N) j_1 = N;
  for (int j = j_0; j < j_1; ++j, ++dest)
    *dest = get(row, j);
}

TD_T_DEC
void TD_C_DEC::mul_row(int row, V alpha) {
  int j_0 = row - 1;
  int j_1 = row + 2;
  if (j_0 == -1) j_0 = 0;
  if (j_1 > N) j_1 = N;
  for (int j = j_0; j < j_1; ++j) (*this)(row,j) *= alpha;
}

TD_T_DEC
size_t TD_C_DEC::row_vars_no(int row) const {
  int j_0 = row - 1;
  int j_1 = row + 2;
  if (j_0 == -1) j_0 = 0;
  if (j_1 > N) j_1 = N;
  int cnt = 0;
  for (int j = j_0; j < j_1; ++j)
    if ((*this)(row, j) != zero)
      ++cnt;
  return cnt;
}

TD_T_DEC
bool TD_C_DEC::diagonalized() const {
  for (int i = 0; i < N - 1; ++i) {
    if ((*this)(i, i+1) != 0) return false;
    if ((*this)(i+1, i) != 0) return false;
  }
  return true;
}

TD_T_DEC
ostream& operator<<(ostream& out, const TD_C_DEC& t) {
  int n = t.size();
  out << "$$\\begin{pmatrix}" << std::endl;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      out << t.get(i, j);
      if (j != n -1)
        out << " & ";
    }
    if (i !=  n -1)
      out << "\\\\";
    out << std::endl;
  }
  out << "\\end{pmatrix}$$" << std::endl;
  return out;
}

template<typename V>
void td::print_vector(std::ostream& out, const std::vector<V>& vec, const std::string& var) {
  out << "$$";
  if (var != "")
    out << var << "=" << std::endl;
  int n = vec.size();
  out << "\\begin{pmatrix}";
  for (int i = 0; i < n; ++i) {
    std::cout << vec[i];
    if (i != n - 1) std::cout << "\\\\";
    std::cout << std::endl;
  }
  std::cout << "\\end{pmatrix}$$" << std::endl;
}
#undef TD_C
#undef TD_C_DEC
#undef TD_T_DEC
