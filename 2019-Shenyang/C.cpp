#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
#include <local_debug.h>
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__);
#else
#define debug(...)
#endif

int main()
{
    int n, m;
    while (~scanf("%d%d", &n, &m))
    {
        vector<int> dp(10001, 0x3f3f3f3f);
        dp[0] = 0;
        for (int i = 0, p, c; i < n; i++)
        {
            scanf("%d%d", &p, &c);
            for (int j = c; j <= 10000; j++)
                dp[j] = min(dp[j], dp[j - c] + p);
        }
        int ans = 0x3f3f3f3f, ww = 0;
        for (int i = m; i < 10001; i++)
        {
            if (ans >= dp[i]) ans = dp[i], ww = i;
        }
        printf("%d %d\n", ans, ww);
    }
}
