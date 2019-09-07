#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
#include <local_debug.h>
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__);
#else
#define debug(...)
#endif

const int MAXN = 501000;

int n, m;
int arr[MAXN];
int result[MAXN];
int cnt;
int idx[MAXN];

int main() {
    
    std::scanf("%d%d", &n, &m);
    for(int i = 0; i < n; ++i)
        std::scanf("%d", &arr[i]);

    for(int i = n - 1; i >= 0; --i) {

        if(!cnt) idx[cnt++] = i, result[i] = -1;
        else {

            auto it = std::lower_bound(idx, idx + cnt, arr[i] + m, [](int a, int b) {
                return arr[a] < b;
            });
            if(it == idx + cnt) result[i] = -1;
            else result[i] = *it - i - 1;
            if(arr[i] > arr[idx[cnt - 1]]) idx[cnt++] = i;

        }

    }
    for(int i = 0; i < n; ++i)
        std::printf("%d%c", result[i], " \n"[i == n - 1]);

}
