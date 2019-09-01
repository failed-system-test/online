#include <bits/stdc++.h>

using i64 = long long;

i64 mm(i64 x, i64 m) {

    return x < m ? x : x % m + m;

}

i64 pow64(i64 a, i64 b, i64 m) {

    i64 result = 1;
    while(b) {
        
        if(b & 1) result = mm(result * a, m);
        a = mm(a * a, m);
        b >>= 1;

    }
    return result;

}

const int N = 1001000;
int phi[N] = {0, 1};
void caleuler()
{
    for (int i = 2; i < N; i++)
        if (!phi[i])
            for (int j = i; j < N; j += i)
            {
                if (!phi[j]) phi[j] = j;
                phi[j] = phi[j] / i * (i - 1);
            }
}

int t;
int a, b, m;

int calc(int a, int b, int m) {

    if(m == 1) return 1;
    if(!b) return 1;
    int p = phi[m];
    int x = calc(a, b - 1, p);
    return pow64(a, x, m);
    
}

int main() {

    caleuler();

    std::scanf("%d", &t);
    for(int i = 0; i < t; ++i) {

        std::scanf("%d%d%d", &a, &b, &m);
        std::printf("%d\n", calc(a, b, m) % m);

    }

}
