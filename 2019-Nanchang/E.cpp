#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
#include <local_debug.h>
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__);
#else
#define debug(...)
#endif

const int MAXQ = 200;

int t, n, m, q;
int qq[MAXQ];
int result[MAXQ];

int main()
{
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d%d%d", &n, &m, &q);
        std::unordered_map<int, int> mm;
        for (int i = 0; i < q; ++i)
            std::scanf("%d", &qq[i]), --qq[i], mm[qq[i]] = i;
        std::deque<int> dq;
        for(int i = 0; i < n; ++i) {

            auto it = mm.find(i);
            if(it == mm.end()) dq.push_back(-1);
            else dq.push_back(it->second);

        }
        int count = q;
        for(int i = 0; i < n; ++i) {

            int x = dq.front();
            dq.pop_front();
            if(x >= 0) {

                result[x] = i;
                --count;
                if(!count) break;

            }
            for(int j = 0; j < m; ++j) {

                int y = dq.front();
                dq.pop_front();
                dq.push_back(y);

            }

        }
        for(int i = 0; i < q; ++i)
            std::printf("%d\n", result[i] + 1);
    }
}
