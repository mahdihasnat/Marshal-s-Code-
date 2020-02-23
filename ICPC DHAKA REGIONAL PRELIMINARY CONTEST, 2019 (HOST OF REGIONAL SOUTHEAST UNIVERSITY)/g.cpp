#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

ll phi[10000007];
bool siv[10000007];

void gen() {

    for(int i=2;i<=10000000;i++) {
        if(siv[i]) {
            continue;
        }

        phi[i]=i-1;

        for(int j=i+i;j<=10000000;j+=i) {
            siv[j]=1;
            phi[j]/=(ll)i;
            phi[j]*=(ll)(i-1);
        }
    }
}



int main() {

    for(int i=1;i<=10000000;i++) {
        phi[i]=i;
    }
    gen();

    for(int i=1;i<=1e7;i++) {
        phi[i]=phi[i-1]+phi[i];
    }


    int t;
    scanf("%d",&t);

    for(int cs=1;cs<=t;cs++) {
        ll n,p;
        scanf("%lld %lld",&n,&p);

        ll lo=1;
        ll hi=n;
        ll md;
        ll ans=-1;

        while(lo<=hi) {
            md=(lo+hi)/2;
            ll val=phi[n/md];
//            cout<<md<<" "<<val<<endl;
            if(val>=p) {
                ans=md;
                lo=md+1;
            } else {
                hi=md-1;
            }
        }

        printf("Case %d: %lld\n",cs,ans);

    }


    return 0;
}
