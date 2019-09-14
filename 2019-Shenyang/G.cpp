#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
#include <local_debug.h>
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__);
#else
#define debug(...)
#endif

using i64 = long long;

const int MAXN = 1001000;

int t;
char ns[MAXN];
int n;
double a;

int main() {
    
    std::scanf("%d", &t);
    for(int test = 0; test < t; ++test) {

        std::scanf("%s%lf", &ns, &a);
        int len = std::strlen(ns);
        if(len > 5) n = 100000;
        else std::sscanf(ns, "%d", &n);
        double result = 2;
        for(int i = 1; i < n * 2; ++i)
            result = 1 / (1 + 1 / result) + 1;
        std::printf("%.10f\n", result * a);

    }

}
