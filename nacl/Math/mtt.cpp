#include <bits/stdc++.h>
using namespace std;
// https://www.luogu.com.cn/article/08nmgxd1
namespace poly {
long double const pi = acos(-1);
struct comp {
    long double r, i;
    comp() { r = i = 0; }
    comp(long double x, long double y) { r = x, i = y; }
    comp conj() { return comp(r, -i); }
    friend comp operator+(comp x, comp y) {
        return comp(x.r + y.r, x.i + y.i);
    }
    friend comp operator-(comp x, comp y) {
        return comp(x.r - y.r, x.i - y.i);
    }
    friend comp operator*(comp x, comp y) {
        return comp(x.r * y.r - x.i * y.i,
                    x.i * y.r + x.r * y.i);
    }
};
typedef long long ll;
int r[400005];
comp a[400005], b[400005], c[400005], d[400005];
void fft(comp *f, int n, int op) {
    for(int i = 1; i < n; i++)
        r[i] = (r[i >> 1] >> 1) + ((i & 1) ? (n >> 1) : 0);
    for(int i = 1; i < n; i++)
        if(i < r[i]) swap(f[i], f[r[i]]);
    for(int len = 2; len <= n; len <<= 1) {
        int q = len >> 1;
        comp wn = comp(cos(pi / q), op * sin(pi / q));
        for(int i = 0; i < n; i += len) {
            comp w = comp(1, 0);
            for(int j = i; j < i + q; j++, w = w * wn) {
                comp d = f[j + q] * w;
                f[j + q] = f[j] - d;
                f[j] = f[j] + d;
            }
        }
    }
}
void mtt(int *f, int *g, int *h, int n, int p) {
    for(int i = 0; i < n; i++) {
        a[i].r = (f[i] >> 15);
        a[i].i = (f[i] & 32767);
        c[i].r = (g[i] >> 15);
        c[i].i = (g[i] & 32767);
    }
    fft(a, n, 1), fft(c, n, 1);
    for(int i = 1; i < n; i++) b[i] = a[n - i].conj();
    b[0] = a[0].conj();
    for(int i = 1; i < n; i++) d[i] = c[n - i].conj();
    d[0] = c[0].conj();
    for(int i = 0; i < n; i++) {
        comp aa = (a[i] + b[i]) * comp(0.5, 0);
        comp bb = (a[i] - b[i]) * comp(0, -0.5);
        comp cc = (c[i] + d[i]) * comp(0.5, 0);
        comp dd = (c[i] - d[i]) * comp(0, -0.5);
        a[i] = aa * cc + comp(0, 1) * (aa * dd + bb * cc);
        b[i] = bb * dd;
    }
    fft(a, n, -1), fft(b, n, -1);
    for(int i = 0; i < n; i++) {
        int aa = (ll)(a[i].r / n + 0.5) % p,
            bb = (ll)(a[i].i / n + 0.5) % p,
            cc = (ll)(b[i].r / n + 0.5) % p;
        h[i] = ((1ll * aa * (1 << 30) + 1ll * bb * (1 << 15) +
                 cc) %
                    p +
                p) %
               p;
    }
}
} // namespace poly
using namespace poly;
int f[400005], g[400005], h[400005];
// 400005 is 2 * (n + m)
int main() {
    int n, m, p;
    scanf("%d%d%d", &n, &m, &p);
    for(int i = 0; i <= n; i++) scanf("%d", &f[i]);
    for(int i = 0; i <= m; i++) scanf("%d", &g[i]);
    int lim = 1;
    while(lim <= (n + m)) lim <<= 1;
    mtt(f, g, h, lim, p);
    for(int i = 0; i <= n + m; i++) printf("%d ", h[i]);
    return 0;
}
