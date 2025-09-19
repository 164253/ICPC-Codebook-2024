// cses Planets Queries II 基環樹森林模板
#include <bits/stdc++.h>
using namespace std;
#define N 200005
#define pb push_back
// int cyc[i]=1~n 代表i屬於哪顆樹
// bitset incyc[i]=0/1 代表i是否在環上
// int len[k]=1~n 代表第k棵樹的環長度
// int num[i]=1~n 如果incyc[i]代表的是在環上的編號
// 否則代表的是環上最近的點的編號 int dis[i]=0~n-1
// 代表到環上最近點的距離 若i在環上則為0
int tag = 1, cyc[N], len[N], num[N], dis[N], nxt[N][19];
bitset<N> vis, incyc;
vector<int> path;
void dfs(int now) {
    if(vis[now]) {
        int i = 1;
        for(int k; k = path.back(), path.pop_back(),
                   k != now && !path.empty();
            ++i) {
            cyc[k] = tag;
            incyc[k] = 1;
            num[k] = i;
        }
        cyc[now] = tag;
        incyc[now] = 1;
        num[now] = i;
        len[tag] = i;
        ++tag;
        return;
    }
    vis[now] = 1;
    path.pb(now);
    if(!cyc[nxt[now][0]]) dfs(nxt[now][0]);
    if(cyc[now]) return;
    cyc[now] = cyc[nxt[now][0]];
    num[now] = num[nxt[now][0]];
    dis[now] = dis[nxt[now][0]] + 1;
}
int jmp(int a, int x) {
    for(int k = 19; k--;)
        for(; 1 << k <= x;) x -= 1 << k, a = nxt[a][k];
    return a;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, q, i = 1, u, v;
    for(cin >> n >> q; i <= n; ++i) cin >> nxt[i][0];
    for(int k = 1; k < 19; ++k)
        for(i = 1; i <= n; ++i)
            nxt[i][k] = nxt[nxt[i][k - 1]][k - 1];
    for(i = 1; i <= n; ++i)
        if(!cyc[i]) path.clear(), dfs(i);
    for(; q--;) {
        cin >> u >> v;
        if(cyc[u] == cyc[v]) {
            if(incyc[v])
                cout << (!incyc[u] ? dis[u] : 0) +
                            (num[u] - num[v] + len[cyc[u]]) %
                                len[cyc[u]]
                     << "\n";
            else if(num[u] == num[v] && dis[u] >= dis[v] &&
                    jmp(u, dis[u] - dis[v]) == v)
                cout << dis[u] - dis[v] << "\n";
            else
                cout << "-1\n";
        } else
            cout << "-1\n";
    }
}