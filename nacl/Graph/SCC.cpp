int n, m;
vector<int> v[100005];
int d[100005];
int low[100005];
int cnt = 0;
stack<int> s;
int scc[100005];
int now = 0;

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
