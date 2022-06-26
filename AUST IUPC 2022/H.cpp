///****In the name of ALLAH, most Gracious, most Compassionate****//

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair <int, int> pii;

#define ALL(a) a.begin(), a.end()
#define FastIO ios::sync_with_stdio(false); cin.tie(0);cout.tie(0)
#define IN freopen("input.txt","r+",stdin)
#define OUT freopen("output.txt","w+",stdout)

#define DBG(a) cerr<< "line "<<__LINE__ <<" : "<< #a <<" --> "<<(a)<<endl
#define NL cout<<endl

template < class T1,class T2>
ostream &operator <<(ostream &os,const pair < T1,T2 > &p)
{
    os<<"{"<<p.first<<","<<p.second<<"}";
    return os;
}

const int N=2e5+5;
const int oo=1e9+7;

namespace DSU{
int parent[N];
int rnk[N];
int find_set(int v)
{
    return parent[v] == v ? v :  parent[v] = find_set(parent[v]);
}

void make_set(int v)
{
    parent[v] = v;
    rnk[v] = 0;
}

bool union_sets(int a, int b)
{
    a = find_set(a);
    b = find_set(b);
    if (a != b)
    {
        if (rnk[a] < rnk[b])
            swap(a, b);
        parent[b] = a;
        if (rnk[a] == rnk[b])
            rnk[a]++;
				return 0;
    }
		return 1;
}
}

vector<int > g[N];
int cur_pos;
int  parent[N];
int depth[N];
int heavy[N];
int pos[N];
int head[N];

int dfs(int v) {
	// DBG(v);
    int size = 1;
    int max_c_size = 0;
    for (int c : g[v]) {
        if (c != parent[v]) {
            parent[c] = v, depth[c] = depth[v] + 1;
            int c_size = dfs(c);
            size += c_size;
            if (c_size > max_c_size)
                max_c_size = c_size, heavy[v] = c;
				}
		}
    return size;
}
void decompose(int v,int h){
    head[v] = h, pos[v] = cur_pos++;
    if (heavy[v] != -1)
        decompose(heavy[v], h);
    for (int c :g[v]) {
        if (c != parent[v] && c != heavy[v])
            decompose(c, c);
		}
}


int sum[N<<2];
int lazy[N<<2];

int x,y;

void prop(int u,int l,int r)
{
	if(lazy[u])
		sum[u]=0;
	if(l!=r)
		lazy[u<<1]|=lazy[u],
		lazy[u<<1|1]|=lazy[u];
	lazy[u]=0;
}

int gt(int u,int l,int r)
{
	prop(u,l,r);
	// if(lazy[u])
	// 	return 0;
	if(y < l or r < x)
		return 0;
	if(x<=l and r <= y)
		return sum[u];
	int mid = (l+r)>>1;
	return 
		gt(u<<1,l,mid)+
		gt(u<<1|1,mid+1,r);
}

void upd(int u,int l,int r)
{
	prop(u,l,r);
	// if(lazy[u])
	// 	return ;
	if(y < l or r < x)
		return ;
	if(x<=l and r <= y)
		{
			lazy[u]=1;
			return prop(u,l,r);
		}
	int mid = (l+r)>>1;
		upd(u<<1,l,mid);
		upd(u<<1|1,mid+1,r);
	sum[u]=sum[u<<1]+sum[u<<1|1];
}
void build(int u,int l,int r)
{
	if(l==r)
	{
		sum[u]=1;
		lazy[u]=0;
	}
	else 
	{
		int mid = (l+r)>>1;
		build(u<<1,l,mid);
		build(u<<1|1,mid+1,r);
		sum[u]=sum[u<<1]+sum[u<<1|1];
		lazy[u]=0;
	}
}

int segment_tree_query(int a,int b)
{
	x=a;
	y=b;
	// DBG(gt);
	// DBG(x);
	// DBG(y);
	// DBG(gt(1,1,cur_pos));
	// NL;
	
	return gt(1,1,cur_pos);
}
void segment_tree_update(int a,int b)
{
	x=a;
	y=b;
	// DBG(upd);
	// DBG(x);
	// DBG(y);
	// NL;
	upd(1,1,cur_pos);
}



