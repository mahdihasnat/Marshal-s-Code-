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



typedef pair<int,int> pii;
typedef long long ll;


const int N = 3e5+5;
const int oo=1e9+7;

#define ALL(a) a.begin(),a.end()

int p[N];
int idx[N];
ll sum[N];

int main()
{
    FastIO;
    int T;
    cin>>T;
    while(T--)
    {
        int n,q;
        cin>>n>>q;
        for(int i=1;i<=n;i++)
            cin>>p[i];
        for(int i=1;i<=n;i++)
            idx[p[i]]=i;

        sum[0]=0;
        for(int i=1;i<=n;i++)
        {
            sum[i] = sum[i-1] + n-idx[i]+1;
        }
//        DBG(sum);
//        for(int i=1;i<=n;i++)
//            DBG(sum[i]);
//        NL;
        while(q--){
        ll k;
        cin>>k;
        int i=lower_bound(sum,sum+n+1,k)-sum;
        k-=sum[i-1];
//        DBG(i);
        cout<<idx[i] <<" "<<idx[i] + k-1<<"\n";
        }
    }
}
