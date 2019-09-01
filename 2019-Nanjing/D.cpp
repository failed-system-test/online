#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
#include <local_debug.h>
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__);
#else
#define debug(...)
#endif

using i64 = long long;

const int MAXN = 101000;

int t;
int n, m;
std::vector<int> g[MAXN];

double dp[MAXN][2];
bool vis[MAXN];

double dfs1(int u)
{
    if (vis[u]) return dp[u][0];
    vis[u] = true;
    double result = 0;
    int x = g[u].size();
    if (x == 0) return dp[u][0] = 0;
    for (auto& v : g[u]) result += dfs1(v);
    return dp[u][0] = (result / (x + 1) + 1) * (x + 1) / x;
}

double dfs2(int u)
{
    if (vis[u]) return dp[u][1];
    vis[u] = true;
    double result = 0;
    int x = g[u].size();
    if (x == 0) return dp[u][1] = 0;
    double result2 = 0;
    for (auto& v : g[u]) result += dfs2(v), result2 += dp[v][0];
    result2 += dp[u][0];
    result2 /= (x + 1);
    result = result / (x + 1) + result2 + 1;
    return dp[u][1] = result * (x + 1) / x;
}

int main()
{
    scanf("%d", &t);
    for (int test = 0; test < t; ++test)
    {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; ++i) g[i].clear();
        for (int i = 0, u, v; i < m; ++i)
        {
            scanf("%d%d", &u, &v);
            --u, --v;
            g[u].push_back(v);
        }
        std::fill(vis, vis + n, false);
        dfs1(0);
        std::fill(vis, vis + n, false);
        dfs2(0);
        for (int i = 0; i < n; i++) debug(dp[i][0], dp[i][1]);
        printf("%.2f\n", dp[0][1]);

    }
}
