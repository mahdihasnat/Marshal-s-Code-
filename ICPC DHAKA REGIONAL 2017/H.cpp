#include<bits/stdc++.h>
using namespace std;
vector<pair<int,bool> > V;
int main()
{
    int n;
    while(scanf("%d",&n)!=EOF)
    {
        if(n==0) return 0;
        for(int i=0;i<n;i++)
        {
            pair<int,int> p;
            scanf("%d %d",&p.first,&p.second);
            V.push_back(make_pair((p.first-p.second),false));
            V.push_back(make_pair((p.first+p.second),true));
        }
        sort(V.begin(),V.end());

        int curr=0;
        int ans=0;
        for(int i=0;i<(int) V.size();i++)
        {
            //printf("%d %d\n",V[i].first,V[i].second);
            if(V[i].second) curr--;
            else curr++;
            ans=max(ans,curr);
        }
        V.clear();
        printf("%d\n",ans);
    }
    return 0;
}
