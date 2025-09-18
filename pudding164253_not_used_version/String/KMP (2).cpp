#define V vector
V<int> kmp(string s){
    int n=s.size();
    V<int> f(n);
    for(int i=1;i<n;++i){
        int j=f[i-1];
        for(;j>0&&s[j]!=s[i];)j=f[j-1];
        f[i]=j+(s[j]==s[i]);
    }
    return f;
}
//kmp(s+"#"+t) 得到的陣列中，f[i]=s.size() 的格子代表 t 中匹配到 s 的結尾位置