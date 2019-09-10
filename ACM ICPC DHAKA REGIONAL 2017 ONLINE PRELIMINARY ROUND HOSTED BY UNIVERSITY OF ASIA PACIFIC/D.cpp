///****In the name of Allah, most Gracious, most Compassionate****//

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

const int N=4e4+5;
const int oo=1e9+7;


int parent[N];
int rnk[N];
int size[N];
int find_set(int v)
{
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

void make_set(int v)
{
    parent[v] = v;
    rnk[v] = 0;
    size[v]=1;
}

void union_sets(int a, int b)
{
    a = find_set(a);
    b = find_set(b);
    if (a != b)
    {
        if (rnk[a] < rnk[b])
            swap(a, b);
        size[a]+=size[b];
        parent[b] = a;
        if (rnk[a] == rnk[b])
            rnk[a]++;
    }
}


int ans[100005];
pii c[100005];
int32_t main()
{
    FastIO;
    int T,cs=0;
    cin>>T;
    while(T--)
    {
        int n,m;
        cin>>n>>m;
        vector< pair< int, pii > > in(m);
        for(int i=0; i<m; i++)
        {
            cin>>in[i].second.first>>in[i].second.second>>in[i].first;
            in[i].first = -in[i].first;
        }
        sort(ALL(in));
        for(int i=1; i<=n; i++)
            make_set(i);
        int q;
        cin>>q;
        for(int i=0; i<q; i++)
        {
            cin>>c[i].first;
            c[i].second=i;
            c[i].first =- c[i].first;
        }
        sort(c,c+q);
        int i=0;
        for(int j=0; j<q; j++)
        {
            c[j].first  = -c[j].first ;

            while(i<m and -in[i].first >= c[j].first )
            {
                union_sets(in[i].second.first, in[i].second.second);
                i++;
            }
            ans[c[j].second] = size[find_set(1)];
        }
        cout<<"Case "<<++cs<<":\n";
        for(int i=0; i<q; i++)
            cout<<ans[i]-1<<"\n";

    }
}
