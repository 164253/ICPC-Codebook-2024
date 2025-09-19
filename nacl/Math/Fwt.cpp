#define LOGN 21
#define N (1 << LOGN)
void fwt(ll f[], int rev) {
    for(int k = 1; k < LOGN; ++k) {
        for(int i = 0, m = 1 << k - 1; i + m < N; i += 1 << k) {
            for(int j = 0; j < m; ++j) {
                ll u = f[i + j], v = f[i + j + m];
                f[i + j] = u + v;
                f[i + j + m] = u - v;
                if(rev) f[i + j] >>= 1, f[i + j + m] >>= 1;
            }
        }
    }
}