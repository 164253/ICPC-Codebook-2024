#include <bits/stdc++.h>
#define int long long
using namespace std;

int t;
int n, d;
bitset<1000005> exist;
bitset<1000005> vis;
vector<int> prime;
int phi[1000005];

void init() {
    phi[1] = 1;
    for(int i = 2; i <= 1000000; i++) {
        if(!vis[i]) {
            prime.push_back(i);
            phi[i] = i - 1;
        }
        for(int j : prime) {
            if(i * j > 1000000) break;
            vis[i * j] = 1;
            if(i % j == 0) {
                phi[i * j] = phi[i] * j;
                break;
            } else {
                phi[i * j] = phi[i] * phi[j];
            }
        }
    }
    exist[2] = exist[4] = 1;
    for(int i : prime) {
        if(i == 2) continue;
        for(int j = i; j <= 1000000; j *= i) {
            exist[j] = 1;
            if(j * 2 <= 1000000) {
                exist[j << 1] = 1;
            }
        }
    }
}

vector<int> factors(int x) {
    vector<int> v;
    for(int i = 1; i * i <= x; i++) {
        if(x % i == 0) {
            v.push_back(i);
            if(i * i != x) {
                v.push_back(x / i);
            }
        }
    }
    return v;
}

int f(int x, int y, int mod) {
    int ret = 1;
    while(y) {
        if(y & 1) {
            ret *= x;
            ret %= mod;
        }
        x *= x;
        x %= mod;
        y >>= 1;
    }
    return (ret % mod + mod) % mod;
}

vector<int> findroot(int x) {
    vector<int> ret;
    if(!exist[x]) return ret;
    int phix = phi[x];
    vector<int> fact = factors(phix);
    int fst;
    for(int i = 1;; i++) {
        if(__gcd(i, x) != 1) continue;
        bool ok = 1;
        for(int j : fact) {
            if(j != phix && f(i, j, x) == 1) {
                ok = 0;
                break;
            }
        }
        if(ok) {
            fst = i;
            break;
        }
    }
    int now = fst;
    // cout << fst <<"\n";
    for(int i = 1; i <= phix; i++) {
        if(__gcd(i, phix) == 1) {
            ret.push_back(now);
        }
        now *= fst;
        now %= x;
    }
    return ret;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    init();
    cin >> t;
    while(t--) {
        cin >> n >> d;
        vector<int> v = findroot(n);
        sort(v.begin(), v.end());
        cout << v.size() << "\n";
        for(int i = 0; i < v.size(); i++) {
            if(i % d == d - 1) {
                cout << v[i] << " ";
            }
        }
        cout << "\n";
    }
}