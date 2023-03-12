#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
#ifdef APURBA
#include "DEBUG_TEMPLATE.h"
#else
#define HERE
#define debug(args...)
#endif
#define ALL(x) x.begin(),x.end()


const int N = 1e5 +5;
typedef pair<int,int> pii;




namespace NTT {
 vector<int> perm, wp[2];
 const int mod = 998244353, G = 3; ///G is the primitive root of M
 int root, inv, N, invN;
 int power(int a, int p) {
  int ans = 1;
  while (p) {
   if (p & 1) ans = (1LL*ans*a)%mod;
   a = (1LL*a*a)%mod;
   p >>= 1;
  }
  return ans;
 }

 void precalculate(int n) {
//  assert( (n&(n-1)) == 0 && (mod-1)%n==0);
  N = n;
  invN = power(N, mod-2);
  perm = wp[0] = wp[1] = vector<int>(N);

  perm[0] = 0;
  for (int k=1; k<N; k<<=1)
   for (int i=0; i<k; i++) {
    perm[i] <<= 1;
    perm[i+k] = 1 + perm[i];
   }

  root = power(G, (mod-1)/N);
  inv = power(root, mod-2);
  wp[0][0]=wp[1][0]=1;
  for (int i=1; i<N; i++) {
   wp[0][i] = (wp[0][i-1]*1LL*root)%mod;
   wp[1][i] = (wp[1][i-1]*1LL*inv)%mod;
  }
 }
 void fft(vector<int> &v, bool invert = false) {
  if (v.size() != perm.size())   precalculate(v.size());
  for (int i=0; i<N; i++)
   if (i < perm[i])
    swap(v[i], v[perm[i]]);

  for (int len = 2; len <= N; len *= 2) {
   for (int i=0, d = N/len; i<N; i+=len) {
    for (int j=0, idx=0; j<len/2; j++, idx += d) {
     int x = v[i+j];
     int y = (wp[invert][idx]*1LL*v[i+j+len/2])%mod;
     v[i+j] = (x+y>=mod ? x+y-mod : x+y);
     v[i+j+len/2] = (x-y>=0 ? x-y : x-y+mod);
    }
   }
  }
  if (invert) {
   for (int &x : v) x = (x*1LL*invN)%mod;
  }
 }
 vector<int> multiply(vector<int> a, vector<int> b) {
  int n = 1;
  while (n < a.size()+ b.size())  n<<=1;
  a.resize(n);
  b.resize(n);

  fft(a);
  fft(b);
  for (int i=0; i<n; i++) a[i] = (a[i] * 1LL * b[i])%mod;
  fft(a, true);
  return a;
 }
};
const int oo=998244353;

inline int add(int a,int b)
{
    a+=b;
    return a>=oo?a-oo:a;
}
inline int gun(int a,int b)
{
    return a*1LL*b%oo;
}

int bigmod(int a,int p)
{
    int ret=1;
    int coeff = a;
    while(p)
    {
        if(p&1)
            ret=gun(ret,coeff);
        coeff=gun(coeff,coeff);
        p>>=1;
    }
    return ret;
}


int fact[N];
int fact_inv[N];

void init()
{

    fact[0]=1;
    for(int i=1;i<N;i++)
        fact[i]=gun(fact[i-1],i);
    fact_inv[N-1] = bigmod(fact[N-1],oo-2);
    for(int i=N-2;i>=0;i--)
    {
        fact_inv[i]=gun(fact_inv[i+1],i+1);
    }
//    assert(fact_inv[0]==1);
}

auto powPol(auto base,int a,int k)
{
    vector<int> v={1};
    while(a)
    {
        if(a&1)
            v=NTT::multiply(v,base);
        if(v.size()>k) v.resize(k);
        base=NTT::multiply(base,base);
        if(base.size()>k) base.resize(k);
        a>>=1;
    }
    return v;
}

auto gtPol(int suru,int a,int k)
{
    vector<int> base(k,0);
    for(int i=suru;i<k;i+=2)
    {
        base[i] = fact_inv[i];
    }
    return powPol(base,a,k);
}

auto gt(int a,int b,int k)
{
    auto x = gtPol(1,a,k);
    auto y = gtPol(0,b,k);
    auto z = NTT::multiply(x,y);
    z.resize(k,0);
    return z;
}

void TEST_CASES()
{
    int n,m,k,b;
    cin>>n>>m>>k>>b;
    vector<int> ro(n,0);
    vector<int> co(m,0);
    debug(n,m);
    while(b--)
    {
        int x,y;
        cin>>x>>y;
        x--;
        y--;
        ro[x]^=1;
        co[y]^=1;
    }
    debug(1);
//    debug(ro,co);
    int s1 = accumulate(ALL(ro),0);
    auto x = gt(s1,n-s1,k+1);
//    debug(s1,x);
    int s2 = accumulate(ALL(co),0);
    auto y = gt(s2,m-s2,k+1);
    debug(s1,s2);
//    debug(x,y);
    debug(x);
    int ans =0;
    for(int i=0;i<=k;i++)
        ans = add(ans, gun(gun(gun(x[i],y[i]),fact[i]), fact[i]));
    cout<<ans<<"\n";
}




/*
*/

int32_t main()
{
#ifndef APURBA
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#endif
    //freopen("input.txt","r",stdin);
    //freopen("out1.txt","w",stdout);
    init();
    int t=1;
    cin>>t;

    for(int i=1;i<=t;i++)
    {
        cout<<"Case "<<i<<": ";
        TEST_CASES();
    }
    return 0;
}
