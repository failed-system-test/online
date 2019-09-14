#include <bits/stdc++.h>


const int MAXN = 101000;

struct Hand {

    char name[20];
    char cards[13];
    std::vector<char> count[4];
    char sum;

    int getRank() const {

        if(count[0].size() == 5) {

            if(cards[9] == 1 && cards[10] == 1 && cards[11] == 1 && cards[12] == 1 && cards[0] == 1) return 0;
            if(count[0][0] + 4 == count[0][4]) return 1;

        }
        if(count[3].size() == 1) return 2;
        if(count[2].size() == 1) {

            if(count[1].size() == 1) return 3;
            else return 4;

        }
        if(count[1].size() == 2) return 5;
        if(count[1].size() == 1) return 6;
        return 7;

    }

    friend bool operator <(const Hand& a, const Hand& b) {

        int ra = a.getRank(), rb = b.getRank();
        if(ra != rb) return ra < rb;
        switch(ra) {
        case 0: break;
        case 1: {
            
            if(a.count[0][0] != b.count[0][0]) return a.count[0][0] > b.count[0][0];
            break;

        }
        case 2: {
            
            if(a.count[3][0] != b.count[3][0]) return a.count[3][0] > b.count[3][0];
            if(a.count[0][0] != b.count[0][0]) return a.count[0][0] > b.count[0][0];
            break;

        }
        case 3: {
            
            if(a.count[2][0] != b.count[2][0]) return a.count[2][0] > b.count[2][0];
            if(a.count[1][0] != b.count[1][0]) return a.count[1][0] > b.count[1][0];
            break;

        }
        case 4: {
            
            if(a.count[2][0] != b.count[2][0]) return a.count[2][0] > b.count[2][0];
            int sa = a.count[0][0] + a.count[0][1], sb = b.count[0][0] + b.count[0][1];
            if(sa != sb) return sa > sb;
            break;

        }
        case 5: {
            
            if(a.count[1][1] != b.count[1][1]) return a.count[1][1] > b.count[1][1];
            if(a.count[1][0] != b.count[1][0]) return a.count[1][0] > b.count[1][0];
            if(a.count[0][0] != b.count[0][0]) return a.count[0][0] > b.count[0][0];
            break;

        }
        case 6: {
            
            if(a.count[1][0] != b.count[1][0]) return a.count[1][0] > b.count[1][0];
            int sa = a.count[0][0] + a.count[0][1] + a.count[0][2], sb = b.count[0][0] + b.count[0][1] + b.count[0][2];
            if(sa != sb) return sa > sb;
            break;

        }
        case 7: {

            if(a.sum != b.sum) return a.sum > b.sum;
            break;

        }
        }
        return std::strcmp(a.name, b.name) < 0;

    }

};


int read() {

    char c;
    while(std::isspace(c = std::getchar()));
    if(c == 'A') return 0;
    if(c == 'J') return 10;
    if(c == 'Q') return 11;
    if(c == 'K') return 12;
    if(c == '1') { std::getchar(); return 9; }
    return c - '1';

}

int n;
Hand hands[MAXN];
int indexs[MAXN];

int main() {

    std::scanf("%d", &n);
    for(int i = 0; i < n; ++i) {

        std::scanf("%s", hands[i].name);
        for(int j = 0; j < 5; ++j)
            ++hands[i].cards[read()];
        for(int j = 0; j < 13; ++j) {
            
            hands[i].sum += j * hands[i].cards[j];
            if(hands[i].cards[j] == 5) *(int*)0 = 0;
            if(hands[i].cards[j])
                hands[i].count[hands[i].cards[j] - 1].push_back(j);
        }
        indexs[i] = i;

    }

    std::sort(indexs, indexs + n, [](int a, int b) { return hands[a] < hands[b]; });
    for(int i = 0; i < n; ++i)
        std::puts(hands[indexs[i]].name);

}
