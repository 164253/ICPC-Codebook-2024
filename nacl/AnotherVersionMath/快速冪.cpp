template <class T, class POW>
void fastpow(T x, POW n, POW p, T &ans) {
    for(; n; n >>= 1) {
        if(n & 1) {
            ans *= x;
            ans %= p;
        }
        x *= x;
        x %= p;
    }
}
/*輸入x,n,p,ans 會將ans修改為x^n%p
對整數/矩陣/不要求精度的浮點 皆有效
模板第一個型別是x,ans 第二個是n,p(應該放LL或__int128)*/