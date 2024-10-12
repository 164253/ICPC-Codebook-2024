#include <bits/stdc++.h>
#define int long long
using namespace std;

int n;
double a[105][105];

// n <= m
void gaussian(double a[105][105], int n, int m) {
  int curi = 0;
  for (int j = 0; j < m; j++) {
    int i;
    for (i = curi; i < n; i++) {
      if (a[i][j]) {
        break;
      }
    }
    if (a[i][j] == 0)
      continue;
    for (int k = 0; k < m; k++) {
      swap(a[i][k], a[curi][k]);
    }
    for (int k = m - 1; k >= j; k--) {
      a[curi][k] /= a[curi][j];
    }
    for (int i = 0; i < n; ++i) {
      if (i != curi) {
        for (int k = m - 1; k >= j; k--) {
          a[i][k] -= a[curi][k] * a[i][j];
        }
      }
    }
    curi++;
  }
}