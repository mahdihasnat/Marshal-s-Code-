#include<bits/stdc++.h>
#define ll long long int
#define pii pair<int,int>
#define uu first
#define vv second
#define fastRead ios::sync_with_stdio(0);cin.tie(0)
#define INF 1E9
using namespace std;

const int MAX = 1e5 + 3;

int n , pcnt[MAX] ,pen[MAX]  , ara[MAX];
vector<int>rec[MAX];

bool ok() {

    int lastcnt = INF;
    int lastpen = INF;

    for(int i =1 ; i<=n ; i++ ) {
        int id = ara[i];

        int nowpen = pen[id];
        int nowcnt = pcnt[id];
        for(auto x: rec[id]) {

            if(nowcnt + 1 > lastcnt) break;
            if(nowcnt + 1 == lastcnt && nowpen + x < lastpen) break;

            nowcnt++;
            nowpen += x;
        }


//        cout<<id<<" -- "<<nowcnt <<" "<<nowpen<<endl;
        if(nowcnt > lastcnt ) return false;
        if(nowcnt == lastcnt && nowpen < lastpen) return false;


        lastcnt = nowcnt;
        lastpen = nowpen;
    }


    return true;


}

int main()
{
    fastRead;
    int t , tst = 0;
    cin>>t;

    while(t--) {

        cin>>n;
        for(int i =1 ; i <=n ; i++) rec[i].clear();

        for(int i =0 ; i < n ; i ++) {
            int id;
            cin>>id;
            cin>>pcnt[id]>>pen[id];
            int tmp;
            cin>>tmp;
            for(int j =0 ; j < tmp ; j++) {

                int _time;
                cin>>_time;
                rec[id].push_back(_time);
            }
        }

        for(int i =1 ; i<= n ; i++ ) cin>>ara[i];

        cout<<"Case "<<++tst<<": ";

        if(ok()) cout<<"We respect our judges :)\n";
        else cout<<"Say no to rumour >:\n";

    }
    return 0;
}

