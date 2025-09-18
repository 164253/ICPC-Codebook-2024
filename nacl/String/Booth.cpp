#define V vector
string booth(string s) {
  s += s;
  int n = s.size(), k = 0;
  V<int> f(n, -1);
  for (int i = 1; i < n; ++i) {
    int j = f[i - k - 1];
    for (; j >= 0 && s[j + k + 1] != s[i]; j = f[j])
      if (s[i] < s[j + k + 1])
        k = i - j - 1;
    if (s[i] != s[j + k + 1]) {
      if (s[i] < s[k])
        k = i;
      f[i - k] = -1;
    } else
      f[i - k] = j + 1;
  }
  return s.substr(k, s.size() >> 1);
}
//給出循環排列後最小字典序的解