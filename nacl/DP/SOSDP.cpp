for(int i = 0; i < 20; ++i)
    for(int j = i; j < N; ++j)
        if(j >> i & 1) dp[j] += dp[j ^ (1 << i)]; // subset
for(int i = 0; i < 20; ++i)
    for(int j = 0; j < N; ++j)
        if(!(j >> i & 1))
            dp2[j] += dp2[j | (1 << i)]; // superset