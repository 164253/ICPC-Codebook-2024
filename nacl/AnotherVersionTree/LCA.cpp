#define N 100005
#define LG 15
int dep[N], par[N][LG], sub[N];
vector<int> g[N];
void dfs(int now = 1, int pre = 0) {
    dep[now] = dep[pre] + 1;
    par[now][0] = pre;
    sub[now] = 1;
    for(int e : g[now])
        if(e != pre) dfs(e, now), sub[now] += sub[e];
}
int jmp(int x, int k) {
    for(int i = LG; i--;)
        for(; k >= 1 << i; k -= 1 << i) x = par[x][i];
    return x;
}
int lca(int a, int b) {
    if(dep[a] > dep[b]) swap(a, b);
    b = jmp(b, dep[b] - dep[a]);
    if(a == b) return a;
    for(int i = LG; i--;)
        for(; par[a][i] != par[b][i]; b = par[b][i])
            a = par[a][i];
    return par[a][0];
}
int main() {
    int n;
    cin >> n;
    for(int i = n, u, v; --i;)
        cin >> u >> v, g[u].pb(v), g[v].pb(u);
    dfs();
    for(int i = 1; i < LG; ++i)
        for(int j = 1; j <= n; ++j)
            par[j][i] = par[par[j][i - 1]][i - 1];
    int k = lca(1, n);
}
//點編號 1~n，建的無向圖但改 dfs
//就能變有向，改有向記得邊要反著建 dep[n] 代表 n 的深度(1
// base)，par[i][j] 代表 i 往上 1<<j 步的祖先是誰，不存在則是
// 0，sub[i] 代表 i 的子樹大小 jmp(i,j) 代表 i 往上 j
// 步的祖先是誰

#pragma GCC optimize(                                          \
    "Ofast,fast-math,unroll-loops,no-stack-protector")
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define N 200005
#define pii pair<int, int>
#define V vector
#define inf 1000000007
#define M 200005
#define LG 18
#define pii pair<int, int>
#define ppp pair<pii, pii>
char buf[1 << 22], *p1, *p2;
int p[12];
#define gc()                                                   \
    (p1 == p2 &&                                               \
             (p2 = (p1 = buf) + fread(buf, 1, 1 << 22, stdin), \
              p1 == p2)                                        \
         ? EOF                                                 \
         : *p1++)
inline int gi() {
    int x = 0;
    for(char c; '0' <= (c = gc()) && c <= '9'; x += c - '0')
        x *= 10;
    return x;
}
inline void pi(int x, char c = ' ') {
    if(!x) putchar('0');
    int i = 0;
    for(; x; x /= 10) p[i++] = x % 10;
    for(; i--;) putchar(p[i] + '0');
    putchar(c);
}
int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m, q;
    cin >> n >> m >> q;
    vector<ppp> g(m);
    bitset<M> ans;
    vector<vector<pii>> adj(n + 1, vector<pii>());
    for(int i = 0; i < m; ++i) {
        auto &[p1, p2] = g[i];
        auto &[w, idx] = p1;
        auto &[u, v] = p2;
        cin >> u >> v >> w;
        idx = i;
    }
    sort(g.begin(), g.end());
    vector<ll> dsu(n + 1, -1);
    auto qry = [&dsu](auto qry, int x) -> int {
        return dsu[x] < 0 ? x : dsu[x] = qry(qry, dsu[x]);
    };
    auto upd = [&dsu, &qry](int u, int v) -> void {
        if(dsu[u = qry(qry, u)] > dsu[v = qry(qry, v)])
            swap(u, v);
        dsu[u] += dsu[v];
        dsu[v] = u;
    };
    for(auto &[p1, p2] : g) {
        auto &[w, idx] = p1;
        auto &[u, v] = p2;
        if(qry(qry, u) != qry(qry, v))
            upd(u, v), adj[u].pb({v, w}), adj[v].pb({u, w});
    }
    vector<vector<int>> par(n + 1, vector<int>(LG)),
        mx(n + 1, vector<int>(LG));
    vector<int> dep(n + 1);
    auto dfs = [&par, &mx, &dep, &adj](auto dfs, int now,
                                       int p = 0,
                                       int w = 0) -> void {
        par[now][0] = p;
        mx[now][0] = w;
        dep[now] = dep[p] + 1;
        for(auto &[e, w] : adj[now])
            if(e != p) dfs(dfs, e, now, w);
    };
    dfs(dfs, 1);
    for(int i = 1; i < LG; ++i)
        for(int j = 1; j <= n; ++j)
            par[j][i] = par[par[j][i - 1]][i - 1],
            mx[j][i] =
                max(mx[j][i - 1], mx[par[j][i - 1]][i - 1]);
    auto lca = [&par, &dep](int u, int v) -> int {
        if(dep[u] > dep[v]) swap(u, v);
        for(int i = LG; i--;)
            if((1 << i) & (dep[v] - dep[u])) v = par[v][i];
        if(u == v) return u;
        for(int i = LG; i--;)
            if(par[u][i] != par[v][i])
                u = par[u][i], v = par[v][i];
        return par[u][0];
    };
    auto path = [&par, &mx, &dep](int k, int x) -> int {
        int ans = 0;
        for(int i = LG; i--;)
            if((1 << i) & (dep[x] - dep[k]))
                ans = max(ans, mx[x][i]), x = par[x][i];
        return ans;
    };
    for(auto &[p1, p2] : g) {
        auto &[w, idx] = p1;
        auto &[u, v] = p2;
        int k = lca(u, v);
        ans[idx] = max(path(k, u), path(k, v)) >= w;
    }
    for(int i = 0; i < m; ++i)
        cout << i << " "
             << (const char[2][5]){"NO\n", "YES\n"}[ans[i]];
    cout << "\n";
    for(int k; q--;) {
        cin >> k;
        int flag = 1;
        for(int x; k--;) {
            cin >> x;
            if(!ans[x - 1]) flag = 0;
        }
        cout << (const char[2][5]){"NO\n", "YES\n"}[flag];
    }
}