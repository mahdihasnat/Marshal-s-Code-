#include<bits/stdc++.h>
using namespace std;

const int N =1e5+10;
const int K =20;

vector<int > tree[4*N];
#define ALL(x) x.begin() , x.end()
#define next asdfg
#define DBG(x) cout<<(#x)<<" --> "<<(x)<<endl;
#define NL cout<<endl;


char s[N];
int lg2[N];
int table[K+1][N];
int SA[N], iSA[N];
int cnt[N], next[N];
bool bh[N], b2h[N];
int lcp[N];
vector<int> alphacnt[256];

void buildSA(int n) {

    for(int i = 0; i < n; i++) alphacnt[s[i]].push_back(i);
    int nn=0;
    for(int i=0;i<256;i++) {
        for(int j: alphacnt[i])
            SA[nn++]=j;
        alphacnt[i].clear();
    }
    assert(nn==n);

//    for(int i = 0; i < n; i++) SA[i] = i;
//    sort(SA, SA + n, [](int i, int j) { return s[i] < s[j]; });

    for(int i = 0; i < n; i++) {
        bh[i] = i == 0 || s[SA[i]] != s[SA[i - 1]];
        b2h[i] = 0;
    }

    for(int h = 1; h < n; h <<= 1) {
        int tot = 0;
        for(int i = 0, j; i < n; i = j) {
            j = i + 1;
            while(j < n && !bh[j]) j++;
            next[i] = j; tot++;
        } if(tot == n) break;

        for(int i = 0; i < n; i = next[i]) {
            for(int j = i; j < next[i]; j++)
                iSA[SA[j]] = i;
            cnt[i] = 0;
        }

        cnt[iSA[n - h]]++;
        b2h[iSA[n - h]] = 1;
        for(int i = 0; i < n; i = next[i]) {
            for(int j = i; j < next[i]; j++) {
                int s = SA[j] - h;
                if(s < 0) continue;
                int head = iSA[s];
                iSA[s] = head + cnt[head]++;
                b2h[iSA[s]] = 1;
            }
            for(int j = i; j < next[i]; j++) {
                int s = SA[j] - h;
                if(s < 0 || !b2h[iSA[s]]) continue;
                for(int k = iSA[s] + 1; !bh[k] && b2h[k]; k++)
                    b2h[k] = 0;
            }
        }
        for(int i = 0; i < n; i++) {
            SA[iSA[i]] = i;
            bh[i] |= b2h[i];
        }
    }
    for(int i = 0; i < n; i++) iSA[SA[i]] = i;
}

void buildLCP(int n) {
    for(int i = 0, k = 0; i < n; i++) {
        if(iSA[i] == n - 1) { k = 0; continue; }
        int j = SA[iSA[i] + 1];
        while(i + k < n && j + k < n && s[i + k] == s[j + k]) ++k;
        lcp[iSA[i]] = k;
        if(k) k--;
    }
}
void buildSparse(int n)
{
    for(int i=0;i<n;i++)
        table[0][i] =lcp[i];
    for(int j=1;j<=K;j++)
    {
        for(int i=0;i+(1<<j) <=n ;i++)
            table[j][i] =min(table[j-1][i] , table[j-1][i+(1<<j-1)]);
    }
}


int getmin(int L,int R)
{
    int x = lg2[R-L+1];
    return min(table[x][L] , table[x][R-(1<<x) + 1]);
}

int minlen(int n,int L,int R)
{
    assert(R>=L);
    if(L>R) swap(L,R);
    if(L==R ) return n-SA[L];
    return getmin(L,R-1);
}

int high(int n,int i,int len)
{
    int lo = i , hi = n-1 , mid;
    assert(minlen(n,i,lo)>=len);
    while(lo<hi)
    {
        mid= (lo+hi+1)/2;
        if(minlen(n,i,mid)>=len)
            lo = mid;
        else hi = mid-1;
    }
    return lo;
}
int low(int n,int i,int len)
{
    int lo = 0 , hi  = i, mid;
    assert(minlen(n,hi,i)>=len);
    while(lo<hi)
    {
        mid= (lo+hi)/2;
        if(minlen(n,mid,i)>=len)
            hi = mid;
        else lo = mid+1;
    }
    return hi;
}

void build(int node,int l,int r)
{
    if(l==r)
    {
        tree[node] = vector<int > (1,SA[l]);
    }
    else
    {
        int mid =l+r >> 1;
        build(node<<1 , l, mid);
        build(node<<1|1 , mid+1 , r);
        tree[node].clear();
        tree[node].resize(tree[node<<1].size() + tree[node<<1|1].size());
        merge(ALL(tree[node<<1]) , ALL(tree[node<<1 | 1] ) , tree[node].begin());
    }
}

int query(int node,int ss,int se,int l,int r,int L,int R)
{
    if(ss>se or r<ss or l>se or r<l) return 0;
    int mid = ss+se >>1;
    if(ss>=l and r>=se)
    {
        return upper_bound(ALL(tree[node]) , R )- lower_bound(ALL(tree[node] ) , L) ;
    }
    return query(node<<1 , ss , mid , l,r,L,R) + query(node<<1 | 1 , mid+1 , se,l,r,L,R);
}


int main()
{
    lg2[1]=0;
    for(int i=2;i<N;i++) lg2[i]= lg2[i/2]+1;

    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%s",s);

        int n= strlen(s);
        buildSA(n);
        buildLCP(n);
        buildSparse(n);
        build(1,0,n-1);
        for(int i=0;i<n;i++)
            iSA[SA[i]]= i;
//        DBG(SA);
//        for(int i=0;i<n;i++){
//            for(int j=SA[i];j<n;j++)
//                cout<<s[j];
//            NL;
//            DBG(lcp[i]);
//        }
//        NL;
//        for(int i=0;i<n;i++)
//        {
//            DBG(i);
//            for(int j=i;j<n;j++)
//            {
//                cout<<minlen(n,i,j)<<" ";
//            }
//            NL;
//        }

        int q;
        scanf("%d",&q);
        while(q--)
        {
            int a,b,c,d;
            scanf("%d %d %d %d",&a,&b,&c,&d);
            a--;
            b--;
            c--;
            d--;
            int len = d-c+1;
            c =iSA[c];

            b = b-len +1;
            int l  = low(n,c,len);
            int r = high(n,c,len);
//            DBG(c);
//            DBG(len);
//            DBG(l);
//            DBG(r);
//            DBG(SA);
//            for(int i=l;i<=r;i++) cout<<SA[i]<<" "; NL;
//            DBG(a);
//            DBG(b);
            int ans = 0;
            if(a<=b)
                ans =query(1,0,n-1,l,r,a,b);
            printf("%d\n",ans);
        }
    }
}
