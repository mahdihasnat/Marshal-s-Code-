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

const int N=1e6+5;
const int oo=1e9+7;

const int K = 25; // ceil(log2(n)) + 1
int st1[N][K +1]; // mini
int st2[N][K +1]; // maxi
int lg2[N];
int a[N];


int maxi1(int i,int j)
{
    if(a[i]== a[j]) return min(i,j);
    return a[i]>a[j] ? i: j;
}
int maxi2(int i,int j)
{
    if(a[i]== a[j]) return max(i,j);
    return a[i]>a[j] ? i: j;
}

void make_table( int n)
{


    for (int i = 1; i <= n; i++)
        st1[i][0]  = st2[i][0]= i ;

    for (int j = 1; j <= K; j++)
        for (int i = 1; i + (1 << j) <= n+1; i++)
        {
            st1[i][j]= maxi1(st1[i][j-1], st1[i + (1 << (j - 1))][j - 1]);
            st2[i][j]= maxi1(st2[i][j-1], st2[i + (1 << (j - 1))][j - 1]);
        }
}
int q1(int L,int R)
{
    if(R<L) return 0;
    int j = lg2[R - L + 1];
    return maxi1(st1[L][j], st1[R - (1 << j) + 1][j]);
}
int q2(int L,int R)
{
    if(R<L) return 0;
    int j = lg2[R - L + 1];
    return maxi2(st2[L][j], st2[R - (1 << j) + 1][j]);
}



ll ans;



void sol(int l,int r)
{
    if(r-l+1 <2) return;

    if(r-l+1 == 2)
    {
        int m = max(a[l],a[r]);
        int sm = min(a[l],a[r]);
        ans= max(ans,1LL*(m-sm)*2);

        return ;
    }
    int m= q1(l,r);



    int nowl = l,nowr = r;
    while(nowr-nowl+1 >=2 )
    {
        int sm  = 0;

        sm = maxi2(sm,q2(nowl,m-1));
        sm = maxi2(sm,q1(m+1,nowr));

        ans= max(ans,1LL*(a[m]- a[sm])*(nowr-nowl+1));
        assert(sm!=m);
        if(sm<m)
            nowl=sm+1 ;
        else
            nowr=sm-1 ;

    }

    sol(l,m-1);
    sol(m+1,r);
}
void iterative_sol(int n)
{
    stack<int > stak;
    stak.push(1);
    stak.push(n);

    while(!stak.empty())
    {
        int  r= stak.top();
        stak.pop();
        int  l= stak.top();
        stak.pop();

        if(r-l+1 <2)  continue;

        if(r-l+1 == 2)
        {
            int m = max(a[l],a[r]);
            int sm = min(a[l],a[r]);
            ans= max(ans,(m-sm)*2LL);

            continue ;
        }
        int m= q1(l,r);


//        DBG(m);
//        DBG(l);
//        DBG(r);
//        NL;

        int nowl = l,nowr = r;
        while(nowr-nowl+1 >=2 )
        {
            int sm  = 0;
            if(nowl>m) break;
            if(nowr<m) break;
            sm = maxi2(sm,q2(nowl,m-1));
            sm = maxi2(sm,q1(m+1,nowr));
            assert(sm!=0);


            ans= max(ans, 1LL*(a[m]- a[sm])*(nowr-nowl+1));
            assert(sm!=m);
            if(sm<m)
                nowl=sm+1 ;
            else
                nowr=sm-1 ;

        }

        stak.push(l);
        stak.push(m-1);


        stak.push(m+1);
        stak.push(r);

    }
}
int32_t main()
{
    FastIO;
//    IN;
    lg2[1] = 0;
    for (int i = 2; i < N; i++)
        lg2[i] = lg2[i/2] + 1;



    int T,cs=0;
    cin>>T;
    while(T--)
    {
        cout<<"Case "<<++cs<<": ";
        a[0]=-1;
        int n;
        cin>>n;
        for(int i=1; i<=n; i++)
            cin>>a[i];
        make_table(n+1);

        ans=0;
        iterative_sol(n);
        cout<<ans<<"\n";
    }
}
