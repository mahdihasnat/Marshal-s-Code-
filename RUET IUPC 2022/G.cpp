//21
#include<bits/stdc++.h>
using namespace std;
#define dbg(x) cerr << "LINE : "<<__LINE__ <<" "<< #x <<" -> "<<(x)<<endl;

#define DBG(x) dbg(x)
typedef long long ll;

const int N=1e5+5;
const int K=21;
const int oo = 1e9+7;

int p[N][K];
int dep[N];

int kth(int u,int k)
{
    for(int i=K-1;i>=0;i--)
    {
        if((k>>i)&1)
        {
            u=p[u][i];
        }
    }
    return u;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int T,cs=0;
    cin>>T;
    while(T--)
    {
        cout<<"Case "<<++cs<<":"<<"\n";
        int n;
        cin>>n;
        map<string ,int> idx;
        idx["Main"] = 0;
        int cnt =1;
        while(n--)
        {
            char typ;
            cin>>typ;
            string a,b,c,d,e;
            if(typ=='+')
            {
                cin>>a>>b>>c>>d;
                assert(idx.find(b) == idx.end());
                assert(idx.find(d) != idx.end());

                idx[b] = cnt;
                p[cnt][0] = idx[d];
                dep[cnt] = dep[idx[d]]+1;
                for(int i=1;i<K;i++)
                    p[cnt][i]=p[p[cnt][i-1]][i-1];
                cnt++;
            }
            else
            {
                cin>>a>>b>>c>>d>>e;
                bool ans = 0;
                if(idx.find(a)!=idx.end())
                {
                    int x = idx[a];
                    e.pop_back();
                    e.pop_back();
//                    DBG(e);
                    if(idx.find(e) != idx.end())
                    {
                        int y = idx[e];
                        if(dep[y] >= dep[x])
                        {
                            ans =( kth(y, dep[y]-dep[x]) == x);
                        }
                    }
                }
                cout<<(ans?"yes\n":"no\n");

            }
        }
    }
}
