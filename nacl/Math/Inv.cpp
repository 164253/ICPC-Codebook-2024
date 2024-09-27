int exgcd(int a, int b, int &x, int &y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  int d = exgcd(b, a % b, y, x);
  y -= x * (a / b);
  return d;
}

int inv(int a, int p) {
  int x, y;
  exgcd(a, p, x, y);
  return (x % p + p) % p;
}
