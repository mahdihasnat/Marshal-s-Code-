/// AC
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
ostream &operator <<(ostream &os, queue<int > q)
{
    os<<"[[[ ";
    while(!q.empty()) {

        os<<q.front()<<" ";
        q.pop();
    }
    os<<" ]]]";
    return os;
}



const int N=3e5+5;
const int oo=1e9+7;

int32_t main()
{
    FastIO;

    int T,cs=0;
    cin>>T;
    while(T--)
    {
        cout<<"Case "<<++cs<<": ";
        int p,n,t;

        cin>>p>>n>>t;
        vector<pii> inn;
        for(int i=0;i<n;i++)
        {
            int p,o;
            cin>>p>>o;
            inn.push_back({o,p});
        }
        sort(ALL(inn));
        vector<int > tday;
        for(int i=0;i<t;i++){
            int d;
            cin>>d;
            tday.push_back(d);
        }
        sort(ALL(tday));
        int id=0,ans=0;
        map<int ,queue< int >  > total;
        for(int i : tday)
        {
            while(id<n and inn[id].first<= i)
                total[inn[id].second].push(inn[id].first), id++;
//            DBG(i);
            vector<int > del;
            for(auto &x : total)
            {
//                DBG(x);
                ans=max(ans,i-x.second.front());
                x.second.pop();
                if(x.second.empty()) del.push_back(x.first);

            }
            for(int j: del)
                total.erase(total.find(j));
        }
        if(total.size() or id<n)
            cout<<"-1\n";
        else
            cout<<ans<<"\n";
    }
}
