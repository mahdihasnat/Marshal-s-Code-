///****In the name of ALLAH, most Gracious, most Compassionate****//

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair <int, int> pii;

#define ALL(a) a.begin(), a.end()
#define FastIO ios::sync_with_stdio(false); cin.tie(0);cout.tie(0)
#define IN freopen("input.txt","r+",stdin)
#define OUT freopen("output.txt","w+",stdout)

#define DBG(a) cerr<< "line "<<__LINE__ <<" : "<< #a <<" --> "<<(a)<<endl
#define NL cerr<<endl

template < class T1,class T2>
ostream &operator <<(ostream &os,const pair < T1,T2 > &p)
{
    os<<"{"<<p.first<<","<<p.second<<"}";
    return os;
}

const int N=1e5+5;
const int oo=1e9+7;

const int maxn = 1e5+5;
int wa[maxn],wb[maxn],wv[maxn],wc[maxn];
int r[maxn],sa[maxn],rak[maxn], height[maxn],dp[maxn][22],jump[maxn], SIGMA = 0 ;

int cmp(int *r,int a,int b,int l){return r[a] == r[b] && r[a+l] == r[b+l];}
void da(int *r,int *sa,int n,int m)
{
    int i,j,p,*x=wa,*y=wb,*t;
    for( i=0;i<m;i++) wc[i]=0;
    for( i=0;i<n;i++) wc[x[i]=r[i]] ++;
    for( i=1;i<m;i++) wc[i] += wc[i-1];
    for( i= n-1;i>=0;i--)sa[--wc[x[i]]] = i;
    for( j= 1,p=1;p<n;j*=2,m=p){
        for(p=0,i=n-j;i<n;i++)y[p++] = i;
        for(i=0;i<n;i++)if(sa[i] >= j) y[p++] = sa[i] - j;
        for(i=0;i<n;i++)wv[i] = x[y[i]];
        for(i=0;i<m;i++) wc[i] = 0;
        for(i=0;i<n;i++) wc[wv[i]] ++;
        for(i=1;i<m;i++) wc[i] += wc[i-1];
        for(i=n-1;i>=0;i--) sa[--wc[wv[i]]] = y[i];
        for(t=x,x=y,y=t,p=1,x[sa[0]] = 0,i=1;i<n;i++) x[sa[i]]= cmp(y,sa[i-1],sa[i],j) ? p-1:p++;
    }
}
void calheight(int *r,int *sa,int n)
{
    int i,j,k=0;
    for(i=1;i<=n;i++) rak[sa[i]] = i;
    for(i=0;i<n;height[rak[i++]] = k ) {
        for(k?k--:0, j=sa[rak[i]-1] ; r[i+k] == r[j+k] ; k ++) ;
    }
}

void initRMQ(int n)
{
    for(int i= 0;i<=n;i++) dp[i][0] = height[i];
    for(int j= 1; (1<<j) <= n; j ++ ){
        for(int i = 0; i + (1<<j) - 1 <= n ; i ++ ) {
            dp[i][j] = min(dp[i][j-1] , dp[i + (1<<(j-1))][j-1]);
        }
    }
    for(int i = 1;i <= n;i ++ ) {
        int k = 0;
        while((1 << (k+1)) <= i) k++;
        jump[i] = k;
    }

}
int askRMQ(int L,int R)
{
    int k = jump[R-L+1];
    return min(dp[L][k], dp[R - (1<<k) + 1][k]);
}


// int main()
// {
//     scanf("%s",s);
//     int n = strlen(s);
//     for(int i = 0; i < n; i ++) {
//         r[i] = s[i]-'a' + 1;
//         SIGMA = max(SIGMA, r[i]);
//     }
//     r[n] = 0;
//     da(r,sa,n+1,SIGMA + 1); // don't forget SIGMA + 1. It will ruin you.
//     calheight(r,sa,n);
// }

const int K = 23 ; /// k >= ceil(lg22(n)) +1
int lg2[N+1];
void ini()
{
    lg2[1] = 0;
    for (int i = 2; i <= N; i++)
        lg2[i] = lg2[i/2] + 1;
}

