#include <bits/stdc++.h>
#define int long long
using namespace std;

int n, m;
vector<int> v[200005];
int d[200005];
int low[200005];
int cnt = 0;
int now = 0;
int scc[200005];
stack<int> s;
int op[200005];
vector<int> v2[200005];
int ind[200005];
queue<int> q;
int ans[200005];

int no(int x) {
  if (x > m)
    return x - m;
  return x + m;
}

void dfs(int x) {
  d[x] = low[x] = ++cnt;
  s.push(x);
  for (int i : v[x]) {
    if (scc[i])
      continue;
    if (d[i]) {
      low[x] = min(low[x], d[i]);
    } else {
      dfs(i);
      low[x] = min(low[x], low[i]);
    }
  }
  if (d[x] == low[x]) {
    now++;
    while (!s.empty()) {
      int k = s.top();
      s.pop();
      scc[k] = now;
      if (k == x)
        break;
    }
  }
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> m;
  while (n--) {
    char a, b;
    int x, y;
    cin >> a >> x >> b >> y;
    if (a == '-')
      x = no(x);
    if (b == '-')
      y = no(y);
    v[no(x)].push_back(y);
    v[no(y)].push_back(x);
  }
  for (int i = 1; i <= 2 * m; i++) {
    if (!d[i]) {
      dfs(i);
    }
  }
  for (int i = 1; i <= m; i++) {
    if (scc[i] ^ scc[i + m]) {
      op[scc[i]] = scc[i + m];
      op[scc[i + m]] = scc[i];
    } else {
      cout << "IMPOSSIBLE";
      exit(0);
    }
  }
  for (int i = 1; i <= 2 * m; i++) {
    for (int j : v[i]) {
      if (scc[i] ^ scc[j]) {
        v2[scc[j]].push_back(scc[i]);
        ind[scc[i]]++;
      }
    }
  }
  for (int i = 1; i <= now; i++) {
    if (!ind[i]) {
      q.push(i);
    }
  }
  while (!q.empty()) {
    int k = q.front();
    q.pop();
    if (!ans[k]) {
      ans[k] = 1;
      ans[op[k]] = 2;
    }
    for (int i : v2[k]) {
      ind[i]--;
      if (!ind[i]) {
        q.push(i);
      }
    }
  }
  for (int i = 1; i <= m; i++) {
    if (ans[scc[i]] == 1) {
      cout << "+ ";
    } else {
      cout << "- ";
    }
  }
}
