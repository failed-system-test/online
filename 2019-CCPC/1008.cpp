#include <bits/stdc++.h>

typedef long long i64;
typedef unsigned long long u64;

const int MAXN = 101000;

int t;
int n, m;
i64 k;
i64 arr[MAXN];

int main() {
    
    std::scanf("%d", &t);
    for(int test = 0; test < t; ++test) {
        
        std::scanf("%d%lld", &n, &k);
        for(int i = 0; i < n; ++i)
            std::scanf("%lld", &arr[i]);
        
        i64 sum = 0, s0 = 0;
        for(int i = 0; i < n; ++i)
            sum += arr[i], s0 += arr[i] / k;
        
        if(s0 >= n - 1) std::printf("%lld\n", sum + k);
        else {
            
            m = n - 1;
            for(int i = 0; i < n; ++i)
                m -= arr[i] / k, arr[i] %= k;
            
            std::sort(arr, arr + n, std::greater<int>());
            i64 result = k * n;
            for(int i = m; i < n; ++i)
                result += arr[i];
            
            std::printf("%lld\n", result);
            
        }
        
    }
    
}
