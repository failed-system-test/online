#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
#include <local_debug.h>
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__);
#else
#define debug(...)
#endif

using i64 = long long;

const int mod = 119 << 23 | 1;

using Arr = int[129];

inline int Pow(const Arr* a, long long n)
{
    n %= (mod - 1);
    int t = 1;
    for(int i = 0; n; ++i, n >>= 7) {
        
        int x = n & 127;
        if(x) t = i64(t) * a[i][x] % mod;

    }
    return t;
}

const int sq = 473844410;
const int inv2 = mod + 1 >> 1;
const int rt1 = 1LL * (sq + 3) * inv2 % mod;
const int rt2 = 1LL * (mod - sq + 3) * inv2 % mod;

int tt1[11][129], tt2[11][129];

const int A = 169935932;
const int B = 329186245;
// 0 1 3
int main()
{
    debug(1LL * sq * sq % mod);
    debug(rt1, rt2);
    tt1[0][0] = 1, tt2[0][0] = 1;
    for(int i = 1; i <= 128; ++i)
        tt1[0][i] = i64(tt1[0][i - 1]) * rt1 % mod, tt2[0][i] = i64(tt2[0][i - 1]) * rt2 % mod;
    for(int i = 1; i < 10; ++i) {

        tt1[i][0] = 1, tt2[i][0] = 1;
        for(int j = 1; j <= 128; ++j) {

            tt1[i][j] = i64(tt1[i][j - 1]) * tt1[i - 1][128] % mod;
            tt2[i][j] = i64(tt2[i][j - 1]) * tt2[i - 1][128] % mod;

        }

    }
    int q;
    long long n;
    scanf("%d%lld", &q, &n);
    int ans = 0;
    int tmp;
    for (int i = 0; i < q; i++)
    {
        tmp = (1LL * A * Pow(tt1, n + 1) + 1LL * B * Pow(tt2, n + 1)) % mod;
        // debug(tmp);
        ans ^= tmp;
        n ^= (1LL * tmp * tmp);
    }
    printf("%d\n", ans);
}
