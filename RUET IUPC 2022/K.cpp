// 21
#include<bits/stdc++.h>
using namespace std;
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
    while(T--) {
    map<string ,string > mp,mp2;
        int m;
        cin>>m;
        while(m--)
        {
            int tp;
            cin>>tp;
            string x,t;
            cin>>x;
            if(tp==1)
            {
                cin>>t;
                if(mp.find(x) == mp.end())
                    mp[x]=x;
                if(mp.find(t)==mp.end())
                    mp[t]=mp[x],
                    mp.erase(x);
                mp2[x]=x;
                mp2[t]=t;
            }
            else
            {
                string s;
                if(mp2.find(x) != mp2.end()){
                if(mp.find(x)==mp.end())
                    s="Not in use!";
                else s=mp[x];
                }
                else mp[x]=x,s=x;
                cout<<s<<"\n";
            }

        }


    }
}

//1 6 1 theredwarrior thegreenwarrior 1 theyellowwarrior thegreenwarrior 2 thegreenwarrior 2 theyellowwarrior 2 theredwarrior 2 theorangewarrior
