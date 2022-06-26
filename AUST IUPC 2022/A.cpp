#include<bits/stdc++.h>
using namespace std;
#define DBG(x) cerr <<__LINE__<<": "<< #x <<" -> "<<(x) <<"\n";
#define NL cerr <<"\n";
#define FastIO ios_base::sync_with_stdio(0); cin.tie(0);

#define xx first
#define yy second

#include<ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;


#define ALL(a) a.begin(),a.end()

typedef pair<int,int> pii;
typedef long long ll;


const int N = 3e5+5;
const int oo=1e9+7;


int main()
{
    FastIO;
    int T,cs=0;
    cin>>T;
    while(T--)
    {
        ll n,k,m;
        cin>>n>>k>>m;
            ll ans =0;
        if(n<=4)
        {
            vector<int> a(n);
            for(int i=0;i<n;i++)
                a[i]=i+1;
            k--;
            while(k--)
                next_permutation(ALL(a));
            int last = n-1;
            while(m--)
                ans+=a[last--];
        }
        else if(m<=4)
        {
            vector<int> a(4);
            for(int i=0;i<4;i++)
                a[i]=n-3+i;
            k--;
            while(k--)
                next_permutation(ALL(a));
            int last = 4-1;
            while(m--)
                ans+=a[last--];
        }
        else
        {
            ans = n*(n+1)/2 - (n-m)*(n-m+1)/2;
        }
        cout<<"Case "<<++cs<<": "<<ans<<"\n";
    }
}
