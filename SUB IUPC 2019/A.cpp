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
//    FastIO;

    int T,cs=0;
    cin>>T;
    while(T--)
    {
        cout<<"Case "<<++cs<<": ";
        int n;
        cin>>n;
        int lo =1;
        int up=n-1;
        int g = __gcd(lo,up);
        lo/=g;
        up/=g;
        cout<<up<<"/"<<lo<<"\n";
    }
}
