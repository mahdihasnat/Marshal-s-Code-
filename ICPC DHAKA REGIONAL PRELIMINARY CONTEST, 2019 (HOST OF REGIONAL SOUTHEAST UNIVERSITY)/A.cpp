///****In the name of Allah, most Gracious, most Compassionate****//

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

const int N=3e6+5;
const int oo=1e9+7;




///https://codeforces.com/blog/entry/4025?#comment-81534


// lexicographic order for pairs
inline bool leq(int a1, int a2, int b1, int b2) {
    return(a1 < b1 || a1 == b1 && a2 <= b2);
}

// and triples
inline bool leq(int a1, int a2, int a3, int b1, int b2, int b3) {
    return(a1 < b1 || a1 == b1 && leq(a2,a3, b2,b3));
} // and triples

// stably sort a[0..n-1] to b[0..n-1] with keys in 0..K from r
static void radixPass(int* a, int* b, int* r, int n, int K) {// count occurrences
    int* c = new int[K + 1]; // counter array
    for (int i = 0; i <= K; i++) c[i] = 0; // reset counters
    for (int i = 0; i < n; i++) c[r[a[i]]]++; // count occurrences
    for (int i = 0, sum = 0; i <= K; i++) // exclusive prefix sums
    {
        int t = c[i];
        c[i] = sum;
        sum += t;
    }
    for (int i = 0;  i < n; i++) b[c[r[a[i]]]++] = a[i]; // sort
    delete [] c;
}

// find the suffix array SA of s[0..n-1] in {1..K}ˆn  , k is ALPHABET SIZE
// require s[n]=s[n+1]=s[n+2]=0, n>=2
void suffixArray(int* s, int* SA, int n, int K) {
    int n0 = (n+2)/3, n1 = (n+1)/3, n2 = n/3, n02 = n0+n2;
    int* s12 = new int[n02+3]; s12[n02] = s12[n02+1] = s12[n02+2] = 0;
    int* SA12 = new int[n02+3]; SA12[n02] = SA12[n02+1] = SA12[n02+2] = 0;
    int* s0 = new int[n0];
    int* SA0 = new int[n0];
    // generate positions of mod 1 and mod 2 suffixes
    // the "+(n0-n1)" adds a dummy mod 1 suffix if n%3 == 1
    for (int i=0, j=0; i < n + (n0-n1); i++)
        if (i%3 != 0) s12[j++] = i;
    // lsb radix sort the mod 1 and mod 2 triples
    radixPass(s12 , SA12, s+2, n02, K);
    radixPass(SA12, s12 , s+1, n02, K);
    radixPass(s12 , SA12, s  , n02, K);
    // find lexicographic names of triples
    int name = 0, c0 = -1, c1 = -1, c2 = -1;
    for (int i = 0; i < n02; i++) {
        if (s[SA12[i]] != c0 || s[SA12[i]+1] != c1 || s[SA12[i]+2] != c2) {
            name++;
            c0 = s[SA12[i]];
            c1 = s[SA12[i]+1];
            c2 = s[SA12[i]+2];
        }
        if (SA12[i]%3 == 1) s12[SA12[i]/3] = name; // left half
        else s12[SA12[i]/3 + n0] = name; // right half
    }
    // recurse if names are not yet unique
    if (name < n02) {
        suffixArray(s12, SA12, n02, name);
        // store unique names in s12 using the suffix array
        for (int i = 0; i < n02; i++) s12[SA12[i]] = i + 1;
    } else // generate the suffix array of s12 directly
        for (int i = 0;  i < n02; i++) SA12[s12[i] - 1] = i;
    // stably sort the mod 0 suffixes from SA12 by their first character
    for (int i = 0, j = 0; i < n02; i++)
        if (SA12[i] < n0) s0[j++] = 3*SA12[i];
    radixPass(s0, SA0, s, n0, K);
    // merge sorted SA0 suffixes and sorted SA12 suffixes
    for (int p = 0, t = n0-n1, k = 0; k < n; k++) {
        #define GetI() (SA12[t] < n0 ? SA12[t] * 3 + 1 : (SA12[t] - n0) * 3 + 2)
        int i = GetI(); // pos of current offset 12 suffix
        int j = SA0[p]; // pos of current offset 0 suffix
        if (SA12[t] < n0 ? // different compares for mod 1 and mod 2 suffixes
            leq(s[i], s12[SA12[t] + n0], s[j], s12[j/3]) :
            leq(s[i],s[i+1],s12[SA12[t]-n0+1], s[j],s[j+1],s12[j/3+n0]))
        {// suffix from SA12 is smaller
            SA[k] = i; t++;
            if (t == n02) // done --- only SA0 suffixes left
            for (k++; p < n0; p++, k++) SA[k] = SA0[p];
        } else {// suffix from SA0 is smaller
            SA[k] = j; p++;
            if (p == n0) // done --- only SA12 suffixes left
            for (k++; t < n02; t++, k++) SA[k] = GetI();
        }
    }
    delete [] s12; delete [] SA12; delete [] SA0; delete [] s0;
}

