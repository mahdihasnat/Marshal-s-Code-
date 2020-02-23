#include<bits/stdc++.h>
#define ll long long int
#define pii pair<int,int>
#define uu first
#define vv second
#define fastRead ios::sync_with_stdio(0);cin.tie(0)
#define INF 1E9
#define MOD 1e9 + 7
using namespace std;
const int MAX = 1e5 + 5;
int t , n  ,m , cnt[MAX] , penalty[MAX] , tst;
int attempt[1000][1000]  , ques[1000][1000] , _time[1000][1000], rlist[1000];
string name[MAX];
map<string ,int>mp;


void reset() {

    for(int i =1;  i <=n ; i++ ) {
        for(int j =1 ; j <=m ; j++ ) {
            attempt[i][j] = 0;
            ques[i][j] = 0;
            _time[i][j] = 0;
        }
    }
    mp.clear();
}

void setInitScore(string &str , int id) {

//    cout<<str<<'\n';
    int pcnt  =0 , pen = 0 , state = 0;
    for(int i =0 ; i <str.size()  ; i++ ) {
        if(str[i] == ' ') continue;
        if(str[i] == '/') state = 1;
        else if(state == 0) {
            pcnt = pcnt *10 + (str[i] - '0');
        }
        else {
            pen = pen *10 + (str[i] - '0');
        }
    }
    cnt[id] = pcnt;
    penalty[id] = pen;

}

void addScore(string &str , int ro , int col) {


    if(str[0] == '-' || str[0] == '0') return;
    if(str[0] == '?') ques[ro][col] = 1;


    int  state = 0;
    int i = 0;
    if(str[0] == '?' ) i++;

    for(;i < str.size() ; i++ ) {
        if(str[i] == ' ') continue;
        if(str[i] == '/') state = 1;
        else if( state == 0 ) {
            attempt[ro][col] = attempt[ro][col]*10 + str[i] -'0';
        }
        else {
            _time[ro][col] = _time[ro][col]*10 + str[i] -'0';
        }
    }

}


void process(string &str , int id) {
    //0 -> |
    int i =0;
    i++;
    string teamname = "";
    for( int cnt = 0; cnt < 20; i++  ,cnt++ ) {
        teamname += str[i];
    }
    name[id] = teamname;
    mp[teamname] = id;

    i++;
    string score = "";
    for( int cnt = 0  ; cnt  < 7 ; cnt++ , i++) {
        score += str[i];
    }
    setInitScore(score , id);
    i++;

    for(int j = 1 ; j <= m ; j++) {
        string pt = "";
        for(int cnt = 0 ; cnt < 7  ; cnt++ , i++) {
            pt += str[i];
        }
        addScore(pt , id , j);
        i++;
    }

}

void input() {
    int cnt = 0;
    for(int i =0 ; i < (n+1)*2 +2 ; i++ ) {

        string str;

        getline(cin , str);

        if(i%2  || i < 3) continue;

        process(str , ++cnt);

    }
}



void input1() {
    string str;
    int cnt  =0;
    for(int i =0 ; i < n + 3; i++ ) {
        getline(cin , str);
//        cin.ignore();
        if(i < 2 || i == n+2) continue;
//        cout<<str<<'\n';
        string nam = "";
        for(int j = 1 ; j < 21 ; j++) nam += str[j];
        rlist[++cnt] = mp[nam];
    }

}
void  print() {
    for(int i =1 ; i <= n ; i++ ) {
        cout<<name[i]<<" "<<cnt[i]<<" "<<penalty[i]<<endl;
        cout<<" --- "<<endl;
        for(int j = 1; j<= m ;j++ ) cout<<attempt[i][j]<<" "<<_time[i][j]<<" " <<ques[i][j]<<endl;
        cout<<endl;
    }
}



int main()
{
    fastRead;
    cin>>t;
    while(t--) {

        cin>>n>>m;
        reset();
        input();
        input1();
        for(int i =1 ; i <= n ; i++ ) cout<<rlist[i]<<" ";
        cout<<endl;
//        cout<<'\n';
//        cout<<"Case "<<++tst<<": "<<solve()<<'\n';
    }
    return 0;
}
