#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
#include <local_debug.h>
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__);
#else
#define debug(...)
#endif

enum { UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3, TOP = 4, BOTTOM = 5 };
const int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
const int TRANS[6][4] = {
    {BOTTOM, TOP, UP, UP},
    {TOP, BOTTOM, DOWN, DOWN},
    {LEFT, LEFT, BOTTOM, TOP},
    {RIGHT, RIGHT, TOP, BOTTOM},
    {UP, DOWN, LEFT, RIGHT},
    {DOWN, UP, RIGHT, LEFT},
};

const int MAXX = 4010;
const int OFFSET = 5;
const int LIMIT = 20;

const int INF = 0x3f3f3f3f;

namespace SB {
int dp[MAXX][LIMIT][6];
void bfs() {
    
    std::memset(dp, -1, sizeof(dp));
    std::queue<std::tuple<int, int, int>> q;
    q.emplace(OFFSET, OFFSET, TOP);
    dp[OFFSET][OFFSET][TOP] = 0;
    do {

        auto t = q.front();
        q.pop();
        int x = std::get<0>(t), y = std::get<1>(t), s = std::get<2>(t), d = dp[x][y][s] + 1;
        for(int i = 0; i < 4; ++i) {
            
            int dx = x + DIR[i][0], dy = y + DIR[i][1], ds = TRANS[s][i];
            if(dx < 0 || dx >= MAXX || dy < 0 || dy >= LIMIT) continue;
            int& xx = dp[dx][dy][ds];
            if(xx >= 0) continue;
            xx = d;
            q.emplace(dx, dy, ds);

        }
        
    } while(!q.empty());

}

int getdis(int x1, int y1, int x2, int y2) {
    
    int dx = x2 - x1, dy = y2 - y1;
    if(dx < 0) dx = -dx;
    if(dy < 0) dy = -dy;
    if(dx < dy) std::swap(dx, dy);
    if(dy + OFFSET >= LIMIT) return dx + dy;
    return dp[dx + OFFSET][dy + OFFSET][TOP];

}
}

int dp[1 << 16][16];

int main() {

    SB::bfs();

    int T;
    scanf("%d", &T);
    while (T--)
    {
        int n;
        scanf("%d", &n);
        vector<pair<int, int>> p;
        for (int i = 0, x, y; i < n; i++)
        {
            scanf("%d%d", &x, &y);
            p.emplace_back(x, y);
        }
        for (int i = 0; i < (1 << n); i++)
            for (int j = 0; j < n; j++)
                dp[i][j] = INF;
        for (int i = 0; i < n; i++)
        {
            dp[1 << i][i] = SB::getdis(0, 0, p[i].first, p[i].second);
        }
        for (int i = 1; i < (1 << n); i++)
            for (int j = 0; j < n; j++)
                if (i >> j & 1)
                    for (int k = 0; k < n; k++)
                        if (!(i >> k & 1))
                            dp[i | (1 << k)][k] = min(dp[i | (1 << k)][k],
                                                      dp[i][j] + SB::getdis(p[j].first, p[j].second, p[k].first, p[k].second));
        printf("%d\n", *min_element(dp[(1 << n) - 1], dp[(1 << n) - 1] + n));
    }
}
