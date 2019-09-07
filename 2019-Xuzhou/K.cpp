#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#include <local_debug.h>
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__);
#else
#define debug(...)
#endif

using pp = std::pair<int, int>;
using i64 = long long;

const int MAXN = 2000;

int n;
pp arr[MAXN];
std::set<pp> points;
std::map<pp, int> centers;

int main() {

    std::scanf("%d", &n);
    for(int i = 0; i < n; ++i) {

        std::scanf("%d%d", &arr[i].first, &arr[i].second);
        arr[i].first *= 2;
        arr[i].second *= 2;
        points.insert(arr[i]);

    }
    if(n <= 2) std::puts("0");
    else {
        
        for(int i = 0; i < n - 1; ++i)
            for(int j = i + 1; j < n; ++j) {
                
                pp center = {(arr[i].first + arr[j].first) / 2, (arr[i].second + arr[j].second) / 2};
                ++centers[center];

            }
        
        int result = n;
        for(auto&& p : centers) {

            int value = n - p.second * 2 - points.count(p.first);
            result = std::min(result, value);

        }
        std::printf("%d\n", result);

    }
    
}
