#include <bits/stdc++.h>
#define int long long
#define fastio                                                                 \
  ios_base::sync_with_stdio(0);                                                \
  cin.tie(0);                                                                  \
  cout.tie(0);

using namespace std;

template <typename T> pair<T, T> operator-(pair<T, T> a, pair<T, T> b) {
  return make_pair(a.first - b.first, a.second - b.second);
}

template <typename T> T cross(pair<T, T> a, pair<T, T> b) {
  return a.first * b.second - a.second * b.first;
}

template <typename T> vector<pair<T, T>> getCH(vector<pair<T, T>> v) {
  int n = v.size();
  sort(v.begin(), v.end());
  vector<pair<T, T>> hull;
  for (int i = 0; i < 2; i++) {
    int t = hull.size();
    for (auto x : v) {
      while (hull.size() - t >= 2 &&
             cross(hull[hull.size() - 1] - hull[hull.size() - 2],
                   x - hull[hull.size() - 2]) <= 0)
        hull.pop_back();
      hull.push_back(x);
    }
    hull.pop_back();
    reverse(v.begin(), v.end());
  }
  return hull;
}