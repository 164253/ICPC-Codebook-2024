// luogu P4097 區間插線段李超
#include <bits/stdc++.h>
using namespace std;
#define N 50005
struct Line {
    double a, b;
    int l, r, id; // ax+b{l<=x<=r}
    Line(double _a = -1e6, double _b = -1, int _l = 1,
         int _r = N, int _id = 0)
        : a(_a), b(_b), l(_l), r(_r), id(_id) {}
    double operator()(int x) { return a * x + b; }
} line[N];
int seg[N << 2];
#define lid (id << 1)
#define rid (id << 1 | 1)
#define M (L + R >> 1)
#define eps 1e-6
void ins(int l, int L = 1, int R = N, int id = 1) {
    // cout<<"ins{"<<line[l].a<<","<<line[l].b<<","<<line[l].l<<","<<line[l].r<<"}"<<L<<"
    // "<<R<<"\n";
    if(line[l].r < L || R < line[l].l) return;
    if(L == R) {
        if(line[l](M) - line[seg[id]](M) > eps) seg[id] = l;
        return;
    }
    if(line[l].l <= M && M <= line[l].r &&
       line[l](M) - line[seg[id]](M) > eps)
        swap(l, seg[id]);
    if(line[l].l <= L && R <= line[l].r) {
        if(line[l].a - line[seg[id]].a > eps)
            ins(l, M + 1, R, rid);
        else
            ins(l, L, M, lid);
    }
    /*if(line[l].a>line[seg[id]].a)*/ ins(l, M + 1, R, rid);
    /*else */ ins(l, L, M, lid);
}
int qry(int x, int L = 1, int R = N, int id = 1) {
    // cout<<"qry"<<x<<"{"<<line[seg[id]].a<<","<<line[seg[id]].b<<"}"<<L<<"
    // "<<R<<" "<<id<<"\n";
    if(L == R) return seg[id];
    int k = (x <= M ? qry(x, L, M, lid)
                    : qry(x, M + 1, R, rid)),
        not_k = 0, not_seg = 0;
    if(line[k].r < x || x < line[k].l) not_k = 1;
    if(line[seg[id]].r < x || x < line[seg[id]].l) not_seg = 1;
    if(not_k && not_seg) return 0;
    if(not_k) return seg[id];
    if(not_seg) return k;
    return line[k](x) - line[seg[id]](x) > eps ? k : seg[id];
}
int main() {
    int n, ans = 0, p = 1;
    for(cin >> n; n--;) {
        int op;
        cin >> op;
        if(op) {
            int x0, y0, x1, y1;
            cin >> x0 >> y0 >> x1 >> y1;
            x0 = (x0 + ans - 1) % 39989 + 1;
            y0 = (y0 + ans - 1) % 1000000000 + 1;
            x1 = (x1 + ans - 1) % 39989 + 1;
            y1 = (y1 + ans - 1) % 1000000000 + 1;
            if(x0 > x1) swap(x0, x1), swap(y0, y1);
            // cout<<"?"<<((double)y1-y0)/(x1-x0)<<"
            // "<<y0-x0*((double)y1-y0)/(x1-x0)<<"\n";
            if(x0 != x1)
                line[p] = Line(((double)y1 - y0) / (x1 - x0),
                               y0 - x0 * ((double)y1 - y0) /
                                        (x1 - x0),
                               x0, x1, p);
            else
                line[p] = Line(0, max(y0, y1), x0, x1, p);
            ins(p);
            ++p;
        } else {
            int k;
            cin >> k;
            k = (k + ans - 1) % 39989 + 1;
            cout << (ans = qry(k)) << "\n";
        }
    }
    // cout<<qry(9)<<"\n";
}