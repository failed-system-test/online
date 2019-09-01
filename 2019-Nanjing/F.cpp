#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
#include <local_debug.h>
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__);
#else
#define debug(...)
#endif
#define lson (rt << 1)
#define rson (rt << 1 | 1)
#define Lson l, m , lson
#define Rson m+1,r, rson
const int maxn = 1e5+5;
using ll = long long ;
int a[maxn],pos[maxn];

struct Node{
    ll dp;
    int val;
} seg[maxn <<2];

void build(int l,int r,int rt){
    seg[rt].dp = -1e18;
    if(l == r) {
        seg[rt].val = a[l];
        return ;
    }
    int m = l + r >> 1;
    build(Lson);
    build(Rson);
}

void update(int l,int r,int rt,int p, ll x){
    if(l == r) {
        seg[rt].dp = x;
        return ;
    }
    int m = l + r >> 1;
    if(p <= m)update(Lson,p,x);
    else update(Rson, p,x);
    auto &o = seg[rt], &ls = seg[lson], &rs = seg[rson];
    if(rs.dp >= 0 && ls.dp >= 0){
        if(rs.val > ls.val) o = rs;
        else o = ls;
    } else if(rs.dp >= 0){
        o = rs;
    } else o = ls;
}
Node query(int l,int r,int rt,int L,int R){
    if(L <= l && R >= r) return seg[rt];
    int m = l + r >> 1;
    Node ret;
    ret.dp = -1e18;
    ret.val = -1;
    if(L <= m) 
        ret = query(Lson,L,R);
    if(m+1 <= R) {
        auto it = query(Rson,L,R);
        if(it.dp >= 0 && ret.dp >= 0){
            if(it.val > ret.val) ret = it;
        } else if(it.dp >= 0) ret = it;
    }
    return ret;
}
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        int n,k;
        scanf("%d%d",&n,&k);
        for(int i=1;i<=n;i++) scanf("%d",a+i), pos[a[i]] = i;
        build(1,n,1); 
        for(int i=1;i<=n;i++){
            int l = max(1, pos[i] - k);
            int r = min(n, pos[i] + k);
            auto res = query(1,n,1,l,r);
            if(res.dp < 0) res.dp = 0;
            update(1,n,1,pos[i],res.dp+1);
        }
        for(int i=1;i<=n;i++) printf("%lld%c",query(1,n,1,pos[i],pos[i]).dp, i == n ? '\n': ' ');
    }
}
