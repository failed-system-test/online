#include <bits/stdc++.h>

typedef long long i64;
typedef unsigned long long u64;

const int MAXN = 2000;

int t, k;
bool mat[MAXN][MAXN];

int main() {
    
    mat[0][0] = 0;
    mat[0][1] = 0;
    mat[1][0] = 0;
    mat[1][1] = 1;
    
    for(int i = 1; i < 10; ++i) {
        
        int s = 1 << i;
        int t = 2 << i;
        for(int x = 0; x < t; ++x)
            for(int y = 0; y < t; ++y) {
                
                mat[x][y] = mat[x % s][y % s] ^ ((x / s) && (y / s));
                
            }
        
    }
    
    std::scanf("%d", &t);
    for(int test = 0; test < t; ++test) {
        
        std::scanf("%d", &k);
        int s = 1 << k;
        for(int x = 0; x < s; ++x) {
            
            for(int y = s - 1; y >= 0; --y)
                std::putchar("CP"[mat[x][y]]);
            std::putchar('\n');
            
        }
        
    }
    
}
