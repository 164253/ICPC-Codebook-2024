#include <bits/stdc++.h>
#define int long long
using namespace std;

int n, q;
int a[200005];
int r[200005];
int d[200005];
int cycle[200005];
int len[200005];
int cnt = 0;
vector<int> v[200005];
bitset<200005> vis1;
bitset<200005> vis2;

void findcycle(int x) {
    while(!vis1[x]) {
        vis1[x] = 1;
        x = a[x];
    }
    cnt++;
    cycle[x] = cnt;
    r[x] = 0;
    len[cnt] = 1;
    int temp = a[x];
    while(temp ^ x) {
        r[temp] = len[cnt];
        len[cnt]++;
        cycle[temp] = cnt;
        temp = a[temp];
    }
}

void dfs(int x) {
    if(vis2[x]) return;
    vis2[x] = 1;
    for(int i : v[x]) {
        dfs(i);
    }
}

void dfs2(int x) {
    if(cycle[x] || d[x]) return;
    dfs2(a[x]);
    d[x] = d[a[x]] + 1;
    r[x] = r[a[x]];
    cycle[x] = cycle[a[x]];
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        v[i].push_back(a[i]);
        v[a[i]].push_back(i);
    }
    for(int i = 1; i <= n; i++) {
        if(!vis2[i]) {
            findcycle(i);
            dfs(i);
        }
    }
    for(int i = 1; i <= n; i++) {
        if(!cycle[i] && !r[i]) {
            dfs2(i);
        }
    }
    for(int i = 1; i <= n; i++) {
        cout << d[i] + len[cycle[i]] << " ";
    }
}
