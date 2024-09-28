#include <bits/stdc++.h>
#define int long long
using namespace std;

int n, q;
int a[200005][21];
int d[200005];
vector<int> v[200005];

void init() {
  for (int j = 1; j < 21; j++) {
    for (int i = 1; i <= n; i++) {
      a[i][j] = a[a[i][j - 1]][j - 1];
    }
  }
}

void dfs(int x, int pre) {
  for (int i : v[x]) {
    if (i == pre) {
      continue;
    }
    a[i][0] = x;
    d[i] = d[x] + 1;
    dfs(i, x);
  }
}

int lca(int x, int y) {
  while (d[x] ^ d[y]) {
    if (d[x] < d[y]) {
      swap(x, y);
    }
    int k = __lg(d[x] - d[y]);
    x = a[x][k];
  }
  if (x == y) {
    return x;
  }
  for (int i = 20; i >= 0; i--) {
    if (a[x][i] != a[y][i]) {
      x = a[x][i];
      y = a[y][i];
    }
  }
  return a[x][0];
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> q;
  for (int i = 1; i < n; i++) {
    int x, y;
    cin >> x >> y;
    v[x].push_back(y);
    v[y].push_back(x);
  }
  dfs(1, 0);
  init();
  while (q--) {
    int x, y;
    cin >> x >> y;
    int k = lca(x, y);
    cout << (d[x] + d[y] - 2 * d[k]) << "\n";
  }
}