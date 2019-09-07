// unsolved
#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
#include <local_debug.h>
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__);
#else
#define debug(...)
#endif

using ll = long long ;
const int maxn = 1e5+5;
const int mod = 998244353;

bool isprime[maxn];
vector<int> prime;
ll ans, n;
ll sn;
ll g[maxn];
ll sum[100], tot[100];

void init(){
    for(int i=2;i<=sn;i++) isprime[i] = true;
    for(int i=2;i<=sn;i++){
        if(isprime[i]){
            prime.push_back(i);
            for(int j=2*i;j<=sn;j+=i) isprime[j] = false;
        }
    }
    g[1] = 0;
    for(int i=2,x;i<=sn;i++){
        x = i;
        for(auto &v:prime){
            if(v > x) break;
            while(x % v == 0){
                g[i]++;
                x /= v;
            }
        }
        tot[g[i]]++;
        (sum[g[i]] += i) %= mod;
        ans = (ans + g[i] * (n - i + 1) % mod) % mod;
    }
}

ll tot_prime, sum_prime;

const ll inv2 = mod + 1 >> 1; 
struct SB{
    const static int N=1e6+5;
    ll f1[N],f2[N],n;
    ll cal_tot(ll n){
        int lim = sqrt(n);
        for(int i=1;i<=lim;++i)f1[i]=i-1,f2[i]=n/i-1;
        for(int p=2;p<=lim;++p){
            if(f1[p]==f1[p-1])continue;
            for(int i=1;i<=lim/p;++i)f2[i]-=f2[i*p]-f1[p-1];
            for(int i=lim/p+1;(ll)i<=n/(ll)p/(ll)p&&i<=lim;++i)f2[i]-=f1[n/i/p]-f1[p-1];
            for(int i=lim;i>=(ll)p*p;--i)f1[i]-=f1[i/p]-f1[p-1];
        }
        return f2[1];
    }
    
    inline ll S(const ll&x){return (x+1) % mod * (x % mod) % mod * inv2 % mod;}
    ll cal_sum(ll n){
        if(!n)return 0;
        ll lim=sqrt(n);
        for(ll i=1;i<=lim;++i)f1[i]=S(i),f2[i]=S(n/i);
        for(ll p=2;p<=lim;++p){
            if(f1[p] == f1[p-1]) continue;
            ll t=f1[p-1];
            for(ll i=1;i<=lim/p;++i)
                f2[i] = (f2[i] - (f2[i*p] - t + mod) % mod * p % mod + mod) % mod;
            for(ll i=lim/p+1;i<=lim&&i<=n/p/p;++i)
                f2[i] = (f2[i] - (f1[n/i/p]-t + mod) % mod * p % mod + mod) % mod;
            for(ll i=lim;i>=p*p;--i)
                f1[i] = (f1[i] - (f1[i/p]-t + mod) % mod * p % mod + mod) % mod;
	    }
	    return f2[1];
    }
} sb;
void first(){
    tot_prime = (sb.cal_tot(n) - sb.cal_tot(sn) + mod) % mod;
    sum_prime = (sb.cal_sum(n) - sb.cal_sum(sn) + mod) % mod;
    for(ll i=1;i<50;i++){  
        ll tmp = tot[i] * (n + 1) % mod * tot_prime % mod * (i + 1) % mod - sum[i] * (i + 1) % mod * sum_prime % mod + mod;
        cerr << tmp << endl;
        ans = (ans + tmp % mod) % mod;
    }
}


ll suf_g[maxn], suf_j[maxn], suf_gj[maxn];

void second(){
    for(ll i = sn;i>0;i--) suf_g[i] = (suf_g[i+1] + g[i]) % mod, suf_j[i] = (suf_j[i+1] + i) % mod, suf_gj[i] = (suf_gj[i+1] + g[i] * i % mod) % mod;
    for(ll i=1; i <= sn;i++){
        ll j = n / i;
        while(j * i < n) j++;
        if(j > sn) continue;
        ll len = sn - j + 1;
        ll tmp = len * g[i] % mod * (n + 1) % mod + suf_g[j] * (n+1) % mod;
        tmp %= mod;
        ll tmp1 = g[i] * i % mod * suf_j[j] % mod +  i * suf_gj[j] % mod;
        tmp1 = (mod - tmp1 % mod) % mod;

        tmp = (tmp - tmp1 + mod) % mod;
        ans = (ans + tmp) % mod;
    }
}
int main() {
    scanf("%lld",&n);
    ans = 0;
    sn = sqrt(n);
    while(sn * sn > n) sn--;

    init();
    first();
    second();
    printf("%lld\n",ans);
}
