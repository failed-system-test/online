#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
#include <local_debug.h>
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__);
#else
#define debug(...)
#endif

typedef long long ll;
const int mod = 1e9 + 7;

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int k;
        ll n;
        scanf("%d%lld", &k, &n);
        vector<int> a(k * 2);
        for (int i = 0; i < k * 2; i++) scanf("%d", &a[i]);
        if (n <= k * 2)
        {
            int sum = 0;
            for (int i = 0; i < n; i++) (sum += a[i]) %= mod;
            printf("%d\n", sum);
        }
        else
        {
            int sum = 0;
            for (auto& t : a) (sum += t) %= mod;
            debug(sum);
            (sum += 1LL * a.back() * ((n - 2 * k) % mod) % mod) %= mod;
            printf("%d\n", sum);
        }
    }
}
