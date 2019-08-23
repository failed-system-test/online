#include <bits/stdc++.h>

typedef long long i64;
typedef unsigned long long u64;

const int MAXN = 101000;

using li = std::list<int>;

int n, m;
int arr[MAXN];
li list;
li::iterator pos[MAXN];

int main() {
    
    std::scanf("%d%d", &n, &m);
    for(int i = 0; i < n; ++i)
        std::scanf("%d", &arr[i]), --arr[i];
    
    for(int i = 0; i < n; ++i)
        list.push_back(arr[i]), pos[arr[i]] = --list.end();
    
    for(int i = 0; i < m; ++i) {
        
        int x;
        std::scanf("%d", &x), --x;
        auto it = pos[x];
        list.erase(it);
        list.push_front(x);
        pos[x] = list.begin();
        
    }
    
    for(int x : list)
        std::printf("%d ", x + 1);
    
}
