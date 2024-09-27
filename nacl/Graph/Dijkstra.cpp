int n, m;
vector<pair<int, int>> v[100005];
bitset<100005> vis;
int dis[100005];

void dijkstra(int x) {
  priority_queue<pair<int, int>, vector<pair<int, int>>,
                 greater<pair<int, int>>>
      pq;
  memset(dis, 0x3f, sizeof(dis));
  dis[x] = 0;
  pq.push({0, x});
  while (!pq.empty()) {
    pair<int, int> now = pq.top();
    pq.pop();
    if (vis[now.second])
      continue;
    vis[now.second] = 1;
    for (auto [i, w] : v[now.second]) {
      if (vis[i])
        continue;
      if (dis[now.second] + w < dis[i]) {
        dis[i] = dis[now.second] + w;
        pq.push({dis[i], i});
      }
    }
  }
}
