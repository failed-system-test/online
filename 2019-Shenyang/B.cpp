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

int t, n, m, k;
std::vector<int> edges[MAXN];
bool monster[MAXN];

int dsu[MAXN], sz[MAXN];
void init() {

    for(int i = 0; i < n; ++i)
        dsu[i] = i, sz[i] = 1;

}
int find(int u) { return dsu[u] == u ? u : dsu[u] = find(dsu[u]); }
void join(int u, int v) { u = find(u), v = find(v); if(u == v) return; dsu[v] = u, sz[u] += sz[v]; }

int main() {
    
    std::scanf("%d", &t);
    for(int test = 0; test < t; ++test) {

        std::scanf("%d%d%d", &n, &m, &k);
        for(int i = 0; i < n; ++i)
            edges[i].clear(), monster[i] = false;
        for(int i = 0; i < m; ++i) {

            int u, v;
            std::scanf("%d%d", &u, &v);
            --u, --v;
            edges[u].push_back(v);
            edges[v].push_back(u);

        }
        for(int i = 0; i < k; ++i) {

            int u;
            std::scanf("%d", &u);
            --u;
            monster[u] = true;

        }
        init();
        for(int u = 0; u < n; ++u) {
            
            if(monster[u]) continue;
            for(int v : edges[u]) {

                if(monster[v]) continue;
                join(u, v);

            }
            
        }
        int d0 = find(0), s0 = sz[d0];
        double result = 0;
        for(int u = 0; u < n; ++u) {
            
            if(!monster[u]) continue;
            bool ok = false;
            for(int v : edges[u])
                if(find(v) == d0) { ok = true; break; }
            if(!ok) continue;
            i64 sum = 0;
            for(int v : edges[u]) {
                
                if(monster[v]) continue;
                int d = find(v);
                if(d != d0) sum += sz[d];

            }
            result = std::max(result, double(sum) / edges[u].size());

        }
        std::printf("%.6f\n", result + sz[d0]);
        
    }

}
