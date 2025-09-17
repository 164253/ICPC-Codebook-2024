class Kmp{
    #define N 1000005
    public:
        int fail[N],p[N];
        Kmp(char *t,int n){
            fail[0]=-1;
            for(int i=1;i<n;++i){
                for(fail[i]=fail[i-1];t[i]!=t[fail[i]+1]&&fail[i]!=-1;)fail[i]=fail[fail[i]];
                if(t[i]==t[fail[i]+1])++fail[i];
            }
        }
        void match(char *s,int n,char *t,int m){
            p[0]=(s[0]==t[0])-1;
            for(int i=1;i<n;++i){
                for(p[i]=p[i-1];s[i]!=t[p[i]+1]&&p[i]!=-1;)p[i]=fail[p[i]];
                if(s[i]==t[p[i]+1])++p[i];
            }
        }
    #undef N
};
/*Kmp kmp(t)會建好t的失配函數fail[] match會把每格匹配完的失配函數p[]建好*/