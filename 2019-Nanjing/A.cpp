#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
#include <local_debug.h>
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__);
#else
#define debug(...)
#endif

const int N = 1 << 20;
long long bit[N];
void update(int x, int v)
{
    for (; x < N; x += x & -x) bit[x] += v;
}
long long query(int x)
{
    long long ret = 0;
    for (; x; x -= x & -x) ret += bit[x];
    return ret;
}
struct Point
{
    int x, y;
    int value;
    Point(int x, int y, int v) : x(x), y(y), value(v) {}
    bool operator<(const Point& rhs) const { return y == rhs.y ? x < rhs.x : y < rhs.y; }
};
struct Query : public Point
{
    int id, sgn;
    Query(int x, int y, int id, int sgn, int v = -1) : Point(x, y, v), id(id), sgn(sgn) {}
};

using i64 = long long;

i64 gao(int x, int y, int n)
{
    --x, --y;
    int p = std::min({x, y, n - x - 1, n - y - 1}), q = n - p - 1;
    i64 base = i64(n) * n - i64(n - 2 * p) * i64(n - 2 * p) + 1;
    if (x == q) return base + (q - y);
    base += n - 2 * p - 1;
    if (y == p) return base + (q - x);
    base += n - 2 * p - 1;
    if (x == p) return base + (y - p);
    base += n - 2 * p - 1;
    return base + (x - p);
}

int nb(long long x)
{

    int result = 0;
    while (x)
    {

        result += x % 10;
        x /= 10;
    }
    return result;
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        memset(bit, 0, sizeof(bit));
        int n, m, q;
        scanf("%d%d%d", &n, &m, &q);
        std::vector<Point> points;
        std::vector<Query> queries;
        vector<long long> ans(q);
        for (int i = 0, x, y; i < m; i++)
        {
            scanf("%d%d", &x, &y);
            long long v = nb(gao(x, y, n));
            debug(v);
            points.emplace_back(x, y, v);
        }
        points.emplace_back(1, 1000001, 0);
        std::sort(points.begin(), points.end());
        for (int i = 0, x1, y1, x2, y2; i < q; i++)
        {
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            queries.emplace_back(x1 - 1, y1 - 1, i, 1);
            queries.emplace_back(x1 - 1, y2, i, -1);
            queries.emplace_back(x2, y1 - 1, i, -1);
            queries.emplace_back(x2, y2, i, 1);
        }
        std::sort(queries.begin(), queries.end());
        for (int pi = 0, pj, qi = 0, qj; pi < m + 1 || qi < q * 4; pi = pj, qi = qj)
        {
            for (qj = qi; qj < q * 4 && queries[qj].y < points[pi].y; qj++)
            {
                int id = queries[qj].id, sgn = queries[qj].sgn;
                long long res = query(queries[qj].x);
                ans[id] += sgn * res;
            }
            for (pj = pi; pj < m + 1 && points[pi].y == points[pj].y; pj++) update(points[pj].x, points[pj].value);
        }
        for (int i = 0; i < q; i++) printf("%lld\n", ans[i]);
    }
}
