#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define pll pair<int, int>
#define pdd pair<double, double>
#define pll pair<ll, ll>
#define F first
#define S second
#define eps 1e-6
int sign(double x) { return fabs(x) < eps ? 0 : x > 0 ? 1 : -1; }
int sign(ll x) { return !x ? 0 : x > 0 ? 1 : -1; }
template <typename T1, typename T2>
istream &operator>>(istream &s, pair<T1, T2> &p) {
  auto &[a, b] = p;
  s >> a >> b;
  return s;
}
template <typename T1, typename T2>
ostream &operator<<(ostream &s, const pair<T1, T2> p) {
  auto &[a, b] = p;
  s << a << " " << b;
  return s;
}
pll operator+(const pll a, const pll b) { return {a.F + b.F, a.S + b.S}; }
pll operator-(const pll a, const pll b) { return {a.F - b.F, a.S - b.S}; }
pll operator-(const pll a) { return {-a.F, -a.S}; }
pll operator*(const pll a, const pll b) {
  return {(ll)a.F * b.F, (ll)a.S * b.S};
}
pdd operator/(const pll a, const double x) { return {a.F / x, a.S / x}; }
pdd operator*(const pll a, const double x) { return {a.F * x, a.S * x}; }
pdd operator*(const double x, const pll a) { return {a.F * x, a.S * x}; }
//沒有標示幾個 vector 的都是對三個點做事，以第一個點為參考點
ll len2(pll p) { return (ll)p.F * p.F + (ll)p.S * p.S; } // 1 vector
double len(pll p) { return sqrt((double)len2(p)); }
ll cross(pll a, pll b) { return (ll)a.F * b.S - (ll)a.S * b.F; } // 2 vector
ll cross(pll p1, pll p2, pll p3) {
  return cross(p2 - p1, p3 - p1);
} //(b-a) cross (c-a)
ll dot(pll a, pll b, pll c) {
  return (ll)(b.F - a.F) * (c.F - a.F) + (ll)(b.S - a.S) * (c.S - a.S);
} //(b-a) dot (c-a)
ll ori(pll p1, pll p2, pll p3) {
  return sign(cross(p1, p2, p3));
} // normalize to {-1,0,1} (b-a) cross (c-a)
bool btw(pll p1, pll p2, pll p3) {
  return ori(p3, p1, p2) == 0 && dot(p3, p1, p2) <= 0;
} // p3 bwteen p1,p2
bool banana(pll p1, pll p2, pll p3, pll p4) { //問兩線段是否香蕉
  if (btw(p1, p2, p3) || btw(p1, p2, p4) || btw(p3, p4, p1) || btw(p3, p4, p2))
    return true;
  return ori(p1, p2, p3) * ori(p1, p2, p4) < 0 &&
         ori(p3, p4, p1) * ori(p3, p4, p2) < 0;
}
pdd banana_point(
    pll p1, pll p2, pll p3,
    pll p4) { //分點，算的是無限延伸直線的交點，平行的時候 undefined
  return cross(p2 - p1, p4 - p1) / (double)cross(p2 - p1, p4 - p3) * p3 -
         cross(p2 - p1, p3 - p1) / (double)cross(p2 - p1, p4 - p3) * p4;
}
pdd proj(pll p1, pll p2, pll p3) {
  return dot(p1, p2, p3) / (double)len2(p2 - p1) * (p2 - p1);
}
double min_dis(pll p1, pll p2, pll p3) { // min distance of p3 to segment p1,p2
  if (dot(p1, p2, p3) < 0 || dot(p2, p1, p3) < 0)
    return min(len(p3 - p1), len(p3 - p2));
  return abs(cross(p1, p2, p3)) / len(p2 - p1);
}
ll area2(
    vector<pll> &
        v) { //傳入一個多邊形照順序的點集，起點要出現兩次，回傳兩倍面積，注意是兩倍才可以
             // ll
  int n = v.size() - 1;
  ll ans = 0;
  for (int i = 0; i < n; ++i)
    ans += cross(v[i], v[i + 1]);
  return abs(ans);
}
int in_polygon(vector<pll> &v,
               pll p) { //傳入多邊形，起點要出現兩次，回傳 {-1:in, 0:on, 1:out}
  int n = v.size() - 1, ans = 1;
  for (int i = 0; i < n; ++i)
    if (btw(v[i], v[i + 1], p))
      return 0;
  for (int i = 0; i < n; ++i)
    if (banana(v[i], v[i + 1], p, {(ll)2e9 + 7, p.S + 1LL}))
      ans *= -1;
  //對於任意 p 到 {W, p.S+1} 的向量中不會有整數點存在，其中需要滿足 {W, p.S+1}
  //必須很遠，保證在多邊形外
  return ans;
}
void solve() {
  int n;
  cin >> n;
  vector<pll> v(n);
  for (pll &e : v)
    cin >> e;
  v.pb(v[0]);
  ll ans = area2(v) + 2, ans2 = 0;
  for (int i = 0; i < n; ++i) {
    if (v[i].F == v[i + 1].F)
      ans2 += abs(v[i].S - v[i + 1].S);
    else if (v[i].S == v[i + 1].S)
      ans2 += abs(v[i].F - v[i + 1].F);
    else
      ans2 += gcd(abs(v[i].F - v[i + 1].F), abs(v[i].S - v[i + 1].S));
  }
  cout << (ans - ans2) / 2 << " " << ans2;
}
int main() {
  int t = 1;
  // cin>>t;
  for (; t--;) {
    solve();
  }
}