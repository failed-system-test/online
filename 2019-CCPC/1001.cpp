#include <bits/stdc++.h>

typedef long long i64;
typedef unsigned long long u64;

const int MAXN = 2000;

int t;
i64 a, b;

int main() {
    
    std::scanf("%d", &t);
    for(int test = 0; test < t; ++test) {
        
        std::scanf("%lld%lld", &a, &b);
        i64 c = a & b;
        if(!c) {
            
            c = 1;
            while(!(a & c) && !(b & c)) c <<= 1;
            
        }
        std::printf("%lld\n", c);
        
    }
    
}
