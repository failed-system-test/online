#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
#include <local_debug.h>
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__);
#else
#define debug(...)
#endif
#define lson (rt << 1)
#define rson (rt << 1 | 1)
#define Lson l, m, lson
#define Rson m + 1, r, rson
const int maxn = 1e5 + 5;
int a[maxn], ans[maxn];

struct Q
{
    int l, r, id;
    bool operator<(const Q& rhs) const
    {
        return r > rhs.r;
    }
} q[maxn];

int sum[maxn << 2];

void update(int l, int r, int rt, int L, int R)
{
    if (L <= l && R >= r)
    {
        sum[rt] += 1;
        return;
    }
    int m = l + r >> 1;
    if (L <= m) update(Lson, L, R);
    if (m + 1 <= R) update(Rson, L, R);
}
int query(int l, int r, int rt, int p)
{
    if (l == r)
        return sum[rt];
    int m = l + r >> 1;
    int ret = sum[rt];
    if (p <= m)
        ret += query(Lson, p);
    else
        ret += query(Rson, p);
    return ret;
}

bool alive[maxn];
int pos[maxn];
vector<int> G[maxn];
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", a + i);
        alive[i] = true;
        pos[a[i]] = i;
        assert(a[i] <= n);
    }
    for(int i=1;i<=n;i++){
        for(int j=2 * a[i]; j <= n; j += a[i]){
            G[j].push_back(i);
            G[a[i]].push_back(pos[j]);
        }
    }
    // for(int i=1;i<=n;i++){
    //     cerr << a[i] <<": ";
    //     for(auto &v:G[a[i]]){
    //         cerr << v << ' ';
    //     }
    //     cerr << endl;
    // }

    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &q[i].l, &q[i].r);
        q[i].id = i;
    }
    sort(q + 1, q + 1 + m, [](const Q& x, const Q& y) {
        return x.l < y.l;
    });
    int p = 1;
    priority_queue<Q> pq;
    for (int i = 1; i <= n; i++)
    {
        while (p <= m && q[p].l == i)
        {
            int id = q[p].id;
            ans[id] = -query(1, n, 1, q[p].r);
            pq.push(q[p++]);
        }
        for(auto &v:G[a[i]]){
            if(v > i)
                update(1,n,1,v, n);
        }
        while (!pq.empty() && pq.top().r == i)
        {
            auto it = pq.top();
            pq.pop();
            ans[it.id] += query(1, n, 1, it.r);
        }
        alive[a[i]] = false;
    }
    for (int i = 1; i <= m; i++) printf("%d\n", ans[i]);
}
