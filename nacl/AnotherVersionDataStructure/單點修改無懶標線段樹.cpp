template <class T> class Seg {
#define lid id << 1
#define rid id << 1 | 1
#define M (L + R >> 1)
#define N 200005
  public:
    T a[N], seg[N << 2];
    Seg() {
        for(int i = 1; i <= n; ++i) cin >> a[i];
        init();
    }
    T update(int pos, int val, int L = 1, int R = n,
             int id = 1) {
        if(L == R) return seg[id] = val;
        if(pos > M)
            return seg[id] = seg[lid] +
                             update(pos, val, M + 1, R, rid);
        return seg[id] = update(pos, val, L, M, lid) + seg[rid];
    }
    T qry(int l, int r, int L = 1, int R = n, int id = 1) {
        if(l <= L && R <= r) return seg[id];
        if(L == R) return seg[id];
        int M = L + R >> 1;
        if(l > M) return qry(l, r, M + 1, R, rid);
        if(r <= M) return qry(l, r, L, M, lid);
        return qry(l, M, L, M, lid) +
               qry(M + 1, r, M + 1, R, rid);
    }

  private:
    T init(int l = 1, int r = n, int id = 1) {
        if(l == r) return seg[id] = a[l];
        int m = l + r >> 1;
        return seg[id] = init(l, m, lid) + init(m + 1, r, rid);
    }
#undef lid
#undef rid
#undef N
};
/*1based陣列 1based id 單點修改 預設維護區間和*/