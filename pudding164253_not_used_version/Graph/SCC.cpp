#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define pii pair<int,int>
#define N 100005
vector<int> adj[N];stack<int> st;
int dfn[N],low[N],tag,scc[N],scchead[N],sc;bitset<N> in;
void dfs(int now,int par=-1){
    st.push(now);in[now]=1;
    low[now]=dfn[now]=++tag;
    for(int e:adj[now]){
        if(e==par)continue;
        if(!dfn[e])dfs(e,now),low[now]=min(low[now],low[e]);
        else if(in[e])low[now]=min(low[now],dfn[e]);
    }
    if(dfn[now]==low[now]){
        ++sc;
        for(;st.top()!=now;st.pop())scc[st.top()]=sc,in[st.top()]=0;
        st.pop();scc[now]=sc;in[now]=0;scchead[sc]=now;
    }
}
int main(){
    int n,m,u,v;cin>>n>>m;vector<pii> g(m);
    for(auto&[u,v]:g)cin>>u>>v,adj[u].pb(v),adj[v].pb(u);
    for(u=1;u<=n;++u)if(!dfn[u])dfs(u);
    int ans=0;
    for(auto&[u,v]:g)if(scc[u]!=scc[v])++ans;//=eBCC
    cout<<ans<<"\n";
    for(auto&[u,v]:g)if(scc[u]!=scc[v])cout<<u<<" "<<v<<"\n";
}