void init(int n) {
    for(int i=0;i<=n;i++)
			heavy[i]=-1 ;
    cur_pos = 1;
		// DBG(dfs);
		depth[1]=1;
    dfs(1);
		// DBG(decompose);
    decompose(1,1);
		build(1,1,cur_pos);
		// DBG(gt(1,1,cur_pos));
		// DBG(parent);
		// for(int i=1;i<=n;i++)
		// 	cout<<parent[i]<<" ";
		// 	NL;
		
}



int query(int a, int b) {
	int res = 0;
	for (; head[a] != head[b]; b = parent[head[b]]) {
			if (depth[head[a]] > depth[head[b]])
					swap(a, b);
			res+=segment_tree_query(pos[head[b]]+1, pos[b]);
	}
	if (depth[a] > depth[b])
			swap(a, b);
		if(a!=b)
	
		res+=segment_tree_query(pos[a]+1, pos[b]);
	
	return res;
}

void update(int a, int b) {
	
	for (; head[a] != head[b]; b = parent[head[b]]) {
			if (depth[head[a]] > depth[head[b]])
					swap(a, b);
			segment_tree_update(pos[head[b]]+1, pos[b]);
	}
	if (depth[a] > depth[b])
			swap(a, b);
		if(a!=b)
	
	segment_tree_update(pos[a]+1, pos[b]);
	
}

struct Q
{
	int i,u,v;
};
Q qu[N];

struct E
{
	int i,u,v,p;
};
E edgs[N+N];

int32_t main()
{
    
    int T,cs=0;
    scanf("%d",&T);
    while(T--)
    {
        printf("Case %d:\n",++cs);
				int n,m,q;
				int ei=0;
				scanf("%d %d",&n,&m);
				for(int i=1;i<=n;i++)
					DSU::make_set(i);
				
				while(m--)
				{
					int u,v;
					scanf("%d %d",&u,&v);
					if(u==v) continue;
					if(DSU::union_sets(u,v))
					{
						edgs[ei++]={0,u,v,1};
					}
					else 
					{
						g[u].push_back(v);
						g[v].push_back(u);
						edgs[ei++]={0,u,v,0};
					}
				}
				int qi=0;
				scanf("%d",&q);
				
				for(int i=1;i<=q;i++)
				{
					int t,u,v;
					scanf("%d %d %d",&t,&u,&v);
					if(t==1)
					{
						if(u==v)
							continue;
						if(DSU::union_sets(u,v))
						{
							edgs[ei++]={i,u,v,1};
						}
						else 
						{
							g[u].push_back(v);
							g[v].push_back(u);
							edgs[ei++]= {i,u,v,0};
						}
					}
					else 
					{
						qu[qi++]={i,u,v};
					}
				}
				for(int i=2;i<=n;i++)
				{
					if(DSU::find_set(i) != DSU::find_set(1) and DSU::find_set(i)==i)
					{
						g[i].push_back(1);
						g[1].push_back(i);
					}
				}
				// DBG(&g);
				// for(int i=1;i<=n;i++)
				// {
				// 	DBG(i);
				// 	for(int j:  g[i])
				// 		cout<<j<<" ";
				// 	NL;
				// }


				init(n);



				for(int i=1;i<=n;i++) DSU::make_set(i);

				int now = 0;
				for(int x=0;x<qi;x++)
				{
					int i,u,v;
					i=qu[x].i;
					u=qu[x].u;
					v=qu[x].v;
					while(now < ei and edgs[now].i < i)
					{
						int ii,u,v,t;
						u=edgs[now].u;
						v=edgs[now].v;
						t=edgs[now].p;
						now++;
						if(t==0)
						{
							DSU::union_sets(u,v);
						}
						else 
						{
							update(u,v);
						}
					}
					int ans = 0;
					if(u!=v)
						ans = DSU::find_set(u) == DSU::find_set(v)? query(u,v): -1;
					printf("%d\n",ans);
				}
				for(int i=1;i<=n;i++)
					g[i].clear();
				// edgs.clear();

    }
}