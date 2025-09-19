template <class T> class Dsu {
#define N 2000005
  public:
    T dsu[N], size[N];
    Dsu(T n) {
        for(; n; --n) dsu[n] = n, size[n] = 1;
    }
    T qry(T x) {
        if(dsu[x] == x) return x;
        return dsu[x] = qry(dsu[x]);
    }
    void merge(T a, T b) {
        a = qry(a);
        b = qry(b);
        if(a == b) return;
        if(size[a] < size[b])
            dsu[a] = b, size[b] += size[a];
        else
            dsu[b] = a, size[a] += size[b];
    }
#undef N
};
/*1based 初始化為dsu[x]=x 路徑壓縮+啟發式合併*/