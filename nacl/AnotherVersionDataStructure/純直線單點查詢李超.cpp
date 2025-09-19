// luogu P4254 李超
#include <bits/stdc++.h>
using namespace std;
#define N 50005
struct Line {
    double a, b; // ax+b
    Line(double _a = -1, double _b = -1e6)
        : a(_a), b(_b - _a) {}
    double operator()(int x) { return a * x + b; }
} seg[N << 2];
#define lid (id << 1)
#define rid (id << 1 | 1)
#define M (L + R >> 1)
void ins(Line l, int L = 1, int R = N, int id = 1) {
    if(L == R) {
        if(seg[id].a < 0 || l(M) > seg[id](M)) seg[id] = l;
        return;
    }
    if(l(M) > seg[id](M)) swap(l, seg[id]);
    if(l.a > seg[id].a)
        ins(l, M + 1, R, rid);
    else
        ins(l, L, M, lid);
}
double qry(int x, int L = 1, int R = N, int id = 1) {
    if(L == R) return seg[id](x);
    if(x <= M) return max(qry(x, L, M, lid), seg[id](x));
    return max(seg[id](x), qry(x, M + 1, R, rid));
}
int main() {
    int n;
    for(cin >> n; n--;) {
        string s;
        cin >> s;
        if(s[0] == 'Q') {
            int x;
            cin >> x;
            cout << max(0, ((int)(qry(x) * 100)) / 10000)
                 << "\n";
        } else {
            double s, p;
            cin >> s >> p;
            ins(Line(p, s));
        }
    }
}