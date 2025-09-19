#include <bits/stdc++.h>
#define int long long
using namespace std;

int tree[800005];

int n, q;
int a[200005];
int st[200005];
int tp[200005];
int p[200005];
int cnt = 0;
int d[200005];
int si[200005];
vector<int> v[200005];
int b[200005];

void build(int l = 1, int r = n, int index = 1) {
    if(l == r) {
        tree[index] = b[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, index << 1);
    build(mid + 1, r, index << 1 | 1);
    tree[index] = max(tree[index << 1], tree[index << 1 | 1]);
}

int query(int L, int R, int l = 1, int r = n, int index = 1) {
    if(L == l && r == R) {
        return tree[index];
    }
    int mid = (l + r) >> 1;
    if(R <= mid) {
        return query(L, R, l, mid, index << 1);
    }
    if(L > mid) {
        return query(L, R, mid + 1, r, index << 1 | 1);
    }
    return max(query(L, mid, l, mid, index << 1),
               query(mid + 1, R, mid + 1, r, index << 1 | 1));
}

void modify(int x, int val, int l = 1, int r = n,
            int index = 1) {
    if(l == r) {
        tree[index] = val;
        return;
    }
    int mid = (l + r) >> 1;
    if(x <= mid) {
        modify(x, val, l, mid, index << 1);
    } else {
        modify(x, val, mid + 1, r, index << 1 | 1);
    }
    tree[index] = max(tree[index << 1], tree[index << 1 | 1]);
}

void dfs(int x, int pre) {
    si[x] = 1;
    for(int i : v[x]) {
        if(i == pre) continue;
        p[i] = x;
        d[i] = d[x] + 1;
        dfs(i, x);
        si[x] += si[i];
    }
}

void dfs2(int x, int pre, int t) {
    tp[x] = t;
    st[x] = ++cnt;
    int ma = 0;
    for(int i : v[x]) {
        if(i == pre) continue;
        if(si[i] > si[ma]) {
            ma = i;
        }
    }
    if(!ma) return;
    dfs2(ma, x, t);
    for(int i : v[x]) {
        if(i == pre || i == ma) {
            continue;
        }
        dfs2(i, x, i);
    }
}

int f(int x, int y) {
    int ret = 0;
    while(tp[x] ^ tp[y]) {
        if(d[tp[x]] < d[tp[y]]) {
            swap(x, y);
        }
        ret = max(ret, query(st[tp[x]], st[x]));
        x = p[tp[x]];
    }
    if(d[x] > d[y]) swap(x, y);
    ret = max(ret, query(st[x], st[y]));
    return ret;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> q;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        v[x].push_back(y);
        v[y].push_back(x);
    }
    dfs(1, 0);
    dfs2(1, 0, 1);
    for(int i = 1; i <= n; i++) {
        b[st[i]] = a[i];
    }
    build();
    while(q--) {
        int mode, x, y;
        cin >> mode >> x >> y;
        if(mode == 1) {
            modify(st[x], y);
        } else {
            cout << f(x, y) << " ";
        }
    }
}