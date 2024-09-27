struct line {
  int a, b = 1000000000000000;
  int y(int x) { return a * x + b; }
};

line tree[4000005];
int n, x;
int s[200005];
int f[200005];
int dp[200005];

void update(line ins, int l = 1, int r = 1e6, int index = 1) {
  if (l == r) {
    if (ins.y(l) < tree[index].y(l)) {
      tree[index] = ins;
    }
    return;
  }
  int mid = (l + r) >> 1;
  if (tree[index].a < ins.a)
    swap(tree[index], ins);
  if (tree[index].y(mid) > ins.y(mid)) {
    swap(tree[index], ins);
    update(ins, l, mid, index << 1);
  } else {
    update(ins, mid + 1, r, index << 1 | 1);
  }
}

int query(int x, int l = 1, int r = 1000000, int index = 1) {
  int cur = tree[index].y(x);
  if (l == r) {
    return cur;
  }
  int mid = (l + r) >> 1;
  if (x <= mid) {
    return min(cur, query(x, l, mid, index << 1));
  } else {
    return min(cur, query(x, mid + 1, r, index << 1 | 1));
  }
}
