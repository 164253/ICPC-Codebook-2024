#include <bits/stdc++.h>
#define int long long
using namespace std;

template <class T> T extgcd(T a, T b, T &x, T &y) {
  if (!b) {
    x = 1;
    y = 0;
    return a;
  }
  T ans = extgcd(b, a % b, y, x);
  y -= a / b * x;
  return ans;
}

template <class T> T modeq(T a, T b, T p) {
  T x, y, d = extgcd(a, p, x, y);
  if (b % d)
    return 0;
  return ((b / d * x) % p + p) % p;
}

template <class T> class Matrix {
  static const T MOD = 1000000007;

public:
  vector<vector<T>> v;
  Matrix(int n, int m, int identity) {
    v = vector<vector<T>>(n, vector<T>(m, 0));
    if (identity)
      for (int i = 0, k = min(n, m); i < k; ++i)
        v[i][i] = 1;
  }
  Matrix(Matrix &b) { v = b.v; }
  void in(int l = 0, int m = -1, int u = 0, int n = -1) {
    if (n < 0)
      n = v.size();
    if (m < 0)
      m = v[0].size();
    for (int i = u; i < n; ++i)
      for (int j = l; j < m; ++j)
        scanf("%lld", &v[i][j]);
  }
  Matrix(int n, int m) {
    v = vector<vector<T>>(n, vector<T>(m, 0));
    in();
  }
  void out(int l = 0, int m = -1, int u = 0, int n = -1) {
    if (n < 0)
      n = v.size();
    if (m < 0)
      m = v[0].size();
    for (int i = u; i < n; ++i)
      for (int j = l; j < m; ++j)
        printf("%lld%c", v[i][j], " \n"[j == m - 1]);
  }
  Matrix operator=(Matrix &b) {
    v = b.v;
    return *this;
  }
  Matrix operator+(Matrix &b) {
    Matrix ans(*this);
    int n = v.size(), m = v[0].size();
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j) {
        ans.v[i][j] += b.v[i][j];
        if (MOD) {
          if (ans.v[i][j] < 0)
            ans.v[i][j] = (ans.v[i][j] % MOD + MOD) % MOD;
          if (ans.v[i][j] >= MOD)
            ans.v[i][j] %= MOD;
        }
      }
    return ans;
  }
  Matrix operator+(T x) {
    Matrix ans(*this);
    int n = v.size(), m = v[0].size();
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j) {
        ans.v[i][j] += x;
        if (MOD) {
          if (ans.v[i][j] < 0)
            ans.v[i][j] = (ans.v[i][j] % MOD + MOD) % MOD;
          if (ans.v[i][j] >= MOD)
            ans.v[i][j] %= MOD;
        }
      }
    return ans;
  }
  Matrix operator-(Matrix &b) {
    Matrix ans(*this);
    int n = v.size(), m = v[0].size();
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j) {
        ans.v[i][j] -= b.v[i][j];
        if (MOD) {
          if (ans.v[i][j] < 0)
            ans.v[i][j] = (ans.v[i][j] % MOD + MOD) % MOD;
          if (ans.v[i][j] >= MOD)
            ans.v[i][j] %= MOD;
        }
      }
    return ans;
  }
  Matrix operator-(T x) {
    Matrix ans(*this);
    int n = v.size(), m = v[0].size();
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j) {
        ans.v[i][j] -= x;
        if (MOD) {
          if (ans.v[i][j] < 0)
            ans.v[i][j] = (ans.v[i][j] % MOD + MOD) % MOD;
          if (ans.v[i][j] >= MOD)
            ans.v[i][j] %= MOD;
        }
      }
    return ans;
  }
  Matrix operator+=(Matrix &b) {
    int n = v.size(), m = v[0].size();
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j) {
        v[i][j] += b.v[i][j];
        if (MOD) {
          if (v[i][j] < 0)
            v[i][j] = (v[i][j] % MOD + MOD) % MOD;
          if (v[i][j] >= MOD)
            v[i][j] %= MOD;
        }
      }
    return *this;
  }
  Matrix operator+=(T x) {
    int n = v.size(), m = v[0].size();
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j) {
        v[i][j] += x;
        if (MOD) {
          if (v[i][j] < 0)
            v[i][j] = (v[i][j] % MOD + MOD) % MOD;
          if (v[i][j] >= MOD)
            v[i][j] %= MOD;
        }
      }
    return *this;
  }
  Matrix operator-=(Matrix &b) {
    int n = v.size(), m = v[0].size();
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j) {
        v[i][j] -= b.v[i][j];
        if (MOD) {
          if (v[i][j] < 0)
            v[i][j] = (v[i][j] % MOD + MOD) % MOD;
          if (v[i][j] >= MOD)
            v[i][j] %= MOD;
        }
      }
    return *this;
  }
  Matrix operator-=(T x) {
    int n = v.size(), m = v[0].size();
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j) {
        v[i][j] -= x;
        if (MOD) {
          if (v[i][j] < 0)
            v[i][j] = (v[i][j] % MOD + MOD) % MOD;
          if (v[i][j] >= MOD)
            v[i][j] %= MOD;
        }
      }
    return *this;
  }
  Matrix operator*(Matrix &b) {
    int n = v.size();
    int p = b.v.size();
    int m = b.v[0].size();
    Matrix ans(n, m, 0);
    for (int i = 0; i < n; ++i)
      for (int k = 0; k < p; ++k)
        for (int j = 0; j < m; ++j) {
          ans.v[i][j] += v[i][k] * b.v[k][j];
          if (MOD) {
            if (ans.v[i][j] < 0)
              ans.v[i][j] = (ans.v[i][j] % MOD + MOD) % MOD;
            if (ans.v[i][j] >= MOD)
              ans.v[i][j] %= MOD;
          }
        }
    return ans;
  }
  Matrix operator*(T x) {
    Matrix ans(*this);
    int n = v.size(), m = v[0].size();
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j) {
        ans.v[i][j] *= x;
        if (MOD) {
          if (ans.v[i][j] < 0)
            ans.v[i][j] = (ans.v[i][j] % MOD + MOD) % MOD;
          if (ans.v[i][j] >= MOD)
            ans.v[i][j] %= MOD;
        }
      }
    return ans;
  }
  Matrix operator*=(Matrix &b) {
    int n = v.size();
    int p = b.v.size();
    int m = b.v[0].size();
    Matrix ans(n, m, 0);
    for (int i = 0; i < n; ++i)
      for (int k = 0; k < p; ++k)
        for (int j = 0; j < m; ++j) {
          ans.v[i][j] += v[i][k] * b.v[k][j];
          if (MOD) {
            if (ans.v[i][j] < 0)
              ans.v[i][j] = (ans.v[i][j] % MOD + MOD) % MOD;
            if (ans.v[i][j] >= MOD)
              ans.v[i][j] %= MOD;
          }
        }
    v = ans.v;
    return *this;
  }
  Matrix operator*=(T x) {
    int n = v.size(), m = v[0].size();
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j) {
        v[i][j] *= x;
        if (MOD) {
          if (v[i][j] < 0)
            v[i][j] = (v[i][j] % MOD + MOD) % MOD;
          if (v[i][j] >= MOD)
            v[i][j] %= MOD;
        }
      }
    return *this;
  }
  Matrix operator/(T x) {
    Matrix ans(*this);
    int n = v.size(), m = v[0].size();
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j) {
        if (MOD) {
          ans.v[i][j] *= modeq(x, (T)1, (T)MOD);
          if (ans.v[i][j] < 0)
            ans.v[i][j] = (ans.v[i][j] % MOD + MOD) % MOD;
          if (ans.v[i][j] >= MOD)
            ans.v[i][j] %= MOD;
        } else
          ans.v[i][j] /= x;
      }
    return ans;
  }
  Matrix operator/=(T x) {
    int n = v.size(), m = v[0].size();
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j) {
        if (MOD) {
          v[i][j] *= modeq(x, (T)1, (T)MOD);
          if (v[i][j] < 0)
            v[i][j] = (v[i][j] % MOD + MOD) % MOD;
          if (v[i][j] >= MOD)
            v[i][j] %= MOD;
        } else
          v[i][j] /= x;
      }
    return *this;
  }
  Matrix operator%=(T p) {
    int n = v.size(), m = v[0].size();
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j)
        if (v[i][j] >= p)
          v[i][j] %= p;
    return *this;
  }
  void gaussian() {
    int curi = 0;
    int n = v.size();
    int m = v[0].size();
    for (int j = 0; j < m; j++) {
      int i;
      for (i = curi; i < n; i++) {
        if (MOD) {
          v[i][j] %= MOD;
        }
        if (v[i][j]) {
          break;
        }
      }
      if (i >= n) {
        continue;
      }
      if (v[i][j] == 0)
        continue;
      for (int k = 0; k < m; k++) {
        swap(v[i][k], v[curi][k]);
      }
      for (int k = m - 1; k >= j; k--) {
        if (MOD) {
          v[curi][k] *= modeq(v[curi][j], (T)1, (T)MOD);
          v[curi][k] = (v[curi][k] % MOD + MOD) % MOD;
        } else
          v[curi][k] /= v[curi][j];
      }
      for (int i = 0; i < n; ++i) {
        if (i != curi) {
          for (int k = m - 1; k >= j; k--) {
            v[i][k] -= v[curi][k] * v[i][j];
            if (MOD) {
              v[i][k] = (v[i][k] % MOD + MOD) % MOD;
            }
          }
        }
      }
      curi++;
    }
  }
};