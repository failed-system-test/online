#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", __func__, ##__VA_ARGS__)
#else
#define debug(...)
#endif

const int maxn = 1 << 17;
namespace Suffix_Array
{
char s[maxn];
int sa[maxn], t[maxn], t2[maxn], c[maxn], rank[maxn], height[maxn];
void build_sa(int m, int n)
{
    n++;
    int *x = t, *y = t2;
    for (int i = 0; i < m; i++) c[i] = 0;
    for (int i = 0; i < n; i++) c[x[i] = s[i]]++;
    for (int i = 1; i < m; i++) c[i] += c[i - 1];
    for (int i = n - 1; ~i; i--) sa[--c[x[i]]] = i;
    for (int k = 1; k <= n; k <<= 1)
    {
        int p = 0;
        for (int i = n - k; i < n; i++) y[p++] = i;
        for (int i = 0; i < n; i++)
            if (sa[i] >= k) y[p++] = sa[i] - k;
        for (int i = 0; i < m; i++) c[i] = 0;
        for (int i = 0; i < n; i++) c[x[y[i]]]++;
        for (int i = 1; i < m; i++) c[i] += c[i - 1];
        for (int i = n - 1; ~i; i--) sa[--c[x[y[i]]]] = y[i];
        std::swap(x, y);
        p = 1;
        x[sa[0]] = 0;
        for (int i = 1; i < n; i++)
            x[sa[i]] = y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + k] == y[sa[i] + k] ? p - 1 : p++;
        if (p >= n) break;
        m = p;
    }
    n--;
    int k = 0;
    for (int i = 0; i <= n; i++) rank[sa[i]] = i;
    for (int i = 0; i < n; i++)
    {
        if (k) k--;
        int j = sa[rank[i] - 1];
        while (s[i + k] == s[j + k]) k++;
        height[rank[i]] = k;
    }
}

int dp[maxn][30];
void initrmq(int n)
{
    for (int i = 1; i <= n; i++)
        dp[i][0] = height[i];
    for (int j = 1; (1 << j) <= n; j++)
        for (int i = 1; i + (1 << j) - 1 <= n; i++)
            dp[i][j] = std::min(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
}
int rmq(int l, int r)
{
    int k = 31 - __builtin_clz(r - l + 1);
    return std::min(dp[l][k], dp[r - (1 << k) + 1][k]);
}
int lcp(int a, int b)
{
    a = rank[a], b = rank[b];
    if (a > b) std::swap(a, b);
    return rmq(a + 1, b);
}
} // namespace Suffix_Array
using Suffix_Array::build_sa;
using Suffix_Array::initrmq;
using Suffix_Array::lcp;
using Suffix_Array::rank;
using Suffix_Array::rmq;
using Suffix_Array::sa;

int rt[maxn];
int cnt;
int lson[maxn << 5], rson[maxn << 5], sum[maxn << 5];
#define Lson l, m, lson[x], lson[y]
#define Rson m + 1, r, rson[x], rson[y]
void update(int p, int l, int r, int& x, int y)
{
    lson[++cnt] = lson[y], rson[cnt] = rson[y], sum[cnt] = sum[y] + 1, x = cnt;
    if (l == r) return;
    int m = (l + r) >> 1;
    if (p <= m)
        update(p, Lson);
    else
        update(p, Rson);
}
int query(int l, int r, int x, int y, int k)
{
    if (l == r) return l;
    int m = (l + r) >> 1;
    int s = sum[lson[y]] - sum[lson[x]];
    if (s >= k)
        return query(Lson, k);
    else
        return query(Rson, k - s);
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int n, m;
        scanf("%d%d", &n, &m);
        scanf("%s", Suffix_Array::s);
        build_sa(128, n);
        initrmq(n);
        cnt = 0;
        // for (int i = 1; i <= n; i++) debug("%d", sa[i]);
        // for (int i = 0; i < n; i++) printf("%d ", rank[i]);
        // puts("");
        for (int i = 1; i <= n; i++) update(sa[i], 0, n - 1, rt[i], rt[i - 1]);
        for (int i = 0, L, R, k; i < m; i++)
        {
            scanf("%d%d%d", &L, &R, &k);
            --L, --R;
            int l = 1, r = rank[L] - 1;
            int lb = rank[L], ub = rank[L];
            // debug("[%d %d]", lb, ub);
            while (l <= r)
            {
                int m = l + r >> 1;
                if (rmq(m + 1, rank[L]) >= R - L + 1)
                    lb = m, r = m - 1;
                else
                    l = m + 1;
            }
            l = rank[L] + 1, r = n;
            while (l <= r)
            {
                int m = l + r >> 1;
                if (rmq(rank[L] + 1, m) >= R - L + 1)
                    ub = m, l = m + 1;
                else
                    r = m - 1;
            }
            // [lb, ub]
            // debug("[%d %d]", lb, ub);
            if (ub - lb + 1 < k)
                puts("-1");
            else
                printf("%d\n", query(0, n - 1, rt[lb - 1], rt[ub], k) + 1);
        }
    }
}
