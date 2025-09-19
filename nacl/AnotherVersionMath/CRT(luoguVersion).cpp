long long CRT(long long *W, long long *B,
              long long k /*方程组数*/) {
    long long x, y, a = 0, m, n = 1;
    for(long long i = 0; i < k; i++) n *= W[i];
    for(long long i = 0; i < k; i++) {
        m = n / W[i];
        ext_gcd(W[i], m, x, y);
        a = (a + y * m * B[i]) % n;
    }
    return a > 0 ? a : a + n;
}