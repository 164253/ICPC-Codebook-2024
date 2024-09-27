int fact[100005];
int p;

void init() {
  fact[0] = 1;
  for (int i = 1; i <= p; i++) {
    fact[i] = fact[i - 1] * i % p;
  }
}

int inv(int x, int p) {
  if (x == 1)
    return 1;
  return (p - p / x) * inv(p % x, p) % p;
}

int c(int x, int y, int p) {
  if (x < y)
    return 0;
  int k = fact[x] * inv(fact[y], p) % p;
  return k * inv(fact[x - y], p) % p;
}

int lucas(int x, int y, int p) {
  if (x == 0)
    return 1;
  return lucas(x / p, y / p, p) % p * c(x % p, y % p, p) % p;
}
