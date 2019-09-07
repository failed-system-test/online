#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
#include <local_debug.h>
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__);
#else
#define debug(...)
#endif

using i64 = long long;

const int MOD = 1000000007;

i64 pow64(i64 a, i64 b) {

    a %= MOD;
    i64 result = 1;
    while(b) {

        if(b & 1) result = result * a % MOD;
        a = a * a % MOD;
        b >>= 1;

    }
    return result;

}
i64 inv64(i64 x) { return pow64(x, MOD - 2); }

const int MAXN = 1001000;

int n;
std::vector<int> edges[MAXN];
bool visited[MAXN];
int cnt[MAXN], depth[MAXN];
int md;
int result[MAXN];

void dfs1(int u) {

    visited[u] = true;
    cnt[u] = 0;
    for(int v : edges[u]) {

        if(visited[v]) continue;
        ++cnt[u];
        depth[v] = depth[u] + 1;
        dfs1(v);

    }

}

void dfs2(int u) {

    visited[u] = true;
    if(!cnt[u]) {

        result[u] = depth[u] == md;
        return;

    }
    int sum = 0;
    for(int v : edges[u]) {

        if(visited[v]) continue;
        dfs2(v);
        sum = (sum + result[v]) % MOD;

    }
    sum = sum * inv64(cnt[u]) % MOD;
    sum = (1 - sum + MOD) % MOD;
    sum = pow64(sum, cnt[u]);
    sum = (1 - sum + MOD) % MOD;
    result[u] = sum;

}

int main() {
    
    std::scanf("%d", &n);
    for(int i = 0; i < n - 1; ++i) {
        
        int u, v;
        std::scanf("%d%d", &u, &v);
        --u, --v;
        edges[u].push_back(v);
        edges[v].push_back(u);

    }

    for(int i = 0; i < n; ++i)
        visited[i] = false;
    depth[0] = 0;
    dfs1(0);
    md = *std::max_element(depth, depth + n);
    for(int i = 0; i < n; ++i)
        visited[i] = false;
    dfs2(0);

    std::printf("%d\n", result[0]);

}
