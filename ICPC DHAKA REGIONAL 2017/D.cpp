
#include<bits/stdc++.h>
using namespace std;
#define MAX 300005
int k;
vector<int> Graph[MAX];
int sz[MAX];
bool comp(int a,int b)
{
    return sz[a]>sz[b];
}
int dfs(int node, int p=-1)
{
    int idx=-1;
    for(int i=0;i<Graph[node].size();i++)
    {
        if(Graph[node][i]==p)
        {
            idx=i;
            continue;
        }
        dfs(Graph[node][i],node);
    }
    if(idx!=-1)
    {
        swap(Graph[node].back(),Graph[node][idx]);
        Graph[node].pop_back();
    }

    sort(Graph[node].begin(),Graph[node].end(),comp);
    sz[node]=1;
    if(Graph[node].empty()) return sz[node];
    else if(Graph[node].size()<k)
    {
        sz[node]=1;
        return sz[node];
    }
    for(int i=0;i<k;i++)
    {
        sz[node]=sz[node]+sz[Graph[node][i]];
    }
    return sz[node];
}
int main()
{
    int T;
    scanf("%d",&T);
    for(int t=0;t<T;t++)
    {
        int n;
        scanf("%d %d",&n,&k);
        for(int i=1;i<n;i++)
        {
            int u,v;
            scanf("%d %d",&u,&v);
            Graph[u].push_back(v);
            Graph[v].push_back(u);
        }
        int ans=dfs(1);
        for(int i=1;i<=n;i++)
        {
            //printf("ans(%d)=%d\n",i,sz[i]);
            //ans=max(ans,sz[i]);
            Graph[i].clear();
            sz[i]=0;
        }
        printf("Case %d: %d",t+1,ans);
        printf("\n");
    }
    return 0;
}
