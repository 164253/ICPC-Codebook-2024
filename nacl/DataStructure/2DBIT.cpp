/// cses Forest Queries II
#include <bits/stdc++.h>
using namespace std;
#define LL long long
#define pii pair<int, int>
#define N 1005
#define F first
#define S second
int bit[N][N];
#define lb(x) (x & -x)
void upd(int i, int j, int v) {
    for(; j < N; j += lb(j))
        for(int k = i; k < N; k += lb(k)) bit[k][j] += v;
}
int qry2(int i, int j) {
    int ans = 0;
    for(; j; j -= lb(j))
        for(int k = i; k; k -= lb(k)) ans += bit[k][j];
    return ans;
}
int qry(int y1, int x1, int y2, int x2) {
    return qry2(y2, x2) - qry2(y2, x1 - 1) - qry2(y1 - 1, x2) +
           qry2(y1 - 1, x1 - 1);
}
int main() {
    int n, q, i = 1, j, y, x;
    for(scanf("%d %d", &n, &q); getchar(), i <= n; ++i)
        for(j = 1; j <= n; ++j)
            if(getchar() == '*') upd(i, j, 1);
    for(; q--;) {
        scanf("%d", &i);
        if(i == 1)
            scanf("%d%d", &i, &j),
                upd(i, j, 1 - 2 * qry(i, j, i, j));
        else
            scanf("%d%d%d%d", &i, &j, &y, &x),
                printf("%d\n", qry(i, j, y, x));
    }
}