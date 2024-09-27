vector<int> prime;
bitset<1000005> vis;
int n;
int mu[1000005];

void init() {
  for (int i = 2; i <= n; i++) {
    if (!vis[i]) {
      prime.push_back(i);
      mu[i] = -1;
    }
    for (int p : prime) {
      if (i * p > n)
        break;
      vis[i * p] = 1;
      if (i % p == 0) {
        mu[i * p] = 0;
        break;
      } else {
        mu[i * p] = mu[i] * mu[p];
      }
    }
  }
}
