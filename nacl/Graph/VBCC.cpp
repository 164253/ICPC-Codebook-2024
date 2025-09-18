#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define pii pair<int, int>
#define N 100005
vector<int> adj[N], bcc[N];
stack<int> st;
int dfn[N], low[N], tag, bc, root;
bitset<N> ap;
void dfs(int now, int par = -1) {
  st.push(now);
  low[now] = dfn[now] = ++tag;
  int f = 0;
  for (int e : adj[now] | views::reverse) {
    if (e == par)
      continue;
    if (!dfn[e]) {
      dfs(e, now), low[now] = min(low[now], low[e]);
      if (low[e] >= dfn[now]) {
        if (++f > 1 || now != root)
          ap[now] = 1;
        ++bc;
        for (; st.top() != now; st.pop())
          bcc[bc].pb(st.top());
        bcc[bc].pb(now);
      }
    } else
      low[now] = min(low[now], dfn[e]);
  }
}
int main() {
  int n, m, u, v;
  cin >> n >> m;
  vector<pii> g(m);
  for (auto &[u, v] : g)
    cin >> u >> v, adj[u].pb(v), adj[v].pb(u);
  for (root = 1; root <= n; ++root)
    if (!dfn[u])
      dfs(root);
  int ans = 0;
  for (int i : views::iota(1) | views::take(n))
    if (ap[i])
      ++ans;
  cout << ans << "\n";
  for (int i : views::iota(1) | views::take(n))
    if (ap[i])
      cout << i << " ";
}