#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
#include <local_debug.h>
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__);
#else
#define debug(...)
#endif

const int MAXN = 1001000;

int n, m;
char s[MAXN], t[MAXN];
int nx[MAXN][26];

int main() {
    
    scanf("%d%d%s%s", &n, &m, s, t);

    for(int i = 0; i < 26; ++i)
        nx[n][i] = n;
    for(int i = n - 1; i >= 0; --i) {

        for(int j = 0; j < 26; ++j)
            nx[i][j] = nx[i + 1][j];
        nx[i][s[i] - 'a'] = i;

    }

    int result = -1;
    int cur = 0;
    for(int i = 0; i < m; ++i) {

        for(char j = t[i] + 1; j <= 'z'; ++j) {
            
            int p = nx[cur][j - 'a'];
            if(p < n) result = std::max(result, i + (n - p));

        }
        cur = nx[cur][t[i] - 'a'] + 1;
        if(cur >= n) break;

    }
    if(cur < n) result = std::max(result, m + (n - cur));

    std::printf("%d\n", result);

}
