#pragma GCC optimize(                                          \
    "Ofast,fast-math,unroll-loops,no-stack-protector")
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define V vector
#define pb push_back
#define all(x) x.begin(), x.end()
V<ll> v;
ll f(ll k, ll now = 0, ll p = v.size() - 1, ll ans = 0) {
    if(k >= 1 << p) {
        k -= 1 << p;
        ans = max(ans, ans ^ v[now]);
    } else
        ans = min(ans, ans ^ v[now]);
    if(!p) return ans;
    return f(k, now + 1, p - 1, ans);
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ll n, k;
    cin >> n >> k;
    for(ll x, i = 0; i < n; ++i) {
        cin >> x;
        for(ll &e : v) x = min(x, x ^ e);
        if(x) v.pb(x);
    }
    sort(all(v), greater<ll>());
    ll t = n - v.size(), a = k >> t,
       b = k & ((1 << min(t, 20LL)) - 1), i = 0;
    for(; a--; ++i)
        for(ll j = 1 << t, p = f(i); j--;) cout << p << " ";
    for(i = f(i); b--;) cout << i << " ";
}