struct Line{
    mutable int a,b,r;
    bool operator <(const Line& o) const {return a<o.a;}
    bool operator <(const int o) const {return r<o;}
};

struct DynamicHull: multiset<Line,less<>>{
    inline int Div(int a, int b){return a/b-((a^b)<0&&a%b);}
    inline bool intersect(iterator x, iterator y){
        if(y==end()){
            x->r=inf;
            return false;
        }
        if(x->a==y->a) x->r=(x->b)>(y->b)?inf:-inf;
        else x->r=Div((y->b)-(x->b),(x->a)-(y->a));
        return (x->r)>=(y->r);
    }
    void Insert(int a, int b){
        auto y=insert({a,b,0}),z=next(y),x=y;
        while(intersect(y,z)) z=erase(z);
        if(x!=begin()&&intersect(--x,y)) intersect(x,y=erase(y));
        while((y=x)!=begin()&&((--x)->r)>=(y->r)) intersect(x,erase(y));
    }
    int query(int x) const {
        auto l=*lower_bound(x);
        return (l.a)*x+(l.b);
    }
};