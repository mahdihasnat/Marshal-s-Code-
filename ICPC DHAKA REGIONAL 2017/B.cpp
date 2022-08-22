#include<bits/stdc++.h>
using namespace std;
#define int long long
void solve() {
    string s;
    cin >> s;
    int curr = 0;
    stack<pair<char, int>> st;
    int sz = s.size();
    int maxdis[sz + 1];
    memset(maxdis, -1, sizeof(maxdis));
    int res[sz + 1];
    int back_res[sz + 1];
    memset(back_res, 0, sizeof(back_res));
    memset(res, 0, sizeof(res));
    int link[sz + 1];
    memset(link, -1, sizeof(link));
    int normal[sz + 1];
    memset(normal, -1, sizeof(normal));
    for(auto x: s) {
        if(x == ')') {
            if(!st.empty() and st.top().first == '(') {
                auto temp = st.top();
                st.pop();
                normal[curr] = temp.second;
                if(temp.second > 0 and normal[temp.second - 1] != -1) link[normal[temp.second - 1]] = temp.second;
                int add = 0;
                if(temp.second > 0) add = back_res[temp.second - 1];
                res[temp.second] = (curr - temp.second + 1);
                add = add + curr - temp.second + 1;

                res[curr - add + 1] = add;
                maxdis[curr - add + 1] = curr;
                back_res[curr] = add;

            }
            else {
                while(!st.empty()) st.pop();
            }
        }
        else if(x == '}') {
            if(!st.empty() and st.top().first == '{') {
                auto temp = st.top();
                st.pop();
                normal[curr] = temp.second;
                if(temp.second > 0 and  normal[temp.second - 1] != -1) link[normal[temp.second - 1]] = temp.second;
                int add = 0;
                if(temp.second > 0) add = back_res[temp.second - 1];
                res[temp.second] = (curr - temp.second + 1);
                add = add + curr - temp.second + 1;
                res[curr - add + 1] = add;
                maxdis[curr - add + 1] = curr;
                back_res[curr] = add;

            }
            else {
                while(!st.empty()) st.pop();
            }
        }
        else if(x == ']') {
            if(!st.empty() and st.top().first == '[') {
                auto temp = st.top();
                st.pop();
                normal[curr] = temp.second;
                if(temp.second > 0 and normal[temp.second - 1] != -1) link[normal[temp.second - 1]] = temp.second;
                int add = 0;
                if(temp.second > 0) add = back_res[temp.second - 1];
                res[temp.second] = (curr - temp.second + 1);
                add = add + curr - temp.second + 1;
                res[curr - add + 1] = add;
                maxdis[curr - add + 1] = curr;
                back_res[curr] = add;

            }
            else {
                while(!st.empty()) st.pop();
            }
        }
        else if(x == '>') {
            if(!st.empty() and st.top().first == '<') {
                auto temp = st.top();
                st.pop();
                normal[curr] = temp.second;
                if(temp.second > 0 and normal[temp.second - 1] != -1) link[normal[temp.second - 1]] = temp.second;
                int add = 0;
                if(temp.second > 0) add = back_res[temp.second - 1];
                res[temp.second] = (curr - temp.second + 1);
                add = add + curr - temp.second + 1;
                res[curr - add + 1] = add;
                maxdis[curr - add + 1] = curr;
                back_res[curr] = add;

            }
            else {
                while(!st.empty()) st.pop();
            }
        }
        else {
            st.push({x, curr});
        }
        curr++;
    }
    //cout << link[0] << " " << link[2] << " " << link[4] << "\n";
    bool vis[sz + 1];
    memset(vis, 0, sizeof(vis));
    for(int i = 0; i < sz; i++) {
        if(vis[i]) continue;
        int maxi = maxdis[i];
        int curr = i;
        while(link[curr] != -1) {
            curr = link[curr];
            vis[curr] = 1;
            maxi = max(maxi, maxdis[i]);
            res[curr] = max(res[curr], maxi - curr + 1);
        }
    }
    for(int i = 0; i < sz; i++) cout << res[i] << "\n";
}
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int t;
    cin >> t;
    int tc = 1;
    while(t--) {
        cout << "Case " << tc++ << ":\n";
        solve();
    }
}
