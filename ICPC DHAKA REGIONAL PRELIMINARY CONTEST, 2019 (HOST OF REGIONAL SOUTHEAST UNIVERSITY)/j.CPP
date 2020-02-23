///****In the name of Allah, most Gracious, most Compassionate****//

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair <ll, ll> pii;

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

const ll N=3e5+5;
const ll oo=1e9+7;

int32_t main()
{
    FastIO;
    ll T,cs=0;
    cin>>T;
    while(T--)
    {
        cout<<"Case "<<++cs<<": ";
        ll k;
        cin>>k;
        vector<ll > x;
        while(k--)
        {
            ll y;
            cin>>y;
            x.push_back(y);
        }
        sort(ALL(x));
        cout<<x.front()*x.back()<<"\n";
    }
    return 0;
}

