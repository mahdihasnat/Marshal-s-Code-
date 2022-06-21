#include<bits/stdc++.h>
using namespace std;
#define MAX 300005
#define MOD 1000000007
typedef long long ll;

ll fact[MAX+1];
ll factinv[MAX+1];
ll gcd(ll a,ll b)
{
    if(b==0) return a;
    else return gcd(b,a%b);
}

ll egcd(ll a,ll b, ll &x,ll &y)
{
    if(a==0)
    {
        x=0;
        y=1;
        return b;
    }
    ll x1,y1;
    ll d = egcd(b%a,a,x1,y1);
    x = y1-(b/a)*x1;
    y=x1;
    return d;
}
ll ModuloInverse(ll a,ll n)
{
    ll x,y;
    x=gcd(a,n);
    a=a/x;
    n=n/x;
    egcd(a,n,x,y);
    x=(x%n+n)%n;
    return x;
}

void init()
{
    fact[0]=factinv[0]=1;
    for(int i=1;i<=MAX;i++)
    {
        fact[i]=(fact[i-1]*i)%MOD;
    }
    factinv[MAX]=ModuloInverse(fact[MAX],MOD);
    for(int i=MAX-1;i>=0;i--)
    {
        factinv[i]=(factinv[i+1]*(i+1))%MOD;
    }
}

ll C(ll n,ll r)
{
    ll ans=fact[n];
    ans=(ans*factinv[n-r])%MOD;
    ans=(ans*factinv[r])%MOD;
    return ans;
}

signed main() {
    init();
    int T;
    scanf("%d",&T);

    for(int t=0;t<T;t++)
    {
        int n,B;
        scanf("%d %d",&n,&B);
        ll ans=0;
        ll last=0;
        for(int i=0;i<n;i++)
        {
            ll temp=0;
            ll num=i+1;
            while(num%B==0)
            {
                num=num/B;
                temp++;
            }
            last=(last+temp);
            ans=(ans+last*C(n-1,i))%MOD;
            //printf("i=%d, last=%lld, ans=%lld\n",i,last,ans);
        }
        printf("Case %d: %lld\n",t+1,ans);
    }
    return 0;

}
