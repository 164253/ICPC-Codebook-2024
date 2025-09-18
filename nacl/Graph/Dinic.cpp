#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll inf = 8e18;
#define N 505
#define pb push_back
struct pp {
  int from, to;
  ll flow;
};
int t, lvl[N], p[N];
vector<int> g[N];
vector<pp> edge;
int bfs(int s) {
  queue<int> q;
  for (q.push(s), lvl[s] = 1; !q.empty(); q.pop()) {
    int u = q.front();
    for (int e : g[u]) {
      int v = edge[e].to;
      if (lvl[v] || !edge[e].flow)
        continue;
      lvl[v] = lvl[u] + 1;
      q.push(v);
    }
  }
  return lvl[t];
}
ll dfs(int u, ll f = inf) {
  if (u == t || !f)
    return f;
  ll ans = 0;
  for (int &i = p[u]; i < g[u].size(); ++i) {
    pp &e = edge[g[u][i]], &b = edge[g[u][i] ^ 1];
    if (lvl[e.to] == lvl[u] + 1) {
      ll c = dfs(e.to, min(e.flow, f));
      e.flow -= c;
      b.flow += c;
      f -= c;
      ans += c;
    }
  }
  return ans;
}
ll dinic(int s) {
  ll ans = 0;
  for (; bfs(s); memset(lvl, 0, sizeof lvl))
    for (ll k; k = (memset(p, 0, sizeof(p)), dfs(s));)
      ans += k;
  return ans;
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int n, m, cnt = 0;
  for (cin >> n >> m; m--;) {
    int u, v;
    ll f;
    cin >> u >> v >> f;
    g[u].pb(cnt++);
    g[v].pb(cnt++);
    edge.pb({u, v, f});
    edge.pb({v, u, 0});
  }
  t = n;
  cout << dinic(1);
}