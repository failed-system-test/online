#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
#include <local_debug.h>
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__);
#else
#define debug(...)
#endif

const int N = 1 << 10;
int f[N];

struct Edge
{
    int from, to, cost;
    Edge(int u, int v, int w) : from(u), to(v), cost(w) {}
};

vector<Edge> edges;
vector<int> G[N];
void addedge(int u, int v, int w)
{
    edges.emplace_back(u, v, w);
    G[u].push_back(edges.size() - 1);
}

long long d[N][N];
bool vis[N];

void init(int n)
{
    for (int i = 1; i <= n; i++) G[i].clear();
    edges.clear();
}

struct HeapNode
{
    long long d;
    int u;
    HeapNode(long long d, int u) : d(d), u(u) {}
    bool operator<(const HeapNode& rhs) const
    {
        return d > rhs.d;
    }
};

void dijkstra(int s, int n, long long d[])
{
    for (int i = 1; i <= n; i++) d[i] = 1e18, vis[i] = 0;
    priority_queue<HeapNode> q;
    d[s] = 0;
    q.emplace(d[s], s);
    while (!q.empty())
    {
        auto x = q.top();
        int u = x.u;
        q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (auto& id : G[u])
        {
            auto& e = edges[id];
            if (d[e.to] > d[e.from] + e.cost)
            {
                d[e.to] = d[e.from] + e.cost;
                q.emplace(d[e.to], e.to);
            }
        }
    }
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int v, e, s, k, c;
        scanf("%d%d%d%d%d", &v, &e, &s, &k, &c);
        for (int i = 0; i < k; i++) scanf("%d", &f[i]);
        init(v);
        for (int i = 0, u, v, w; i < e; i++)
        {
            scanf("%d%d%d", &u, &v, &w);
            addedge(u, v, w);
            addedge(v, u, w);
        }
        for (int i = 1; i <= v; i++) dijkstra(i, v, d[i]);
        long long hero = *max_element(d[s] + 1, d[s] + v + 1);
        long long fire = 0;
        for (int i = 1; i <= v; i++)
        {
            long long cur = 1e18;
            for (int j = 0; j < k; j++)
                cur = min(cur, d[i][f[j]]);
            fire = max(fire, cur);
        }
        debug(fire, hero);
        if (hero <= fire * c)
            printf("%lld\n", hero);
        else
            printf("%lld\n", fire);
    }
}
