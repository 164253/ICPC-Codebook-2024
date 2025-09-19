#include <bits/stdc++.h>
using namespace std;
int n;
double a[15], x, y;

double get(double x) {
    double ret = 0;
    double k = 1;
    for(int i = 0; i <= n; i++) {
        ret += k * a[i];
        k *= x;
    }
    return -ret;
}

template <class T> T bi_search(T l, T r, T end) {
    if(!check(r - end)) return r - end;
    for(; r - l > end;) {
        T mid = (l + r) / 2;
        if(check(mid))
            r = mid;
        else
            l = mid;
    }
    return l;
}
/*check gives 000000001111 find the last 0*/

template <class T> T tri_search(T l, T r, T end) {
    T midl, midr;
    for(;;) {
        midl = (l + r) / 2;
        midr = (midl + r) / 2;
        if(midr - midl < end) break;
        if(get(midr) > get(midl))
            r = midr;
        else
            l = midl;
    }
    for(; r - l > end;) {
        midl = (l + r) / 2;
        if(get(r) > get(l))
            r = midl;
        else
            l = midl;
    }
    return l;
}
/*get gives the value, find the minimum*/

int main() {
    cin >> n >> x >> y;
    for(int i = n; i >= 0; i--) {
        cin >> a[i];
    }
    cout << fixed << setprecision(7)
         << tri_search<double>(x, y, 1e-7);
}
