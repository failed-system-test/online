#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
#include <local_debug.h>
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__);
#else
#define debug(...)
#endif

const int maxn = 3e5 + 5;
struct Palindromic_Tree
{
    int ch[maxn][26], f[maxn], len[maxn], s[maxn];
    int cnt[maxn]; // 结点表示的本质不同的回文串的个数(调用count()后)
    int num[maxn]; // 结点表示的最长回文串的最右端点为回文串结尾的回文串个数
    int mask[maxn];
    int last, sz, n;
    int newnode(int x)
    {
        memset(ch[sz], 0, sizeof(ch[sz]));
        cnt[sz] = num[sz] = 0, len[sz] = x;
        mask[sz] = 0;
        return sz++;
    }
    void init()
    {
        sz = 0;
        newnode(0), newnode(-1);
        last = n = 0, s[0] = -1, f[0] = 1;
    }
    int get_fail(int u)
    {
        while (s[n - len[u] - 1] != s[n]) u = f[u];
        return u;
    }
    void add(int c)
    { // c-='a'
        s[++n] = c;
        int u = get_fail(last);
        if (!ch[u][c])
        {
            int np = newnode(len[u] + 2);
            f[np] = ch[get_fail(f[u])][c];
            num[np] = num[f[np]] + 1;
            mask[np] = (mask[u] | (1 << c));
            ch[u][c] = np;
        }
        last = ch[u][c];
        cnt[last]++;
    }
    void count()
    {
        for (int i = sz - 1; i > 1; i--) cnt[f[i]] += cnt[i];
    }
    long long solve()
    {
        long long ans = 0;
        for (int i = 2; i < sz; i++)
        {
            debug(mask[i], cnt[i]);
            ans += __builtin_popcount(mask[i]) * cnt[i];
        }
        return ans;
    }

} pam;

char s[maxn];

int main()
{
    scanf("%s", s);
    pam.init();
    for (int i = 0; s[i]; i++) pam.add(s[i] - 'a');
    pam.count();
    printf("%lld\n", pam.solve());
}
