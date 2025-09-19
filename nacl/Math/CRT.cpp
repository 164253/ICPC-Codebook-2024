#include <bits/stdc++.h>
#define int long long
using namespace std;

int n;
int a[15];
int b[15];
int mul = 1;

void exgcd(int a, int b, int &x, int &y) {
    if(b == 0) {
        x = 1;
        y = 0;
        return;
    }
    exgcd(b, a % b, y, x);
    y -= (a / b) * x;
}

int inv(int a, int p) {
    int x, y;
    exgcd(a, p, x, y);
    return x;
}

int ans = 0;

signed main() {
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i];
        mul *= a[i];
    }
    for(int i = 1; i <= n; i++) {
        ans += inv(mul / a[i], a[i]) * (mul / a[i]) % mul *
               b[i] % mul;
        ans %= mul;
    }
    ans = (ans + mul) % mul;
    cout << ans;
}