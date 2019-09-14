#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
#include <local_debug.h>
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__);
#else
#define debug(...)
#endif

const int MAXN = 1001000;
const int MAXP = 1100;

int n, p;

int s2[MAXP][MAXP];
bool visited[MAXN];
int arr[MAXN];

void init() {

    for(int i = 0; i <= n; ++i)
        visited[i] = false;

    s2[0][0] = 1;
    for(int i = 1; i <= p; ++i) {

        s2[i][0] = 0;
        for(int j = 1; j <= i; ++j)
            s2[i][j] = (s2[i - 1][j - 1] + s2[i - 1][j] * j) % p;

    }
    for(int i = 0; i <= p; ++i) {

        visited[i] = true;
        int sum = 0;
        for(int j = 0; j <= i; ++j)
            sum += s2[i][j];
        arr[i] = sum % p;

    }

}

int calc(int x) {

    if(visited[x]) return arr[x];
    visited[x] = true;
    return arr[x] = (calc(x - p) + calc(x - p + 1)) % p;

}

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {

        std::scanf("%d%d", &n, &p);
        init();
        std::printf("%d\n", calc(n));

    }
}
