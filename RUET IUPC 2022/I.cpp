//21
#include<bits/stdc++.h>
using namespace std;
#define dbg(x) cerr << "LINE : "<<__LINE__ <<" "<< #x <<" -> "<<(x)<<endl;

#define DBG(x) dbg(x)
typedef long long ll;

const int N=3e5+5;
const int oo = 1e9+7;
bool isthere[10][8];
void init() {
    isthere[0][0] = 1;
    isthere[0][1] = 1;
    isthere[0][2] = 1;
    isthere[0][3] = 1;
    isthere[0][4] = 1;
    isthere[0][5] = 1;

    isthere[1][1] = 1;
    isthere[1][2] = 1;

    isthere[2][0] = 1;
    isthere[2][1] = 1;
    isthere[2][3] = 1;
    isthere[2][4] = 1;
    isthere[2][6] = 1;

    isthere[3][0] = 1;
    isthere[3][1] = 1;
    isthere[3][2] = 1;
    isthere[3][3] = 1;
    isthere[3][6] = 1;

    isthere[4][1] = 1;
    isthere[4][2] = 1;
    isthere[4][5] = 1;
    isthere[4][6] = 1;

    isthere[5][0] = 1;
    isthere[5][2] = 1;
    isthere[5][3] = 1;
    isthere[5][5] = 1;
    isthere[5][6] = 1;

    isthere[6][0] = 1;
    isthere[6][2] = 1;
    isthere[6][3] = 1;
    isthere[6][4] = 1;
    isthere[6][5] = 1;
    isthere[6][6] = 1;

    isthere[7][0] = 1;
    isthere[7][1] = 1;
    isthere[7][2] = 1;

    isthere[8][0] = 1;
    isthere[8][1] = 1;
    isthere[8][2] = 1;
    isthere[8][3] = 1;
    isthere[8][4] = 1;
    isthere[8][5] = 1;
    isthere[8][6] = 1;


    isthere[9][0] = 1;
    isthere[9][1] = 1;
    isthere[9][2] = 1;
    isthere[9][3] = 1;
    isthere[9][5] = 1;
    isthere[9][6] = 1;

}
pair<int, int> dp2[10][10];
pair<int, int> changeDigit(int x, int y) {
    int shorabo = 0;
    int anbo = 0;
    int cnt1 = 0;
    int cnt2 = 0;
    for(int i = 0; i < 7; i++) {
        if(isthere[x][i] == 1 and isthere[y][i] == 0) shorabo++;
        if(isthere[x][i] == 0 and isthere[y][i] == 1) anbo++;
    }
    return make_pair(anbo, shorabo);
}
const int NN=200+5;
int save[NN][NN][2][NN*7];
bool sv2[NN][NN][2][NN*7];
    string s;int n;
    int cs;
bool dp(int i,int k,int extra)
{
    if(i==n)
    {
        return extra == 0;
    }
    if(extra<0 and abs(extra) > (n-i) * 5)  return 0;
    if(extra>0 and abs(extra) > (n-i) * 5)  return 0;

    int sgn = extra>0;
    int t = abs(extra);
    if(save[i][k][sgn][t] == cs)
        return sv2[i][k][sgn][t];
    save[i][k][sgn][t]=cs;
    bool &ret=sv2[i][k][sgn][t]=0;
    int x=s[i]-'0';
    for(int y=0;y<10;y++)
    {
//        auto z = changeDigit(x,y);
        auto z = dp2[x][y];
        if(k>=z.second)
            ret|=dp(i+1,k-z.second,extra+z.second-z.first);
        if(ret)
            break;
    }
    return ret;
}

//void iter()
//{
//}

void pr(int i,int k,int extra)
{
    if(i==n)
    {
        return;
    }
    int x= s[i]-'0';
    for(int y=9;y>=0;y--)
    {
//        DBG(y);
        auto z = dp2[x][y];
//        DBG(z.first);
//        DBG(z.second);

        if(k>=z.second and dp(i+1,k-z.second,extra+z.second-z.first))
        {
            cout<<y;
            return pr(i+1,k-z.second,extra+z.second-z.first);
        }
    }
}

void solve() {
    cin >> s;
    n=s.size();
    int q;
    cin >> q;

    while(q--)
    {
        int k;
        cin>>k;
        pr(0,k,0);
        cout<<"\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int t;
    cin >> t;
    int tc = 1;
    cs=1;
    init();
    for(int i=0;i<10;i++)
        for(int j=0;j<10;j++){
            dp2[i][j]=changeDigit(i,j);
//            DBG(dp2[i][j].first);
        }

    while(t--) {
        cout << "Case " << tc++ << ":\n";
        solve();
        cs++;
    }

}
