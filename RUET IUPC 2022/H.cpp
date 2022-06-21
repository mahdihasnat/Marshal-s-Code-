
#include<bits/stdc++.h>
using namespace std;
#define dbg(x) cerr << "LINE : "<<__LINE__ <<" "<< #x <<" -> "<<(x)<<endl;

#define DBG(x) dbg(x)
typedef long long ll;
#define int ll
const int N=1e5+5;
const ll oo = 1e9+7;

ll pw[N];
ll qsm[N];


ll rn(int l,int r)
{
    ll ret = qsm[r];
    if(l>0)
        ret = (ret - qsm[l-1]) %oo;
    return ret;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    pw[0]=1;
    qsm[0]=1;

    for(ll i=1;i<N;i++){
        pw[i]=pw[i-1]*10 % oo;
        qsm[i]=(qsm[i-1] + pw[i]) %oo;
    }

    int T,cs=0;
    cin>>T;
    while(T--)
    {
        cout<<"Case "<<++cs<<":"<<"\n";
        string s;
        cin>>s;
        reverse(s.begin(),s.end());
        int x=0;
        int y=int(s.size())-1;
        ll ans = 0;
        int n=s.size();
        set<int> ase;
        for(int i=0;i<n;i++)
        {
            ase.insert(s[i]-'0');
            ans=(ans + pw[i] *(s[i]-'0'))%oo;
        }
//        DBG(ans);
        int q;
        cin>>q;
        set<int> st;
        deque<pair<int,int> > order;
        while(q--)
        {
            int d;
            cin>>d;
//            DBG(x);
//            DBG(y);
            if(ase.find(d)!=ase.end()){
                if(st.find(d) != st.end())
                {
                    int idx = -1;
                    int suru = x-1;
                    for(int j=0;j<order.size();j++)
                    {
                        if(order[j].first == d)
                        {
                            idx = j;
                            break;
                        }
                        suru-=order[j].second;
                    }
                    assert(idx!=-1);
//                    DBG(idx);
//                    DBG(suru);
                    int tot = order[idx].second;
                    ans = (ans - order[idx].first * (rn(suru -tot+1 , suru)) %oo)%oo;
                    suru -= tot;
//                    DBG(tot);
//                    DBG(suru);
                    for(int i=idx+1;i<order.size();i++)
                    {
                        ans = (ans - order[i].first * (rn(suru - order[i].second +1 , suru)) %oo)%oo;
                        ans = (ans + order[i].first * (rn(suru - order[i].second +1  + tot, suru + tot)) %oo)%oo;
                        order[i-1] = order[i];
                        suru -= order[i].second;
                    }
//                    DBG(suru);
                    assert(suru==-1);
                    ans = (ans + d * qsm[tot-1] %oo) %oo;
                    order[order.size()-1] = {d,tot};
                }
                else
                {
                    int tot = 0;
                    for(int i=y;i>=x;i--)
                    {
                        ans = (ans - pw[i] * (s[i]-'0')%oo) %oo;
                        if(s[i] - '0' == d)
                        {
                            tot++;
                        }
                        else
                        {
                            s[i+tot] = s[i];
                            ans = (ans + pw[i+tot] *(s[i]-'0') %oo )%oo;
                        }
                    }
                    int suru = x-1+tot;
                    int ekhon = x-1;
    //                DBG(suru);
    //                DBG(tot);
                    for(pair<int,int> j: order)
                    {
                        ans = (ans - j.first  * rn(ekhon - j.second +1 , ekhon))%oo;
                        ans = (ans + j.first  * rn(suru - j.second +1 , suru))%oo;
                        suru-=j.second;
                        ekhon-=j.second;
                    }
                    assert(tot == suru+1);
                    ans = (ans + d * qsm[tot-1])%oo;
                    order.push_back({d,tot});
                    x+=tot;
                    st.insert(d);
                }
            }
            while(y>=x and s[y] =='0')
                y--;
            if(y-x+1 ==0 and !order.empty() and order.front().first == 0)
            {
                x-=order.front().second;
                order.pop_front();
                ase.erase(0);
            }
            ans = (ans + oo)%oo;
//            DBG(ans);
            cout<<ans<<"\n";
        }
    }
}
