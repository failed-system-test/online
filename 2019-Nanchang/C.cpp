#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
#include <local_debug.h>
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__);
#else
#define debug(...)
#endif

typedef long long ll;
typedef long double ld;
const int inf = 0x3f3f3f3f;
const int maxn = 200000 + 100;
const int maxb = 1000;
int match[4] = {2, 0, 1, 9};
struct node
{
    int rm[5][5];
};
node sig[maxn * 4];
char s[maxn];

int n;
void pushup(int rt)
{
    const int lchild = rt << 1;
    const int rchild = rt << 1 | 1;
    for (int i = 0; i < 5; i++)
    {
        for (int j = i; j < 5; j++)
        {
            for (int k = i; k <= j; k++)
            {
                sig[rt].rm[i][j] = min(sig[rt].rm[i][j], sig[lchild].rm[i][k] + sig[rchild].rm[k][j]);
            }
        }
    }
}
void build(int l = 0, int r = n, int rt = 1)
{
    if (l >= r)
    {
        return;
    }
    memset(sig[rt].rm, inf, sizeof(sig[rt].rm));
    if (l + 1 == r)
    {
        for (int i = 0; i < 5; i++)
        {
            sig[rt].rm[i][i] = 0;
        }
        if (s[l] == '2')
        {
            sig[rt].rm[0][0] = 1;
            sig[rt].rm[0][1] = 0;
        }
        else if (s[l] == '0')
        {
            sig[rt].rm[1][1] = 1;
            sig[rt].rm[1][2] = 0;
        }
        else if (s[l] == '1')
        {
            sig[rt].rm[2][2] = 1;
            sig[rt].rm[2][3] = 0;
        }
        else if (s[l] == '9')
        {
            sig[rt].rm[3][3] = 1;
            sig[rt].rm[3][4] = 0;
        }
        else if (s[l] == '8')
        {
            sig[rt].rm[3][3] = sig[rt].rm[4][4] = 1;
        }
        return;
    }
    const int mid = l + (r - l) / 2;
    build(l, mid, rt << 1);
    build(mid, r, rt << 1 | 1);
    pushup(rt);
    /*    cout << "debug :  "<<rt << endl;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j ++)
        cout << (sig[rt].rm[i][j]== inf ? -1 : sig[rt].rm[i][j]) << " ";
        cout << endl;
    }
    */
}

node query(int L, int R, int l = 0, int r = n, int rt = 1)
{
    if (L <= l && r <= R)
    {
        return sig[rt];
    }
    node ans;
    memset(ans.rm, inf, sizeof(ans.rm));
    if (l + 1 == r)
    {
        return ans;
    }
    node lhs, rhs;
    memset(lhs.rm, inf, sizeof(lhs.rm));
    memset(rhs.rm, inf, sizeof(rhs.rm));
    for (int i = 0; i < 5; i++)
    {
        lhs.rm[i][i] = 0;
        rhs.rm[i][i] = 0;
    }
    const int mid = l + (r - l) / 2;
    if (L < mid)
    {
        lhs = query(L, R, l, mid, rt << 1);
    }
    if (R > mid)
    {
        rhs = query(L, R, mid, r, rt << 1 | 1);
    }
    for (int i = 0; i < 5; i++)
    {
        for (int j = i; j < 5; j++)
        {
            for (int k = i; k <= j; k++)
            {
                ans.rm[i][j] = min(ans.rm[i][j], lhs.rm[i][k] + rhs.rm[k][j]);
            }
        }
    }
    return ans;
}
int main()
{
    int q;
    while (~scanf("%d%d", &n, &q))
    {
        scanf("%s", s);
        reverse(s, s + n);
        build();
        for (int i = 0; i < q; i++)
        {
            int l, r;
            scanf("%d%d", &l, &r);
            r = n - r + 1, l = n - l + 1;
            swap(l, r);
            debug(l, r);
            node ans = query(l - 1, r);
            if (ans.rm[0][4] == inf)
            {
                ans.rm[0][4] = -1;
            }
            printf("%d\n", ans.rm[0][4]);
        }
    }
}
