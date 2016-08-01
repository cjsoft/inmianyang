#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <map>
#include <vector>
#include <ctime>
#include <conio.h>
using namespace std;
int i,n,m,j;
double dp[1000005],sum[1000005];
int main()
{
    freopen("qaq.in","r",stdin);
    freopen("qaq.out","w",stdout);
    int T;
    scanf("%d",&T);
    while (T--)
    {
    cin>>m>>n; dp[0]=1; dp[1]=1/(m+0.0); sum[0]=dp[0]; sum[1]=dp[0]+dp[1];
    for (i=2; i<=n; i++)
    {
        dp[i]=sum[i-1]/(m+0.0);
        if (i>m) dp[i]-=sum[i-m-1]/(m+0.0);
        sum[i]=sum[i-1]+dp[i];
        if (fabs(dp[i]-dp[i-1])<0.0000000000001)
        {
            printf("%.5f\n",dp[i]);
            break;
        }
    }
    if (i==n+1)printf("%.5f\n",dp[n]);
    }
    return 0;
}
