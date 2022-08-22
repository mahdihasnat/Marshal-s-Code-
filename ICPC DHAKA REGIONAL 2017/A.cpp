#include<bits/stdc++.h>
using namespace std;
#define int long long

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int a, b, c, d;
    while(1) {
        cin >> a >> b >> c >> d;
        if(a == 0 and b == 0 and c == 0 and d == 0) break;
        int row_diff = abs(a - c);
        int col_diff = abs(b - d);
        if(a < c) {
            if(a % 2 == b % 2) {
                int ans = 2 * row_diff - 1;
                int extra;
                if(row_diff - 1 <= col_diff) {
                    extra = col_diff - (row_diff - 1);
                }
                else {
                    extra = abs(col_diff - row_diff + 1) % 2;
                }
                ans = ans + extra;
                cout << ans << "\n";
            }
            else {
                int ans = 2 * row_diff;
                int extra;
                if(row_diff <= col_diff) {
                    extra = col_diff - (row_diff);
                }
                else {
                    extra = abs(col_diff - row_diff) % 2;
                }
                ans = ans + extra;
                cout << ans << "\n";
            }
        }
        else {
            if(a % 2 != b % 2) {
                int ans = 2 * row_diff - 1;
                int extra;
                if(row_diff - 1 <= col_diff) {
                    extra = col_diff - (row_diff - 1);
                }
                else {
                    extra = abs(col_diff - row_diff + 1) % 2;
                }
                ans = ans + extra;
                cout << ans << "\n";
            }
            else {
                int ans = 2 * row_diff;
                int extra;
                if(row_diff <= col_diff) {
                    extra = col_diff - (row_diff);
                }
                else {
                    extra = abs(col_diff - row_diff) % 2;
                }
                ans = ans + extra;
                cout << ans << "\n";
            }
        }
    }
    return 0;
}
