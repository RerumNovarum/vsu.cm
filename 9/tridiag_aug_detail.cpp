#define TD_T_DEC template<typename V>
#define TD_C_DEC td::tridiag_aug<V>
#define TD_C typename TD_C_DEC
TD_T_DEC
TD_C_DEC::tridiag_aug(int n) : N(n){
  A = tridiag<V>(n);
  d.resize(n);
}

TD_T_DEC
TD_C_DEC::tridiag_aug(vector& sup, vector& main, vector& sub, vector& d) {
  A = tridiag<V>(sup,main,sub);
  this->d = d;
  N = A.size();
}

TD_T_DEC
TD_C_DEC::tridiag_aug(istream& td_in, istream& d_in) {
  A = td::tridiag<V>(td_in);
  N = A.size();
  int n1;
  d_in >> n1;
  assert(N == n1);
  d.reserve(n1);
  for (int i = 0; i < N; ++i) {
    double v;
    d_in >> v;
    d.push_back(v);
  }
}

TD_T_DEC
TD_C::val_ref TD_C_DEC::operator()(int i, int j) {
  if (j == N && i >= 0 && i < N) return d[i];
  return A(i,j);
}

TD_T_DEC
TD_C::val_const_ref TD_C_DEC::operator()(int i, int j) const {
  if (j == N && i >= 0 && i < N) return d[i];
  return A(i,j);
}

TD_T_DEC
void TD_C_DEC::mul_row(int i, V alpha) {
  A.mul_row(i, alpha);
  d[i] *= alpha;
}

TD_T_DEC
void TD_C_DEC::row_add(int from, int to, V alpha) {
  A.row_add(from, to, alpha);
  d[to] += alpha * d[from];
}

TD_T_DEC
size_t TD_C_DEC::row_vars_no(int row) const {
  return A.row_vars_no(row);
}

TD_T_DEC
int TD_C_DEC::size() const {
return N;
}

TD_T_DEC
bool TD_C_DEC::diagonalized() const {
  return A.diagonalized();
}

TD_T_DEC
ostream& operator<<(ostream& out, const TD_C_DEC& eqn) {
  out << "$$\\begin{pmatrix}" << std::endl;
  int N = eqn.size();
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      out << eqn(i, j);
      if (j != N -1)
        out << " & ";
    }

    out << " & \\vline & "  << eqn(i, N);
    if (i !=  N -1)
      out << " \\\\";
    out << std::endl;
  }
  out << "\\end{pmatrix}$$" << std::endl;
  return out;
}

#undef TD_C
#undef TD_C_DEC
#undef TD_T_DEC
