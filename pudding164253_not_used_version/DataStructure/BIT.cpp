template<class T>
class BIT{
    #define lb(x) ((x)&-(x))
    #define N (int)2e5+5
    public:
        T bit[N]={0};
        void update(T x,T v){for(;x<N;x+=lb(x))bit[x]+=v;}
        T qry(T x){T ans=0;for(;x;x-=lb(x))ans+=bit[x];return ans;}
    #undef lb
    #undef N
};
/*1based bit update預設是加值*/