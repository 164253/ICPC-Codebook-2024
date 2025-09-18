#define V vector
string manacher(string t){
    int n=t.size()<<1|1;
    string s(n,'#');
    for(int i=0,m=t.size();i<m;++i)s[i<<1|1]=t[i];
    V<int> p(n);
    for(int i=0,m=0,r=0;i<n;++i){
        p[i]=r>i?min(r-i,p[m-(i-m)]):1;
        for(;i-p[i]>=0&&i+p[i]<n&&s[i-p[i]]==s[i+p[i]];)++p[i];
        if(i+p[i]>r)r=i+p[i],m=i;
    }
    int k=0;string ans="";
    for(int i=0;i<n;++i)if(p[i]>p[k])k=i;
    for(int r=k+p[k],l=k-p[k];++l<r;)if(s[l]!='#')ans+=s[l];
    return ans;
}
//manacher(s) 給出 s 中的最長回文，若有多個則給字典序最小的，p[i] = 以 i 為中心的最大回文半徑，所有字之間和頭尾都加上 '#'