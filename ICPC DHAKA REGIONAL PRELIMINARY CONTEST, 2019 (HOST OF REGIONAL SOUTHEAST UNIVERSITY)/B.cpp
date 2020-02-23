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

const int N=1e5+10;
const int oo=1e9+7;


#include <ext/pb_ds/assoc_container.hpp> // Common file

using namespace std;
using namespace __gnu_pbds;

/* Special functions:

        find_by_order(k) --> returns iterator to the kth largest element counting from 0
        order_of_key(val) --> returns the number of items in a set that are strictly smaller than our item
*/

typedef tree<
pii,
null_type,
less<pii>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;


ordered_set st[N];
int id[N];

int parent[N];
int rnk[N];
int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

void make_set(int v) {
    parent[v] = v;
    rnk[v] = 0;
    st[v].clear();
    id[v]=v;
}
void marg(ordered_set & a, ordered_set &b)
{
    for(auto i: b)
        a.insert(i);
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (rnk[a] < rnk[b])
            swap(a, b);
        parent[b] = a;
        int x =-1;
        if(st[id[a]].size()>=st[id[b]].size())
        {
            marg(st[id[a]] , st[id[b]]);
            x= id[a];
        }
        else
        {
            marg(st[id[b]] , st[id[a]]);
            x =id[b];
        }
        id[a]=x;

        if (rnk[a] == rnk[b])
            rnk[a]++;
    }
}
int ans(int u,int l,int r)
{
     u= find_set(u);
     return st[id[u]].order_of_key(make_pair(r,oo))  - st[id[u]].order_of_key(make_pair(l,0));
}


int32_t main()
{
    int T,cs=0;
    scanf("%d",&T);
    while(T--)
    {
        printf("Case %d:\n",++cs);
        unordered_map<int , int > cnt;
        int n,q;
        scanf("%d %d",&n,&q);
        for(int i=1;i<=n;i++) make_set(i);
        while(q--)
        {
            int cmd , u,v;
            scanf("%d %d %d",&cmd,&u , &v);
            if(cmd==0)
            {
                union_sets(u,v);
            }
            else if(cmd==1)
            {
                st[id[find_set(u)]].insert({v  , cnt[v]++ });
            }
            else
            {
                int l ,r;
                l = v;
                scanf("%d",&r);
                printf("%d\n",ans(u,l,r));
            }
        }
    }
}

