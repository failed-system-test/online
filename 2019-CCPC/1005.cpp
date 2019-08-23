#include <bits/stdc++.h>

typedef long long i64;
typedef unsigned long long u64;

const int MOD = 1000000007;
const int MAXN = 5000000;


bool visited[MAXN];
int pc;
int primes[MAXN / 4];
int phi[MAXN];

i64 pow64(i64 a, i64 b) {
    
    if(!b) return 1;
    a %= MOD;
    i64 result = 1;
    while(b) {
        
        if(b & 1) result = result * a % MOD;
        a = a * a % MOD;
        b >>= 1;
        
    }
    return result;
    
}
i64 inv64(i64 x) { return pow64(x, MOD - 2); }

void generate() {
    
    pc = 0;
    phi[0] = 0;
    phi[1] = 1;
    for(int i = 2; i < MAXN; ++i) {
        
        if(!visited[i]) primes[pc++] = i, phi[i] = i - 1;
        for(int j = 0; j < MAXN && i * primes[j] < MAXN; ++j) {
            
            int k = i * primes[j];
            visited[k] = true;
            if(!(i % primes[j])) {
                
                phi[k] = phi[i] * primes[j];
                break;
                
            } else phi[k] = phi[i] * (primes[j] - 1);
            
        }
        
    }
    
    for(int i = 1; i < MAXN; ++i)
        phi[i] = (phi[i - 1] + i64(phi[i]) * i) % MOD;
    
}

std::unordered_map<int, int> spi;
int sumPhi(int x) {
    
    if(x < MAXN) return phi[x];
    auto it = spi.find(x);
    if(it != spi.end()) return it->second;
    int result = (__int128(x) * (x + 1) * (x * 2 + 1) / 6) % MOD;
    for(int l = 2, r; l <= x; l = r + 1) {
        
        r = x / (x / l);
        result = ((result - (i64(l + r) * (r - l + 1) / 2) % MOD * sumPhi(x / l) % MOD) % MOD + MOD) % MOD;
        
    }
    return spi[x] = result;
    
}

const int INV2 = inv64(2);

int t;
int n, a, b;

int main() {
    
    generate();
    
    std::scanf("%d", &t);
    for(int test = 0; test < t; ++test) {
        
        std::scanf("%d%d%d", &n, &a, &b);
        std::printf("%d\n", int(i64(sumPhi(n) + MOD - 1) % MOD * INV2 % MOD));
        
    }
    
}