class Z {
  public:
    vector<int> z;
    Z(string s) {
        z = vector<int>(s.size());
        for(int l = 0, i = 1; i < n; ++i) {
            if(l + z[l] >= i)
                z[i] = min(z[l] + l - i, z[i - l]);
            while(i + z[i] < n && s[z[i]] == s[i + z[i]])
                ++z[i];
            if(i + z[i] > l + z[l]) l = i;
        }
    }
};
// Z(s+"#"+t) 得到的陣列中，f[i]=s.size() 的格子代表 t
// 中匹配到 s 的開頭位置