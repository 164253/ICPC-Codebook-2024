template <class T> T extgcd(T a, T b, T &x, T &y) {
    if(!b) {
        x = 1;
        y = 0;
        return a;
    }
    T ans = extgcd(b, a % b, y, x);
    y -= a / b * x;
    return ans;
}
/*extgcd(a,b,x,y)=ax+by,x跟y是會被修改的參數*/
template <class T> T modeq(T a, T b, T p) {
    T x, y, d = extgcd(a, p, x, y);
    if(b % d) return 0;
    return ((b / d * x) % p + p) % p;
}
/*x=modeq(a,b,n),ax=b(mod n),0<=x<n
modeq(a,1,n)相當於求a在mod n下的逆元*/
template <class T> T gcd(T a, T b) {
    if(!a) return b;
    if(!b) return a;
    if(a & b & 1) return gcd(abs(a - b), min(a, b));
    if(a & 1) return gcd(a, b >> 1);
    if(b & 1) return gcd(a >> 1, b);
    return gcd(a >> 1, b >> 1) << 1;
}
/*gcd(a,b) 默認gcd(a,0)=a*/
ll crt(V<ll> &p, V<ll> &a) {
    ll n = 1, ans = 0, k = a.size();
    for(ll &e : p) n *= e;
    for(int i = 0; i < k; ++i)
        ans = (ans + a[i] * n / p[i] % n *
                         modeq(n / p[i], 1LL, p[i]) % n) %
              n;
    return (ans % n + n) % n;
}
/*$(a+b)^p \equiv a+b \equiv a^p+b^p \pmod p$ (小費馬)
$(p-1)! \equiv -1 \pmod p$ (威爾遜定理)
$v(n):=n中p的冪次, (n)_{p}:=\frac{n}{p^{v(n)}},$
$s(n):=p進制下n的所有位數和$
$v(n!)=\sum_{i=1}^\infty \lfloor$
$\frac{n}{p^i} \rfloor=\frac{n-s(n)}{p-1}$ (勒壤得定理)
$v(\binom{n}{m})=\frac{s(n)+s(m-n)-s(m)}{p-1}$ (庫默爾定理)
$v(\binom{n}{{m1,m2,...mk}}=$
$\frac{\sum_{i=1}^{k}s(mi)-s(n)}{p-1}$(庫默爾定理推廣)
\[
    (n!)_p\equiv-1^{\lfloor\frac{n}{p}\rfloor}
\]
\[
    ((\lfloor\frac{n}{p}\rfloor)!)_p((n\%p)!)\pmod p
\]
打階乘表+迭代這條式子可以 $O(p+log_p(n))$ (mod下階乘)
$\binom{n}{m}\equiv\frac{((n+m)!)_p}{(n!)_p(m!)_p}$
$p^{v(n+m)-v(n)-v(m)}\pmod{p^q}$
把 $p$ 從 $C(n,m)$ 裡面隔離掉了 就能用上面的
$(n!)_p$+模逆元(mod下階乘推廣至二項式)
$((p^q)!)_p\equiv\pm 1\pmod {p^q}$ (威爾遜定理推廣)
\[
    \binom{n}{m}\equiv\binom{\lfloor\frac{n}{p}\rfloor}
\]
${\lfloor\frac{m}{p}\rfloor}\binom{n\%p}{m\%p}\pmod p$
(lucas定理) 打階乘表跟模逆元表+迭代這條式子可以 $O(p+log_p(n))$
若 $p$ 進制下任何一位 $i$ 滿足 $n_i<m_i$ 則
$\binom{n_i}{m_i}\%p=0$
則因 $\binom{n}{m}=\prod_{i=0}^{\max(\log_p(a),\log_p(b))}$
$\binom{n_i}{m_i}\%p$導致$\binom{n}{m}\%p=0$
設 $p=2$ 則有 $\binom{n}{m}$ 是奇數的充要條件為二進制下每一位
$n<m$ (lucas定理額外性質) lucas定理可由此生成函數做法得到
不依賴小費馬 對多項式也成立 根據上述
$\binom{n}{m}\%k$ 可將 $k$ 做唯一質數分解
個別做完再做crt得到結果(exlucas定理)
\[
    卡特蘭數 C(0)=C(1)=1,n>1時C(n)=\sum_{k=0}^{n-1}C(k)C(n-1-k)=
\]
$\frac{\binom{2n}{n}}{n+1}$
同時 $n$ 對括號的合法放置數即是 $C(n)$ 若有任意k種括號可選 則
$C(n)k^n$
模逆元表p=i*(p/i)+p%i,-p%i=i*(p/i),inv(i)=-(p/i)*inv(p%i)*/
LL fracp[N], invp[N];
void fracp_init(LL p) {
    fracp[0] = 1;
    for(int i = 1; i < p; ++i) fracp[i] = fracp[i - 1] * i % p;
}
void invp_init(LL p) {
    invp[0] = invp[1] = 1;
    for(int i = 2; i < p; ++i)
        invp[i] = p - (p / i * invp[p % i]) % p;
}
/*階乘表跟模逆元表 之後可以考慮改一下長相*/
template <class T> T lucas(T n, T m, T p) {
    if(!m) return 1;
    if(m > n || m % p > n % p) return 0;
    return lucas(n / p, m / p, p) * fracp[n % p] % p *
           invp[fracp[n % p - m % p]] % p * invp[fracp[m % p]] %
           p;
}
/*lucas(n,m,p)=C(n,m)%p 要求要帶階乘表跟模逆元表
 * O(p+log_p(n))*/
/*米勒拉賓質數 2,325,9375,28178,450775,9780504,1795265022*/
/*crt 質數
(2^16)+1 65537 3
7*17*(2^23)+1 998244353 3
1255*(2^20)+1 1315962881 3
51*(2^25)+1 1711276033 29
*/