#include <bits/stdc++.h>
#define int long long
using namespace std;

string s, t;
int ans = 0;

int z[2000005];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> s >> t;
    s = t + '0' + s;
    int n, m;
    n = s.size();
    m = t.size();
    for(int i = 0, l = 0, r = 0; i < n; i++) {
        if(z[i - l] < r - i + 1) {
            z[i] = z[i - l];
        } else {
            z[i] = max(r - i + 1, (int)0);
            while(i + z[i] < n && s[i + z[i]] == s[z[i]]) {
                z[i]++;
            }
            l = i;
            r = i + z[i] - 1;
            if(z[i] == m) {
                ans++;
            }
        }
    }
    cout << ans;
}