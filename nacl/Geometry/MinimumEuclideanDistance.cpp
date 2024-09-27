#include <bits/stdc++.h>
#define int long long
#define pii pair<int, int>
using namespace std;

int n;
vector<pair<int, int>> v;
set<pair<int, int>> s;
int dd = LONG_LONG_MAX;

int dis(pii x, pii y) {
  return (x.first - y.first) * (x.first - y.first) +
         (x.second - y.second) * (x.second - y.second);
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  for (int i = 0; i < n; i++) {
    int x, y;
    cin >> x >> y;
    x += 1000000000;
    v.push_back({x, y});
  }
  sort(v.begin(), v.end());
  int l = 0;
  for (int i = 0; i < n; i++) {
    int d = ceil(sqrt(dd));
    while (l < i && v[i].first - v[l].first > d) {
      s.erase({v[l].second, v[l].first});
      l++;
    }
    auto x = s.lower_bound({v[i].second - d, 0});
    auto y = s.upper_bound({v[i].second + d, 0});
    for (auto it = x; it != y; it++) {
      dd = min(dd, dis({it->second, it->first}, v[i]));
    }
    s.insert({v[i].second, v[i].first});
  }
  cout << dd;
}
