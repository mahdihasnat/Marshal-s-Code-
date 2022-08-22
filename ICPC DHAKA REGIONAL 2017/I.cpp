#include<bits/stdc++.h>
using namespace std;
#define MOD 100000007
const int N = 5000005;
vector<int> lp(N+1);
vector<int> pr;

void sieve()
{
    for (int i=2; i <= N; ++i)
    {
        if (lp[i] == 0)
        {
            lp[i] = i;
            pr.push_back(i);
        }
        for (int j=0; j < (int)pr.size() && pr[j] <= lp[i] && i*pr[j] <= N; ++j)
        {
            lp[i * pr[j]] = pr[j];
        }
    }
}

long long cnt(int n,int p)
{
    long long k=(n+1)/p;
    long long ans=k*(k-1)/2;
    ans=(ans*p)%MOD;
    long long r=(n+1)%p;
    ans=(ans+r*k)%MOD;
    return ans;
}

int main()
{
    sieve();
    int n;
    while(scanf("%d",&n) != EOF)
    {
        long long ans = 1;
        if(n==0) return 0;
        for(int i = 0;i < (int) pr.size() && pr[i]<=n; i++)
        {
            int p = pr[i];
            long long cur_cnt=0;
            for(long long j=p;j<=n;j=j*p)
            {
                long long cc=cnt(n,(int)j);
                cur_cnt=(cur_cnt+cc)%MOD;
            }
            ans=(ans*(cur_cnt+1))%MOD;
        }
        printf("%lld\n",ans);
    }
    return 0;
}
