#include<bits/stdc++.h>
using namespace std;

const int maxn = 5e5+5;
int a[maxn];
using ll = long long ;

int n,k;
int solve(vector<int> &a, int less){
    if(a.empty()) return 0;
    sort(a.begin(),a.end(),greater<int>());
    ll tot = k;
    int num = 1;
    a.push_back(0);
    for(int i=0;i<a.size() - 1;i++){
        ll tmp = 1LL * num * (a[i] - a[i+1]);
        // cerr << "a[i] = " << a[i] << endl;
        // cerr << "tmp = " << tmp << endl;
        if(tot - tmp <= 0)
            return a[i] - tot / num; 
        tot -= tmp; 
        num++;
    }
    return less;
}
int main(){
    while(~scanf("%d%d",&n,&k)){
        ll sum = 0;
        for(int i=1;i<=n;i++) scanf("%d",a+i), sum += a[i];
        ll avr = sum / n;
        vector<int> b,c;
        for(int i=1;i<=n;i++){
            if(a[i] > avr) b.push_back(a[i] - avr);
            else if(a[i] < avr) c.push_back(avr - a[i]);
        }
        int t1 = solve(c,0);
        if(t1 == 0){
            if(sum % n == 0) puts("0");
            else puts("1");
        } else{
            int t2 = solve(b, 1);
            // printf("%d %d\n",t1,t2);
            printf("%d\n",t1 + t2);
        }
    }
}
