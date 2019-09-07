#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> query;
vector<int> a;

const int N = 1 << 21;
int fa[N];

int find(int x)
{
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

void unite(int x, int y)
{ // x->y;
    x = find(x), y = find(y);
    if (x == y) return;
    fa[x] = y;
}

int getid(int x)
{
    return lower_bound(a.begin(), a.end(), x) - a.begin();
}

int main()
{
    int n, q;
    scanf("%d%d", &n, &q);
    query.reserve(q);
    for (int i = 0, z, x; i < q; i++)
    {
        scanf("%d%d", &z, &x);
        query.emplace_back(z, x);
        if (z == 1)
        {
            a.push_back(x);
            a.push_back(x + 1);
        }
    }
    a.push_back(n + 1);
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
    for (int i = 0; i < a.size(); i++) fa[i] = i;
    for (auto& qq : query)
    {
        if (qq.first == 2)
        {
            int id = getid(qq.second);
            if(a[id] != qq.second) {
                printf("%d\n", qq.second);
                continue;
            }
            int ans = find(id);
            if (a[ans] == n + 1) {
                puts("-1");
            } else {
                printf("%d\n", a[ans]);
            }
        }
        else
        {
            unite(getid(qq.second), getid(qq.second + 1));
        }
    }
}
