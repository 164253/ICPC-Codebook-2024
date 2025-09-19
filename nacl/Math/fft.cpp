#include <bits/stdc++.h>
using namespace std;
inline int read() {
    int ans = 0;
    char c = getchar();
    while(!isdigit(c)) c = getchar();
    while(isdigit(c)) {
        ans = ans * 10 + c - '0';
        c = getchar();
    }
    return ans;
}
typedef complex<double> comp;
const int MAXN = 1000005;
const comp I(0, 1);
const double PI = acos(-1);
comp A[MAXN * 3], B[MAXN * 3], tmp[MAXN * 3], ans[MAXN * 3];
void fft(comp F[], int N, int sgn = 1) {
    if(N == 1) return;
    memcpy(tmp, F, sizeof(comp) * N);
    for(int i = 0; i < N; i++)
        *(i % 2 ? F + i / 2 + N / 2 : F + i / 2) = tmp[i];
    fft(F, N / 2, sgn), fft(F + N / 2, N / 2, sgn);
    comp *G = F, *H = F + N / 2;
    comp cur = 1, step = exp(2 * PI / N * sgn * I);
    for(int k = 0; k < N / 2; k++) {
        tmp[k] = G[k] + cur * H[k];
        tmp[k + N / 2] = G[k] - cur * H[k];
        cur *= step;
    }
    memcpy(F, tmp, sizeof(comp) * N);
}
int main() {
    int n = read(), m = read(), N = 1 << __lg(n + m + 1) + 1;
    for(int i = 0; i <= n; ++i) A[i] = read();
    for(int i = 0; i <= m; ++i) B[i] = read();
    fft(A, N), fft(B, N);
    for(int i = 0; i < N; ++i) ans[i] = A[i] * B[i];
    fft(ans, N, -1);
    for(int i = 0; i <= n + m; ++i)
        printf("%d ", int(ans[i].real() / N + 0.1));
    return 0;
}
