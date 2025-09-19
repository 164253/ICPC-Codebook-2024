#include <bits/stdc++.h>
#define int long long
using namespace std;

int n, m;
vector<int> v[1005];
int head[1005];
int c[1005][1005];
int lv[1005];
int ans = 0;

bool bfs() {
    memset(head, 0, sizeof(head));
    memset(lv, 0, sizeof(lv));
    queue<int> q;
    q.push(1);
    while(!q.empty()) {
        int now = q.front();
        q.pop();
        if(now == n) continue;
        for(int i : v[now]) {
            if(i != 1 && c[now][i] && !lv[i]) {
                lv[i] = lv[now] + 1;
                q.push(i);
            }
        }
    }
    return lv[n];
}

int dfs(int x, int flow) {
    int ret = 0;
    if(x == n) return flow;
    for(int i = head[x]; i < v[x].size(); i++) {
        int y = v[x][i];
        head[x] = y;
        if(c[x][y] && lv[y] == lv[x] + 1) {
            int d = dfs(y, min(flow, c[x][y]));
            flow -= d;
            c[x][y] -= d;
            c[y][x] += d;
            ret += d;
        }
    }
    return ret;
}

signed main() {
    cin >> n >> m;
    while(m--) {
        int x, y, z;
        cin >> x >> y >> z;
        if(c[x][y] || c[y][x]) {
            c[x][y] += z;
            continue;
        }
        v[x].push_back(y);
        v[y].push_back(x);
        c[x][y] = z;
    }
    while(bfs()) {
        ans += dfs(1, INT_MAX);
    }
    cout << ans;
}
