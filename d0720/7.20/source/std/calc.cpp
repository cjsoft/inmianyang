#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <string>
using namespace std;
typedef long long LL;
const int Maxn=3000005,inf=999999999+208;
int l,r,p;
int pr[30],pn=0;
int num[Maxn],f[Maxn],n=0;
bool flag[Maxn];

bool isprime(int x) {
    for (int i=2;i*i<=x;i++)
        if (x%i==0) return false;
    return true;
}

void dfs(int idx,LL v) {
    if (idx>pn) num[++n]=v,f[n]=inf;
    else {
        for (;v<=r;v*=pr[idx])
            dfs(idx+1,v);
    }
}

int main() {
	freopen("calc.in","r",stdin);
	freopen("calc.out","w",stdout);
    cin>>l>>r>>p;
    for (int i=2;i<=p;i++)
        if (isprime(i)) pr[++pn]=i;
    dfs(1,1);
    sort(num+1,num+n+1);
    f[1]=0; flag[1]=true;
    for (int i=2,N=num[n];i<p;i++) {
        for (int j=1,w=1;num[j]*i<=N;j++) {
            while (num[w]<num[j]*i) ++w;
            f[w]=min(f[w],f[j]+1);
            if (f[w]+i<=p) flag[w]=true;
        }
    }
    int ans=0;
    for (int i=1;i<=n;i++) if (num[i]>=l&&flag[i]) ++ans;
    cout<<ans<<endl;
    return 0;
}
