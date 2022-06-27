///****In the name of ALLAH, most Gracious, most Compassionate****//

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair <int, int> pii;

#define ALL(a) a.begin(), a.end()
#define FastIO ios::sync_with_stdio(false); cin.tie(0);cout.tie(0)
#define IN freopen("input.txt","r+",stdin)
#define OUT freopen("output.txt","w+",stdout)

#define DBG(a) cerr<< "line "<<__LINE__ <<" : "<< #a <<" --> "<<(a)<<endl
#define NL cout<<endl

template < class T1,class T2>
ostream &operator <<(ostream &os,const pair < T1,T2 > &p)
{
    os<<"{"<<p.first<<","<<p.second<<"}";
    return os;
}

const int N=1e6+5;
const ll oo=998244353;

long long bigmod ( long long a, long long p, long long m )
{
    long long res = 1;
    long long x = a;

    while ( p )
    {
        if ( p & 1 ) //p is odd
        {
            res = ( res * x ) % m;
        }
        x = ( x * x ) % m;
        p = p >> 1;
    }

    return res;
}


ll fact[N];
ll fact_inv[N];

ll qmul[N];

int32_t main()
{
    FastIO;
	fact[0]=1;
	for(ll i=1;i<N;i++)
	{
		fact[i]=(i*fact[i-1])%oo;
	}
	fact_inv[N-1] = bigmod(fact[N-1] , oo-2,oo);
	for(ll i=N-2;i>=0;i--)
	{
		fact_inv[i]=(i+1)*fact_inv[i+1]%oo;
	}
	qmul[0]=1;
	ll cur = 1;
	for(ll i=1;i<N;i++)
	{
		qmul[i]= qmul[i-1] * cur %oo;
		cur = ((cur *2 )+1)%oo;
	}

    int T,cs=0;
    cin>>T;
    while(T--)
    {
				ll n,k;
				cin>>n>>k;
				ll ans = 0;
				if(n<=k)
				{
					ans = qmul[k] * bigmod(qmul[k-n],oo-2,oo)%oo;
					ans = ans * bigmod(2,(n)*(n-1)/2 % (oo-1), oo) %oo;
					ans = ans * fact_inv[n] %oo;
				}
				cout<<ans<<"\n";

    }
}