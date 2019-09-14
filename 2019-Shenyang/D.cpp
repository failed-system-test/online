#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
#include <local_debug.h>
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__);
#else
#define debug(...)
#endif

const int N = 10005;
const int mod = 1e9 + 7;
vector<pair<int, int>> g[N];

int ans[3];
int dp[N][3];
void dfs(int u, int fa)
{
    dp[u][0] = 1;
    dp[u][1] = 0;
    dp[u][2] = 0;
    for (auto& e : g[u])
    {
        int v = e.first;
        int w = e.second;
        if (v == fa) continue;
        dfs(v, u);
        for (int i = 0; i < 3; i++)
            (dp[u][(i + w) % 3] += dp[v][i]) %= mod;
    }
}

void DFS(int u, int fa, vector<int> last, int val)
{
    // printf("u = %d: ", u);
    // for(int i=0;i<3;i++)
    //     printf("%d ",last[i]);
    //     puts("");

    for (auto& e : g[u])
    {
        int v = e.first;
        int w = e.second;
        if (v == fa) continue;
        vector<int> tmp(3), a(3);
        for (int i = 0; i < 3; i++)
            tmp[(i + w) % 3] = dp[v][i];
        for (int i = 0; i < 3; i++)
            a[(i + w) % 3] = ((last[i] + dp[u][i]) % mod - tmp[i] + mod) % mod;
        DFS(v, u, a, w);
    }
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            ans[(i + j) % 3] = (ans[(i + j) % 3] + 1LL * last[i] * dp[u][j] % mod * val % mod) % mod;
}
int main()
{
    int n;
    while (~scanf("%d", &n))
    {
        for (int i = 0; i < n; i++) g[i].clear();
        for (int i = 1, a, b, c; i < n; i++)
        {
            scanf("%d%d%d", &a, &b, &c);
            g[a].emplace_back(b, c);
            g[b].emplace_back(a, c);
        }
        dfs(0, -1);
        for (int i = 0; i < 3; i++) ans[i] = 0;
        vector<int> tmp(3);
        DFS(0, -1, tmp, 0);
        for (int i = 0; i < 3; i++)
            printf("%d%c", ans[i] * 2 % mod, i == 2 ? '\n' : ' ');
    }
}