namespace SA
{
int st[N][K + 1];
int f(int i,int j)
{
    // if(arr[i]==arr[j]) return i<j ? j: i;
    // return arr[i]<arr[j] ? i: j;
	return min(i,j);
}

void pre( int n)
{

    for (int i = 0; i < n; i++)
        st[i][0] = sa[i];

    for (int j = 1; j <= K; j++)
        for (int i = 0; i + (1 << j) <= n; i++)
            st[i][j] = f( st[i][j-1], st[i + (1 << (j - 1))][j - 1]);
}
int getf( int L,int R)
{
    if(L>R) swap(L,R);
    int j = lg2[R - L + 1];
    return  f(st[L][j], st[R - (1 << j) + 1][j]);
}

}
namespace LCP
{

int st[N][K + 1];
int f(int i,int j)
{
    // if(arr[i]==arr[j]) return i<j ? j: i;
    // return arr[i]<arr[j] ? i: j;
	return min(i,j);
}

void pre( int n)
{

    for (int i = 0; i < n; i++)
        st[i][0] = height[i];

    for (int j = 1; j <= K; j++)
        for (int i = 0; i + (1 << j) <= n; i++)
            st[i][j] = f( st[i][j-1], st[i + (1 << (j - 1))][j - 1]);
}
int getf( int L,int R)
{
    if(L>R) swap(L,R);
    int j = lg2[R - L + 1];
    return  f(st[L][j], st[R - (1 << j) + 1][j]);
}

}

pii value[4*N];
int lazy[4*N];

pii func(pii x,pii y)
{
    return min(x,y);
}

pii UpdateRange(int u , int ss, int se, int us,int ue, int diff)
{
    int mid = ss+(se-ss)/2;

    if (ss>se || ss>ue || se<us)
        return {oo,oo};

    if (ss>=us && se<=ue)
    {
        lazy[u] += diff;
		value[u].first+=diff;
        return value[u];
    }


    UpdateRange(u<<1, ss, mid, us, ue, diff);
    UpdateRange(u<<1|1, mid+1, se, us, ue, diff);

    value[u]=func(value[u<<1],value[u<<1|1]);
	value[u].first+=lazy[u];
	return value[u];
}

vector< pii > qu[N];
int ans[N];

void Build(int u,int ss,int se)
{
    lazy[u]=0;
    if(ss==se)
    {
        value[u]={qu[ss].back().first,ss};
        return ;
    }
    int mid = ss+(se-ss)/2;
    Build(u<<1,ss,mid);
    Build(u<<1|1,mid+1,se);
    value[u]=func(value[u<<1],value[u<<1|1]);
}

int firstChoto(int l,int r,int x)
{
	int m ;
	int L = l;
	if(LCP::getf(l,r)>=x)
		return r+1;
	while(l<r)
	{
		m = (l+r)/2;
		if(LCP::getf(L,m)<x)
		{
			r=m;
		}
		else l=m+1;
	}
	return r;
}

int32_t main()
{
	ini();
    int T,cs=0;
	cin>>T;
    while(T--)
    {
		string s;
		cin>>s;
		int n=s.size();
		for(int i=0;i<n;i++)
			r[i]=s[i]-'a'+1,SIGMA=max(SIGMA,r[i]);
		r[n]=0;
		da(r,sa,n+1,SIGMA+1);
		calheight(r,sa,n);
		// DBG(sa);
		// for(int i=0;i<=n;i++)
		// 	cerr<<sa[i]<<" ";
		// NL;
		// DBG(height);
		// for(int i=0;i<=n;i++)
		// 	cerr<<height[i]<<" ";
		// NL;

		int q;
		cin>>q;
		for(int i=1;i<=q;i++)
		{
			int k,m;
			cin>>k>>m;
			qu[k].push_back({m,i});
			ans[i]=-1;
		}
		for(int i=1;i<=n;i++)
		{
			qu[i].push_back({oo,oo});
			sort(ALL(qu[i]));
			reverse(ALL(qu[i]));
		}
		Build(1,1,n);
		// DBG(UpdateRange(1,1,n,1,n,-1));
		// DBG(UpdateRange(1,1,n,1,n,-1));

		
		SA::pre(n+1);
		
		LCP::pre(n+1);

		for(int i=1;i<=n;i++)
		{
			int l = height[i]+1;
			int r = n-sa[i];
			pii x = UpdateRange(1,1,n,l,r,-1);
			if(x.first == 0)
			{
				do
				{
					int len = x.second;
					int ansi = qu[len].back().second;
					int oldSz = qu[len].back().first;
					qu[len].pop_back();

					int nxtChoto = firstChoto(i+1,n,len);
					ans[ansi] = SA::getf(i,nxtChoto-1);
					
					UpdateRange(1,1,n,len,len,qu[len].back().first-oldSz);

					x = UpdateRange(1,1,n,l,r,0);
				}
				while(x.first == 0);	
			}
		}
		for(int i=1;i<=q;i++)
		{
			if(ans[i]==-1)
				cout<<"Not found\n";
			else cout<<ans[i]<<"\n";
		}
    }
}
