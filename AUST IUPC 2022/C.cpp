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

vector<pii> Graph[N];

long long check(int node,int n)
{
    sort(Graph[node].begin(),Graph[node].end());
    int lo=1;
    if(node==lo) lo++;
    long long ans=0,inf=1000000000000000000;
    for(int i=0;i<Graph[node].size();i++)
    {
        if(Graph[node][i].first>lo) return inf;
        if(Graph[node][i].first<lo) continue;
        ans=ans+Graph[node][i].second;
        lo++;
        if(node==lo) lo++;
    }
    if(lo<=n) return inf;
    return ans;
}
int main()
{
    FastIO;
    int T;
    cin>>T;
    for(int t=1;t<=T;t++)
    {
        int n,m;
        cin>>n>>m;
        for(int i=0;i<m;i++)
        {
            int u,v,w;
            cin>>u>>v>>w;
            Graph[u].push_back(make_pair(v,w));
            Graph[v].push_back(make_pair(u,w));
        }
        long long ans=1000000000000000000;
        for(int i=1;i<=n;i++)
        {
            ans=min(ans,check(i,n));
        }
        cout<<"Case "<<t<<": ";

        if(ans>=1000000000000000000) cout<<"Impossible";
        else cout<<ans;
        cout<<endl;
        for(int i=1;i<=n;i++)
        {
            Graph[i].clear();
        }
    }
}
