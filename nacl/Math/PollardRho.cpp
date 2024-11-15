#include <bits/stdc++.h>
using namespace std;
#define LL long long
#define uLL __uint128_t
#define sub(a, b) ((a) < (b) ? (b) - (a) : (a) - (b))
template <class T, class POW> void fastpow(T x, POW n, POW p, T &ans) {
  for (; n; n >>= 1) {
    if (n & 1) {
      ans *= x;
      ans %= p;
    }
    x *= x;
    x %= p;
  }
}
/*input x, n, p, ans, will modify ans to x ^ n % p
the first is x, ans and the second is n, p (LL or __int128)
*/
uLL pri[7] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022}; /*2^64*/
// int p[3]={2,7,61};/*2^32*/
bool check(const uLL x, const uLL p) {
  uLL d = x - 1, ans = 1;
  fastpow(p, d, x, ans);
  if (ans != 1)
    return 1;
  for (; !(d & 1);) {
    d >>= 1;
    ans = 1;
    fastpow(p, d, x, ans);
    if (ans == x - 1)
      return 0;
    else if (ans != 1)
      return 1;
  }
  return 0;
}
bool miller_rabin(const uLL x) {
  if (x == 1)
    return 0;
  for (auto e : pri) {
    if (e >= x)
      return 1;
    if (check(x, e))
      return 0;
  }
  return 1;
}
template <class T> T gcd(T a, T b) {
  if (!a)
    return b;
  if (!b)
    return a;
  if (a & b & 1)
    return gcd(sub(a, b), min(a, b));
  if (a & 1)
    return gcd(a, b >> 1);
  if (b & 1)
    return gcd(a >> 1, b);
  return gcd(a >> 1, b >> 1) << 1;
}
/*gcd(a,b) denote gcd(a, 0) = a*/
mt19937 rnd(time(0));
template <class T> T f(T x, T c, T mod) {
  return (((uLL)x) * x % mod + c) % mod;
}
template <class T> T rho(T n) {
  T mod = n, x = rnd() % mod, c = rnd() % (mod - 1) + 1, p = 1;
  for (T i = 2, j = 2, d = x;; ++i) {
    x = f(x, c, mod);
    p = ((uLL)p) * sub(x, d) % mod;
    if (i % 127 == 0 && gcd(p, n) != 1)
      return gcd(p, n);
    if (i == j) {
      j <<= 1, d = x;
      if (gcd(p, n) != 1)
        return gcd(p, n);
    }
  }
}
template <class T> T pollard_rho(T n) {
  if (miller_rabin(n))
    return n;
  T p = n;
  while (p == n)
    p = rho(n);
  return max(pollard_rho(p), pollard_rho(n / p));
}
int main() {
  LL t, n, ans;
  for (cin >> t; t--;) {
    cin >> n;
    ans = pollard_rho(n);
    if (ans == n)
      puts("Prime");
    else
      printf("%lld\n", ans);
  }
}