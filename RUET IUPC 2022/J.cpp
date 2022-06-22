//21

#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;
#define MAX 100005
#define MOD 998244353
//#define int long long
#define ll long long
int k;
int gcd(int a,int b)
{
    if(b==0) return a;
    else return gcd(b,a%b);
}
int egcd(int a,int b, int &x,int &y)
{
    if(a==0)
    {
        x=0;
        y=1;
        return b;
    }
    int x1,y1;
    int d = egcd(b%a,a,x1,y1);
    x = y1-(b/a)*x1;
    y=x1;
    return d;
}
int ModuloInverse(int a,int n)
{
    int x,y;
    x = __gcd(a, n);
    a=a/x;
    n=n/x;
    egcd(a,n,x,y);
    x=(x%n+n)%n;
    return x;
}

const int mod=998244353;
const int root=15311432;
const int root_1=469870224;
const int root_pw=1<<23;
void fft(vector<int> &a, bool invert)
{
    int n=a.size();
    for(int i=1,j=0; i<n; i++)
    {
        int bit=n>>1;
        for(; j&bit; bit>>=1)
            j^=bit;
        j^=bit;
        if(i<j) swap(a[i],a[j]);
    }
    for(int len=2; len<=n; len<<=1)
    {
        int wlen=invert? root_1:root;
        int len1=len>>1;
        for(int i=len; i<root_pw; i<<=1)
        {
            ll temp=1LL*wlen*wlen;
            if(temp>=mod) wlen=(int) (temp%mod);
            else wlen=(int) (temp);
            //wlen=(int)(1LL*wlen*wlen%mod);
        }
        for(int i=0; i<n; i+=len)
        {
            int w=1;
            for(int j=0; j<len1; j++)
            {
                int u=a[i+j],v=(int) (1LL*a[i+j+len1]*w%mod);
                a[i+j]=u+v<mod? u+v:u+v-mod;
                a[i+j+len1]=u-v>=0? u-v:u-v+mod;
                //w=(int)(1LL*w*wlen%mod);
                ll temp=1LL*w*wlen;
                if(temp>=mod) w=(int) (temp%mod);
                else w=(int) (temp);
            }
        }
    }
    if(invert)
    {
        int n_1=(int) ModuloInverse(n,mod);
        for(int & x: a)
        {
            x=(int)(1LL*x*n_1%mod);
        }
    }
}
vector<int> multiply(vector<int> &a,vector<int> &b)
{
    vector<int> fa(a.begin(),a.end());
    vector<int> fb(b.begin(),b.end());
    int n=1;
    while(n<(int) (a.size()+b.size()))
    {
        n<<=1;
    }
    fa.resize(n);
    fb.resize(n);
    fft(fa,false);
    fft(fb,false);
    for(int i=0; i<n; i++)
    {
        fa[i]=(int) (1LL*fa[i]*fb[i]%mod);
    }
    fft(fa,true);
    n=min(n,k);
    vector<int> result(n);
    for(int i=0; i<n; i++)
    {
        result[i]=fa[i];
    }
    return result;
}
vector<int> counts;
vector<int> div_con(int l,int r)
{
    if(l==r)
    {
        vector<int> ans(2);
        ans[0]=1;
        ans[1]=counts[l];
        return ans;
    }
    int m=(l+r)>>1;
    vector<int> A=div_con(l,m);
    vector<int> B=div_con(m+1,r);
    return multiply(A,B);
}
unordered_map<int,int> mp;
signed main()
{
    int T;
    scanf("%d",&T);
    for(int t=0; t<T; t++)
    {
        int n;
        scanf("%d %d",&n,&k);
        ll ans=1;
        for(int i=0; i<n; i++)
        {
            int v;
            scanf("%d",&v);
            if(!mp[v])
            {
                mp[v]=2;
            }
            else
            {
                int temp=mp[v];
                mp[v]=(temp<<1)%MOD;
            }
            ans=(ans<<1LL)%MOD;
            //printf("%d->%d\n",v,mp[v]);
        }
        for(auto &mit:mp)
        {
            //printf("curr=%d ",mit->second);
            int temp=mit.second-1;
            if(temp<0) temp=temp+MOD;
            counts.push_back(temp);
            //printf("%d ",counts.back());
        }

        mp.clear();
        printf("Case %d: ",t+1);

        if((int) (counts.size())<k)
        {
            printf("0");
        }
        else
        {
            //printf("Entered else\n");
            int mm=counts.size();
            vector<int> Ans=div_con(0,mm-1);
            int sz = Ans.size();
            sz = min(sz, k);
            for(int i=0; i < sz; i++)
            {
                ans = (ans - Ans[i]);
                if(ans < 0) ans += MOD;
                //ans=(ans+MOD-Ans[i])%MOD;
            }
            printf("%lld",ans);
        }
        counts.clear();
        printf("\n");
    }
    return 0;
}
