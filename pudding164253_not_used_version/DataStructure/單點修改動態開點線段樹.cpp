#include <bits/stdc++.h>
using namespace std;
#define N 200005
#define M int m=l+r>>1
#define MAX 1000000000
int a[N];
typedef struct node{
    struct node *l,*r;
    int val;
};
void check(node *tree,int flag){
    if(flag&&!tree->r)tree->r=(node*)malloc(sizeof(struct node)),tree->r->val=0;
    else if(!flag&&!tree->l)tree->l=(node*)malloc(sizeof(struct node)),tree->l->val=0;
}
void upd(int pos,int val,int l,int r,node *tree){
    tree->val+=val;
    if(l==r)return;
    M;
    if(pos>m)check(tree,1),upd(pos,val,m+1,r,tree->r);
    else check(tree,0),upd(pos,val,l,m,tree->l);
}
int qry(int a,int b,int l,int r,node *tree){
    if(!tree)return 0;
    if(a<=l&&r<=b)return tree->val;
    M;
    if(a>m)return qry(a,b,m+1,r,tree->r);
    if(b<=m)return qry(a,b,l,m,tree->l);
    return qry(a,b,m+1,r,tree->r)+qry(a,b,l,m,tree->l);
}
int main(){
    int n,q,i=1,x;node *root=(node*)malloc(sizeof(struct node));root->val=0;
    for(scanf("%d %d",&n,&q);i<=n;++i)getchar(),scanf("%d",a+i),upd(a[i],1,1,MAX,root);
    // printf("%d %d %d %d %d\n",qry(2,2,1,n,1),qry(3,3,1,n,1),qry(5,5,1,n,1),qry(5,5,1,n,1),qry(1,N,1,n,1));
    for(;q--;){
        getchar();
        char c=getchar();
        scanf(" %d %d",&x,&i);
        if(c=='!')upd(a[x],-1,1,MAX,root),a[x]=i,upd(i,1,1,MAX,root);
        else printf("%d\n",qry(x,i,1,MAX,root));
    }
}