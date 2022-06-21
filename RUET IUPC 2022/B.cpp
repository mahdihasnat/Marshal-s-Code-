#include<bits/stdc++.h>
using namespace std;
#define dbg(x) cerr << "LINE : "<<__LINE__ <<" "<< #x <<" -> "<<(x)<<endl;

#define DBG(x) dbg(x)
typedef unsigned long long ll;

const int N=1e5+5;
const int oo = 1e9+7;
typedef unsigned long long ull;

int tot[N];
vector<int> lft[N];
ull ans[N];
ull qsum[N];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int T,cs=0;
    cin>>T;
    while(T--)
    {
        cout<<"Case "<<++cs<<":"<<"\n";
        int n,m;
        cin>>n>>m;
        memset(qsum,0,sizeof qsum);
        memset(tot,0,sizeof tot);
        bool ok = 1;
        while(m--)
        {
            int l,r;
            cin>>l>>r;
            if(r-l+1 > 64)
                ok=0;
            tot[l]++;
            if(ok)
            lft[r].push_back(l);
        }
        if(ok){
            multiset<int> st;
            for(int i=1;i<=n;i++)
            {
                while(tot[i]--)
                    st.insert(i);
                ull x = 0;
//                DBG(bitset<64> (x));
                for(int j: st)
                {
//                    DBG(qsum[i-1] ^ qsum[j-1]);
                    x |= (qsum[i-1] ^ qsum[j-1]);
                }
                for(ll j=0;j<=63;j++)
                    if(!((x>>j)&1LLU)){
                            ans[i] = 1LLU<<j;break;
                    }
                qsum[i]=qsum[i-1]^ans[i];
                for(int j: lft[i])
                    st.erase(st.find(j));
            }
            cout<<ans[1];
            for(int i=2;i<=n;i++)
                cout<<" "<<ans[i];
            cout<<"\n";
        }
        else
            cout<<"Impossible\n";
        for(int i=1;i<=n;i++)
            lft[i].clear();
    }

}
