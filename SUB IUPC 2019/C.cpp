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

const int N=3e5+5;
const int oo=1e9+7;

int32_t main()
{
    FastIO;

    int T,cs=0;
    cin>>T;
    while(T--)
    {
        cout<<"Case "<<++cs<<": ";
        int d,m,c,r;
        cin>>d>>m>>c>>r;
        int p;
        cin>>p;
        int flg =1;
        while(p--)
        {
            int a,b,cc;
            cin>>a>>b>>cc;
            if(a==d and b==m and c==cc and r==0 )
                flg=0;
            else if(a==d and b==m and c!=cc)
                flg=0;
        }
        cout<<(flg ? "Yes\n":"No\n");
    }
}
