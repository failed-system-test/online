#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
#include <local_debug.h>
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__);
#else
#define debug(...)
#endif

typedef long long ll;

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int n, m;
        scanf("%d%d", &n, &m);
        vector<vector<ll>> g(n, vector<ll>(n, 1e18));
        for (int i = 0; i < n; i++) g[i][i] = 0;
        for (int i = 0, u, v, w; i < m; i++)
        {
            scanf("%d%d%d", &u, &v, &w);
            g[u][v] = w;
        }
        for (int i = 0, u, v; i < 6; i++)
        {
            for (int k = 0; k < n; k++)
                for (int i = 0; i < n; i++)
                    for (int j = 0; j < n; j++)
                        g[i][j] = min(g[i][k] + g[k][j], g[i][j]);
            scanf("%d%d", &u, &v);
            printf("%lld\n", -g[v][u]);
            g[u][v] = -g[v][u];
        }
    }
}
