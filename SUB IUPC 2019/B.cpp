#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair <int, int> pii;

#define NL cout<<"\n";
#define ALL(a) a.begin(), a.end()
#define DBG(a) cout<< #a <<" --> "<<(a)<<endl;
#define FastIO ios::sync_with_stdio(false); cin.tie(0);cout.tie(0)
#define IN freopen("input.txt","r+",stdin)
#define OUT freopen("output.txt","w+",stdout)

template < class T1,class T2>
ostream &operator <<(ostream &os,const pair < T1,T2 > &p)
{
    os<<"{"<<p.first<<","<<p.second<<"}";
    return os;
}

const int N=1e6+5;
const ll oo=1e9+7;
vector<pii > divisor[N];
int a[N];
vector<int > start[N],stop[N];
int powercnt[N][25];
int nowpower[N];

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


void add(ll &now,int prime,int power)
{
    now = now* bigmod(prime,power,oo) % oo;
    if(now<0) now+=oo;
}
void remove(ll &now,int prime,int power)
{
    now = now *bigmod( bigmod(prime,power,oo) , oo-2 ,oo) % oo;
    if(now<0) now+=oo;
}

int32_t main()
{
    FastIO;
    for(int i=2;i<N;i++)
    {
        if(divisor[i].size()==0)
        {
            for(int j=i;j<N;j+=i) {

                int p=0;
                int  x= j;
                while(x%i==0)
                    x/=i,p++;
                divisor[j].push_back({i,p});
            }
        }
        powercnt[i][0]=1;
    }

    int T,cs=0;
    cin>>T;
    while(T--)
    {
        cout<<"Case "<<++cs<<":";
        int n,q;
        cin>>n>>q;
        while(q--)
        {
            int l,r,x;
            cin>>l>>r>>x;
            start[l].push_back(x);
            stop[r].push_back(x);
        }
        ll now=1;
        for(int i=1;i<=n;i++){

            for(int x: start[i])
            {
//                DBG(x);
                for(pii y: divisor[x])
                {
//                    DBG(y);
                    int old =nowpower[y.first];
                    powercnt[y.first][y.second]++;
                    nowpower[y.first]= max(nowpower[y.first], y.second);

                    add(now,y.first,nowpower[y.first]-old);
                }
            }

            a[i]=now;


            for(int x: stop[i])
            {
                for(pii y: divisor[x])
                {
                    int old =nowpower[y.first];
                    powercnt[y.first][y.second]--;
                    while(powercnt[y.first][nowpower[y.first]]==0)
                        nowpower[y.first]--;
                    remove(now,y.first,-nowpower[y.first]+old);
                }
            }
        }
        for(int i=1;i<=n;i++)
            cout<<" "<<a[i];
        NL;
        for(int i=1;i<=n;i++)
            start[i].erase(ALL(start[i])), stop[i].erase(ALL(stop[i]));
    }
}
