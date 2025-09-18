//洛谷P1005
#include <bits/stdc++.h>
using namespace std;
#define N 85
#define LL long long
#define pii pair<int, int>
#define F first
#define S second
struct num {
  const static LL base = 1000000000LL; // base 1e9
  LL p[505], len;
  num() {
    memset(p, 0, sizeof(p));
    len = 0;
  }
  num(LL x) {
    memset(p, 0, sizeof(p));
    len = 0;
    for (p[len++] = x; p[len - 1] >= base; ++len)
      p[len] = p[len - 1] / base, p[len - 1] %= base;
  }
  num operator=(LL x) {
    memset(p, 0, sizeof(p));
    len = 0;
    for (p[len++] = x; p[len - 1] >= base; ++len)
      p[len] = p[len - 1] / base, p[len - 1] %= base;
    return *this;
  }
  num max(const num &b) {
    if (len != b.len)
      return len > b.len ? *this : b;
    for (int i = len; i--;)
      if (p[i] != b.p[i])
        return p[i] > b.p[i] ? *this : b;
    return *this;
  }
  num operator+(const num &b) {
    num c;
    LL x = 0;
    for (LL &i = c.len; i < len || i < b.len; ++i) {
      c.p[i] = p[i] + b.p[i] + x;
      x = c.p[i] / base;
      c.p[i] %= base;
    }
    if (x)
      c.p[c.len++] = x;
    return c;
  }
  num operator*(LL b) {
    num c;
    c.len = len;
    LL x = 0;
    for (LL i = 0; i < len; ++i) {
      c.p[i] = p[i] * b + x;
      x = c.p[i] / base;
      c.p[i] %= base;
    }
    for (; x; x /= base)
      c.p[c.len++] = x % base;
    return c;
  }
} dp[N][N], ans;
ostream &operator<<(ostream &s, num a) {
  if (!a.len)
    return s << "0";
  s << a.p[a.len - 1];
  for (int i = a.len - 1; i--;) {
    if (!a.p[i])
      s << "000000000";
    else {
      for (int k = 10; k * a.p[i] < (LL)1e9; k *= 10)
        s << "0";
      s << a.p[i];
    }
  }
  return s;
}
LL a[N];
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int n, m, i, j;
  for (cin >> n >> m; n--;) {
    for (i = 0; i < m; ++i)
      cin >> a[i];
    for (i = 0; i < m; ++i)
      for (j = 0; j < m; ++j)
        dp[i][j] = 0;
    for (i = 0; i < m; ++i)
      dp[i][i] = a[i] << 1;
    for (j = 1; j < m; ++j)
      for (i = 0; i + j < m; ++i)
        dp[i][i + j] =
            (dp[i][i + j - 1] + a[i + j]).max(dp[i + 1][i + j] + a[i]) * 2;
    ans = ans + dp[0][m - 1];
  }
  cout << ans;
}