//treap模板 洛谷P3369 【模板】普通平衡树
#include <bits/stdc++.h>
using namespace std;
#define pnn pair<node*,node*>
#define F first
#define S second
#define int long long
mt19937 mt(hash<string>()("official_beautiful_fruit"));
struct node{
    node *l,*r;
    int val,sz;
    int mx,mn,sum,num;
    int rev_tag,add_tag;
    node(int _val=0,int _num=1):val(_val),l(0),r(0),sz(1),sum(_num),num(_num),mx(_val),mn(_val),rev_tag(0),add_tag(0){}
    node(node*tr):val(tr->val),l(tr->l),r(tr->r),sz(tr->sz){}
    void pull(){
        sz=1;mx=mn=sum=num;
        if(l)sz+=l->sz,mx=max(mx,l->mx),mn=min(mn,l->mn),sum+=l->sum;
        if(r)sz+=r->sz,mx=max(mx,r->mx),mn=min(mn,r->mn),sum+=r->sum;
    }
    void push(){
        if(rev_tag)swap(l,r);
        if(l)l->add_tag+=add_tag,l->rev_tag^=rev_tag;
        if(r)r->add_tag+=add_tag,r->rev_tag^=rev_tag;
        mx+=add_tag;mn+=add_tag;sum+=add_tag;add_tag=0;rev_tag=0;
    }
};
void debug(node*tr){
    if(!tr)return;
    debug(tr->l);cout<<tr->val<<" ";debug(tr->r);
}
void debug2(node*tr){
    if(!tr)return;
    cout<<tr->val<<" ";debug2(tr->l);debug2(tr->r);
}
int sz(node*tr){return tr?tr->sz:0;}
node*merge(node*a,node*b){
    if(!a||!b)return a?:b;
    if(mt()%(sz(a)+sz(b))<sz(a)){a->r=merge(a->r,b);a->pull();return a;}
    b->l=merge(a,b->l);b->pull();return b;
}
pnn split(node*tr,int v){//(-inf,v],(v,inf)
    if(!tr)return {0,0};
    tr->push();
    if(tr->val<=v){
        auto[l,r]=split(tr->r,v);
        tr->r=l;tr->pull();
        return {tr,r};
    }
    auto[l,r]=split(tr->l,v);
    tr->l=r;tr->pull();
    return {l,tr};
}
pnn splitsz(node*tr,int k){//[rk.1,rk.k],(rk.k,rk.n]
    if(!tr||sz(tr)<=k)return {tr,0};
    tr->push();
    if(k<=sz(tr->l)){
        auto[l,r]=splitsz(tr->l,k);
        tr->l=r;tr->pull();
        return {l,tr};
    }
    else if(k<=sz(tr->l)+1){
        auto r=tr->r;
        tr->r=0;tr->pull();
        return {tr,r};
    }
    else{
        auto [l,r]=splitsz(tr->r,k-(sz(tr->l)+1));
        tr->r=l;tr->pull();
        return {tr,r};
    }
}
node*insert(node*tr,int val=0,int num=1){
    auto[l,r]=split(tr,val);
    return merge(merge(l,new node(val,num)),r);
}
node*insertkth(node*tr,int k){
    auto[l,r]=splitsz(tr,k-1);
    return merge(merge(l,new node()),r);//new node拿來區間操作初始化
}
node*eraseall(node*tr,int v){
    auto[l,r]=split(tr,v-1);
    return merge(l,split(r,v).S);
}
node*eraseone(node*tr,int v){
    auto[l,r]=split(tr,v-1);
    return merge(l,splitsz(r,1).S);
}
node*erasekth(node*tr,int k){
    auto[l,r]=splitsz(tr,k-1);
    return merge(l,splitsz(r,k).S);
}
int rnk(node*tr,int v){
    if(!tr)return 0;
    if(tr->val<=v)return sz(tr->l)+1+rnk(tr->r,v);
    return rnk(tr->l,v);
}
int kth(node*&tr,int k){
    auto[l,x]=splitsz(tr,k-1);
    auto[m,r]=splitsz(x,1);
    if(!m)return 0;
    int ans=m->val;
    tr=merge(merge(l,m),r);
    return ans;
}
int count(node*&tr,int L,int R){//count[L,R]
    auto[l,x]=split(tr,L-1);
    auto[m,r]=split(x,R);
    int ans=m->sum;//看要改啥
    tr=merge(merge(l,m),r);
    return ans;
}
int countkth(node*&tr,int L,int R){//count[rk.L,rk.R]
    auto[l,x]=splitsz(tr,L-1);
    auto[m,r]=splitsz(x,R-L);
    int ans=m->sum;//看要改啥
    tr=merge(merge(l,m),r);
    return ans;
}
int prev(node*&tr,int v){
    auto[x,r]=split(tr,v-1);
    auto[l,m]=splitsz(x,sz(x)-1);
    int ans=m->val;
    tr=merge(merge(l,m),r);
    return ans;
}
int next(node*&tr,int v){
    auto[l,x]=split(tr,v);
    auto[m,r]=splitsz(x,1);
    int ans=m->val;
    tr=merge(merge(l,m),r);
    return ans;
}
int qry(node*&tr,int L,int R){//qry[L,R]
    auto[l,x]=splitsz(tr,L-1);
    auto[m,r]=splitsz(x,R);
    int ans=m->sum;//看要改啥
    tr=merge(merge(l,m),r);
    return ans;
}
void modify(node*&tr,int L,int R,int v){//modify[L,R]
    auto[l,x]=splitsz(tr,L-1);
    auto[m,r]=splitsz(x,R);
    m->val+=v;m->add_tag+=v;//看要改啥
    tr=merge(merge(l,m),r);
}
signed main(){
    vector<node*> tr(2);
    int n,m;
    scanf("%lld%lld",&n,&m);
    for(int i=1,x;i<=n;++i)scanf("%lld",&x),(x)&&(tr[1]=insert(tr[1],i,x));
    for(;m--;){
        int op=-1,p=-1,x=-1,y=-1;
        scanf("%lld",&op);
        if(!op){
            scanf("%lld%lld%lld",&p,&x,&y);
            auto[l,tmp]=split(tr[p],x-1);
            auto[m,r]=split(tmp,y);
            tr[p]=merge(l,r);
            tr.push_back(m);
        }
        else if(op==1){
            scanf("%lld%lld",&p,&x);
            // cout<<kth(tr[x],1)<<"\n";//break;
            auto[l,r]=split(tr[p],kth(tr[x],1));
            tr[p]=merge(merge(l,tr[x]),r);
        }
        else switch(op){
            case 2:scanf("%lld%lld%lld",&p,&x,&y);tr[p]=insert(tr[p],y,x);break;
            case 3:scanf("%lld%lld%lld",&p,&x,&y);printf("%lld\n",count(tr[p],x,y));break;
            case 4:scanf("%lld%lld",&p,&x);printf("%lld\n",kth(tr[p],x));break;
        }
    }
}