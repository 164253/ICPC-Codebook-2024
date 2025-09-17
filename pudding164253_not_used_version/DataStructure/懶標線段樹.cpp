struct Seg{
    #define lid (id<<1)
    #define rid ((id<<1)|1)
    #define M (L+R>>1)
    #define N 200005
    LL seg[N<<2],tag[N<<2];
    void inline addtag(int id,LL v,int L,int R){seg[id]+=v*(R-L+1);tag[id]+=v;}
    void inline push(int id,int L,int R){addtag(lid,tag[id],L,M);addtag(rid,tag[id],M+1,R);tag[id]=0;}
    void inline pull(int id){seg[id]=seg[lid]+seg[rid];}
    void init(int L=1,int R=n,int id=1){
        if(L==R){seg[id]=0;tag[id]=0;return;}
        init(L,M,lid);init(M+1,R,rid);
        pull(id);
    }
    void upd(int l,int r,LL v,int L=1,int R=n,LL id=1){
        if(l<=L&&R<=r){addtag(id,v,L,R);return;}
        push(id,L,R);
        if(r<=M)upd(l,r,v,L,M,lid);
        else if(M+1<=l)upd(l,r,v,M+1,R,rid);
        else upd(l,M,v,L,M,lid),upd(M+1,r,v,M+1,R,rid);
        pull(id);
    }
    LL qry(int l,int r,int L=1,int R=n,int id=1){
        if(l<=L&&R<=r)return seg[id];
        push(id,L,R);
        if(r<=M)return qry(l,r,L,M,lid);
        if(M+1<=l)return qry(l,r,M+1,R,rid);
        return qry(l,M,L,M,lid)+qry(M+1,r,M+1,R,rid);
    }
}seg;
/*1based陣列 1based id 區間修改 預設維護區間和*/