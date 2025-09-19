#include <bits/stdc++.h>
#define int long long
using namespace std;

string s;
string t;
int n;
int d[2000005];
int ans = 0;

signed main() {
    cin >> t;
    n = t.size();
    for(int i = 0; i < 2 * n + 1; i++) {
        if(i & 1 ^ 1) {
            s += '0';
        } else {
            s += t[i / 2];
        }
    }
    n = s.size();
    d[0] = 1;
    for(int i = 0, l = 0, r = 0; i < n; i++) {
        if(i > r) {
            d[i] = 1;
            bool a = i + d[i] < n;
            bool b = i - d[i] >= 0;
      bool c = (s[i + d[i]] == s[i - d[i]];
      while (a && b && c) {
                d[i]++;
                a = i + d[i] < n;
                b = i - d[i] >= 0;
                c = ([i + d[i]] == s[i - d[i]]);
      }
      l = i - d[i] + 1;
      r = i + d[i] - 1;
        } else {
            int j = l + r - i;
            if(j - d[j] + 1 > l) {
                d[i] = d[j];
            } else {
                d[i] = r - i + 1;
                a = i + d[i] < n;
                b = i - d[i] >= 0;
                c = (s[i + d[i]] == s[i - d[i]]);
                while(a && b && c) {
                    d[i]++;
                    a = i + d[i] < n;
                    b = i - d[i] >= 0;
                    c = (s[i + d[i]] == s[i - d[i]]);
                }
                l = i - d[i] + 1;
                r = i + d[i] - 1;
            }
        }
        // cout << d[i] << " ";
        if(d[i] > d[ans]) {
            ans = i;
        }
    }
    for(int i = ans - d[ans] + 1; i < ans + d[ans]; i++) {
        if(s[i] ^ '0') {
            cout << s[i];
        }
    }
}
