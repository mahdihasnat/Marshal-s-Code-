#include<bits/stdc++.h>
using namespace std;
#define dbg(x) cerr << "LINE : "<<__LINE__ <<" "<< #x <<" -> "<<(x)<<endl;

#define DBG(x) dbg(x)
typedef long long ll;

const int N=3e5+5;
const int oo = 1e9+7;

int parent[1000005];
int rating[1000005];
void init(int n) {
    for(int i = 1; i <= n; i++) parent[i] = i, rating[i] = 1;
}
int findParent(int root) {
    return parent[root] = (parent[root] == root ? root : findParent(parent[root]));
}
bool findUnion(int x, int y) {
    int par1 = findParent(x);
    int par2 = findParent(y);
    if(par1 == par2) return false;
    else {
        if(rating[par1] >= rating[par2]) {
            parent[par2] = par1;
            rating[par1] += rating[par2];
        }
        else {
            parent[par1] = par2;
            rating[par2] += rating[par1];
        }
        return true;
    }
}
void solve() {
    int n;
    cin >> n;
    init(n);
    int curr = n / 2;
    ll ans = 0;
    while(curr >= 1) {
        for(int i = 2; i * curr <= n; i++) {
            if(findUnion(curr, i * curr)) ans += curr;
        }
        curr--;
    }
    cout << ans << "\n";
}
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t;
    cin >> t;
    int tc = 1;
    while(t--) {
        cout << "Case " << tc++ << ": ";
        solve();
    }

}