void lcp_construction(int * s, int * SA , int *lcp, int n) {

    int * rank = new int [n];

    for (int i = 0; i < n; i++)
        rank[SA[i]] = i;

    int k = 0;
    for (int i = 0; i < n; i++) {
        if (rank[i] == n - 1) {
            k = 0;
            continue;
        }
        int j = SA[rank[i] + 1];
        while (i + k < n && j + k < n && s[i+k] == s[j+k])
            k++;
        lcp[rank[i]] = k;
        if (k)
            k--;
    }
    return ;
}

char ss [N]  , t[N];
int s[N];
int suf[N] , lcp[N];
int r_suf[N];
const int K = 25 ; /// k >= ceil(lg22(n)) +1
int st[N][K + 1];
int lg2[N+1];
void ini()
{
    lg2[1] = 0;
    for (int i = 2; i <= N; i++)
        lg2[i] = lg2[i/2] + 1;
}
int f( int i,int j)
{
    return i<j? i: j;
}

void pre(int   *array, int n)
{

    for (int i = 0; i < n; i++)
        st[i][0] = array[i];

    for (int j = 1; j <= K; j++)
        for (int i = 0; i + (1 << j) <= n; i++)
            st[i][j] = f( st[i][j-1], st[i + (1 << (j - 1))][j - 1]);
}
int getf( int L,int R)
{
    if(L>R) swap(L,R);
    int j = lg2[R - L + 1];
    return  f(st[L][j], st[R - (1 << j) + 1][j]);
}


int len(int i,int j)
{
     i = r_suf[i] , j =r_suf[j];
     if(i>j) swap(i,j);
     return getf(i,j-1);
}
int match(int i,int k , int m ,int x )
{

    int   j=0;
//    cout<<"  in  "<<i<<"  - --  \n";
    while(j<m)
    {
        int ln = len(i  , x+1+ j);
        j+=ln;
        i+=ln;
//        DBG(i);
//        DBG(j);
//        DBG(ln);
//        NL;
        if(j>=m or i>= x) break;
        if(k>0)
        {
            i++;
            j++;
            k--;
        }
        else
        {
            break;
        }
    }

    //    cout<<"  out  "<<j<<"  " <<k<<"- --  \n";
    //    NL;
    return j>=m ? 1 : 0;
}
int32_t main()
{
//    IN;
    ini();
    int T,cs=0;
    scanf("%d",&T);
    while(T--)
    {
        int k;
        scanf("%s %s %d" , ss , t ,&k);
        int n = 0;
        for(;ss[n]  ; n++)
            s[n] = ss[n];
        int x = n;
        s[n++]=0;
        int m = 0;
        for(int j=0;t[j];j++ , m++)
            s[n++]=t[j];
        suffixArray(s , suf , n , 130);
        lcp_construction(s,suf, lcp , n);
        for(int i=0;i<n;i++)
            r_suf[suf[i]]=i;
        pre(lcp , n);
//        DBG(len(0,0+x+1));
        int ans=0;
        assert(n-x-1 == m);
        for(int i=0;i<x;i++)
        {
            ans+=match(i,k,m,x);
        }
        printf("Case %d: %d\n",++cs , ans);
    }
}
