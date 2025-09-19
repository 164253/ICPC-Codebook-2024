#include <bits/stdc++.h>
#define int long long
using namespace std;

int n, q;
struct node {
    int data, lson, rson, tag;
    int rv() { return data + tag; }
};

node tree[20000005];
int a[200005];
int now = 1;
int mx = 1000000005;

void push(int index) {
    if(!tree[index].lson) {
        tree[index].lson = ++now;
    }
    if(!tree[index].rson) {
        tree[index].rson = ++now;
    }
    int lson = tree[index].lson;
    int rson = tree[index].rson;
    tree[lson].tag += tree[index].tag;
    tree[rson].tag += tree[index].tag;
    tree[index].data = tree[index].rv();
    tree[index].tag = 0;
}

void modify(int l, int r, int L, int R, int val, int index) {
    if(l == L && r == R) {
        tree[index].tag += val;
        return;
    }
    int mid = (l + r) >> 1;
    push(index);
    int lson = tree[index].lson;
    int rson = tree[index].rson;
    if(R <= mid) {
        modify(l, mid, L, R, val, lson);
    } else if(L > mid) {
        modify(mid + 1, r, L, R, val, rson);
    } else {
        modify(l, mid, L, mid, val, lson);
        modify(mid + 1, r, mid + 1, R, val, rson);
    }
    tree[index].data = tree[lson].rv() + tree[rson].rv();
}

int query(int l, int r, int L, int R, int index) {
    // cout << L << " " << R << "\n";
    if(l == L && r == R) {
        return tree[index].rv();
    }
    int mid = (l + r) >> 1;
    push(index);
    int lson = tree[index].lson;
    int rson = tree[index].rson;
    if(R <= mid) {
        return query(l, mid, L, R, lson);
    }
    if(L > mid) {
        return query(mid + 1, r, L, R, rson);
    }
    return query(l, mid, L, mid, lson) +
           query(mid + 1, r, mid + 1, R, rson);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> q;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        modify(1, mx, a[i], a[i], 1, 1);
    }
    while(q--) {
        char mode;
        int x, y;
        cin >> mode;
        if(mode == '?') {
            cin >> x >> y;
            cout << query(1, mx, x, y, 1) << "\n";
        } else {
            cin >> x >> y;
            modify(1, mx, a[x], a[x], -1, 1);
            a[x] = y;
            modify(1, mx, a[x], a[x], 1, 1);
        }
    }
}