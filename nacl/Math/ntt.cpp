#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 1000005;
const int MOD = 998244353, G = 3;
int rev[MAXN * 3];

int qpow(int x, int y) {
    int ret = 1;
    while(y) {
        if(y & 1) {
            ret *= x;
            ret %= MOD;
        }
        x *= x;
        x %= MOD;
        y >>= 1;
    }
    return ret;
}

void ntt(int F[], int N, int sgn) {
    int bit = __lg(N);
    for(int i = 0; i < N; ++i) {
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
        if(i < rev[i]) swap(F[i], F[rev[i]]);
    }
    for(int l = 1, t = 1; l < N; l <<= 1, t++) {
        int step = qpow(G, ((MOD - 1) >> t) * sgn + MOD - 1);
        for(int i = 0; i < N; i += l << 1)
            for(int k = i, cur = 1; k < i + l; ++k) {
                int g = F[k], h = (ll)F[k + l] * cur % MOD;
                F[k] = (g + h) % MOD;
                F[k + l] = ((g - h) % MOD + MOD) % MOD;
                cur = (ll)cur * step % MOD;
            }
    }
    if(sgn == -1) {
        int invN = qpow(N, MOD - 2);
        for(int i = 0; i < N; ++i) F[i] = (ll)F[i] * invN % MOD;
    }
}
