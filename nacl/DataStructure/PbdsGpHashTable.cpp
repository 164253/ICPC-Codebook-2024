#include <bits/extc++.h>
using namespace __gnu_pbds;
#define ull unsigned ll
mt19937 mt(hash<string>()("164253_official_beautiful_fruit"));
struct myhash {
    static ull splitmix64(ull x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    ull operator()(ull x) const {
        static const ull FIXED_RANDOM =
            (ull)make_unique<char>().get() ^
            chrono::high_resolution_clock::now()
                .time_since_epoch()
                .count();
        // static const ull FIXED_RANDOM=mt();
        // static const ull
        // FIXED_RANDOM=chrono::steady_clock::now()
        // .time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
/*
gp_hash_table<ull,ull,myhash> gp;
gp[x]=y;
if(gp.find(x)!=gp.end())cout<<gp[x];
gp.count(); //CE
*/