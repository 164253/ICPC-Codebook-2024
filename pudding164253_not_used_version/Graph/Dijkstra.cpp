//cses Shortest Routes I
#include <bits/stdc++.h>
using namespace std;
#define N 100005
#define LL long long
#define pii pair<int,int>
#define pil pair<LL,LL>
#define F first
#define S second
#define pb push_back
#define DE if(1)
#define INF (LL)1e16
vector<pil> adj[N];LL d[N];bitset<N> vis;
int main(){
    int n,m,u,v;LL c;priority_queue<pil,vector<pil>,greater<pil>> q;
    for(cin>>n>>m;m--;)cin>>u>>v>>c,adj[u].pb({v,c});
    q.push({0,1});d[1]=0;for(u=2;u<=n;++u)d[u]=INF;
    for(;!q.empty();q.pop()){
        if(vis[q.top().S])continue;
        vis[q.top().S]=1;
        for(auto&e:adj[q.top().S]){
            if(!vis[e.F]&&q.top().F+e.S<d[e.F]){
                d[e.F]=q.top().F+e.S;
                q.push({d[e.F],e.F});
            }
        }
    }
    for(u=1;u<=n;++u)printf("%lld ",d[u]);
}