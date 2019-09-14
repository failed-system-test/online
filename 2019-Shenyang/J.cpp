#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
#include <local_debug.h>
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__);
#else
#define debug(...)
#endif

const int mod = 1e9 + 7;

typedef long long ll;
const int maxn = 1 << 20;
int a[maxn];
int f[maxn], invf[maxn];

ll pow(ll x, ll n, ll mod)
{
    assert(n >= 0);
    ll ret = mod != 1;
    for (x %= mod; n; n >>= 1, x = x * x % mod)
        if (n & 1) ret = ret * x % mod;
    return ret;
}
ll inv(ll a, ll p) { return pow(a, p - 2, p); }
void init()
{
    f[0] = 1;
    for (int i = 1; i < maxn; i++) f[i] = ((ll)f[i - 1] * i) % mod;
    invf[maxn - 1] = inv(f[maxn - 1], mod);
    for (int i = maxn - 2; ~i; i--) invf[i] = (ll)invf[i + 1] * (i + 1) % mod;
}
inline int p(int n, int m) { return n < m || m < 0 ? 0 : (ll)f[n] * invf[n - m] % mod; }

int main()
{
    init();
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int n, x;
        scanf("%d%d", &n, &x);
        if (x >= n)
        {
            puts("1");
            continue;
        }
        a[0] = 1;
        for (int i = 1; i < x; i++) a[i] = f[i];
        for (int i = x - 1; i < n; i++)
        {
            a[i + 1] = (a[i] - p(i - 1, x - 1) * (ll)a[i - x] % mod + mod) % mod * i % mod + a[i];
            a[i + 1] %= mod;
        }
        printf("%lld\n", (ll)a[n] * invf[n] % mod);
    }
}
