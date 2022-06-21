#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

#define dbg(x) cerr << "LINE : "<<__LINE__ <<" "<< #x <<" -> "<<(x)<<endl;

#define DBG(x) dbg(x)
typedef long long ll;

const int N=3e5+5;
const int oo = 1e9+7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int T,cs=0;
    cin>>T;
    while(T--)
    {
        int n;
        cin>>n;
        int a=0;
        while(n--)
        {
            int t=0;
            int x=6;
            while(x--)
            {
                int u;
                cin>>u;
                t+=u;
            }
            a+=t==0;
        }
        cout<<"Case "<<++cs<<": "<<a<<"\n";
    }

}
