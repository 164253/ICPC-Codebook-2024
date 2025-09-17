class Z{
    public:
        vector<int> z;
        Z(string s,int n){
            z=vector<int>(n);
            for(int l=0,i=1;i<n;++i){
                if(l+z[l]>=i)z[i]=min(z[l]+l-i,z[i-l]);
                while(i+z[i]<n&&s[z[i]]==s[i+z[i]])++z[i];
                if(i+z[i]>l+z[l])l=i;
            }
        }
};