#define uLL __uint128_t
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
/*輸入x,n,p,ans 會將ans修改為x^n%p
對整數/矩陣/不要求精度的浮點 皆有效
模板第一個型別是x,ans 第二個是n,p(應該放LL或__int128)*/
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