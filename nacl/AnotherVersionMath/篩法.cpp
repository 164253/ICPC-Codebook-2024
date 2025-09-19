// 待加入分塊篩
template <class T> class Prime {
#define N (int)1e8 + 9
  public:
    vector<T> list, factor;
    Prime(T n) {
        eular(n);
        // eratosthenes(n);
        // sqrt_sieve
        // factorize(n);
    }
    void show() {
        for(T e : list) printf("%lld ", e);
        putchar('\n');
    }

  private:
    bitset<N> notprime; // 1e8<2^27=128MB
    void eular(T n) {
        for(T i = 2; i <= n; ++i) {
            if(!notprime[i]) list.emplace_back(i);
            const T k = n / i;
            for(T j : list) {
                if(j > k) break;
                notprime[i * j] = 1;
                if(!(i % j)) break;
            }
        }
    }
    void eratosthenes(T n) {
        for(T i = 2; i <= n; ++i) {
            if(!notprime[i]) list.emplace_back(i);
            const T k = n / i;
            for(T j : list) {
                if(j > k) break;
                notprime[i * j] = 1;
                if(!(i % j)) break;
            }
        }
    }
    void sqrt_sieve(T n) {
        for(T i = 2; i <= n; ++i) {
            bool isprime = 1;
            for(T j : list) {
                if(j > i / j) break;
                if(!(i % j)) {
                    isprime = 0;
                    break;
                }
            }
            if(isprime) list.emplace_back(i);
        }
    }
    void factorize(T n) {
        factor = vector<T>(n);
        if(list.empty()) eular(n);
        for(T j : list) factor[j] = j;
        for(T i = 2; i <= n; ++i) {
            const T k = n / i;
            for(T j : list) {
                if(j > k) break;
                factor[i * j] = j;
                if(!(i % j)) break;
            }
        }
    }
#undef N
};
/*Prime prime(n)建立打好1~n質數表的物件
prime.list(一個vector)是質數表
可修改define N決定歐篩/埃篩上限
可在建構子選擇篩法 有歐篩/埃篩/根號暴力搜
prime.factorize(n)用歐篩方式得到1~n所有數的最小質因數
可在factor(一個vector)上一路回溯 logn得到一個數的質因數分解
做n個數質因數分解共花nlogn
show()會以空格隔開 顯示所有list內的元素 有尾空格尾換行
printf裡面用%lld 視情況換為%d或cout*/