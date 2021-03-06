#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <assert.h>
using namespace std;
int o,dis[505][505],n,i,MAX,j,A,B,C,m,chang[10005],next[1005],e[1005],head[1005],fa[1005],T[1050],a[1005],sum,siz[1005],DP[1005],k,ans;
bool v[1005];
short dp[505][505][505],Be[505][505];
void dfs(int x,int y)
{
    dis[x][i]=y;
    int now=head[x];
    while (now!=0)
    {
        if (!v[e[now]])
        {
            v[e[now]]=true;
            dfs(e[now],min(y+chang[now],1000000005));
        }
        now=next[now];
    }
}
void dfs2(int x,int y)
{
	MAX=max(MAX,y);
    int now=head[x]; siz[x]=1;
    while (now!=0)
    {
        if (!v[e[now]])
        {
            v[e[now]]=true;
            fa[e[now]]=x;
            dfs2(e[now],y+1);
        }
        now=next[now];
    }
    for (int j=1; j<=n; j++)
    if (dis[x][j]<=m)
    {
        now=head[x]; siz[x]=1;
        dp[x][j][1]=T[j];
        while (now!=0)
        {
            if (fa[e[now]]==x)
            {
                for (int k=1; k<=siz[x]; k++)
                  for (int l=1; l<=siz[e[now]]; l++)
                  {
                      DP[k+l-1]=min(DP[k+l-1],dp[x][j][k]+dp[e[now]][j][l]-T[j]);
                      DP[k+l]=min(DP[k+l],dp[x][j][k]+Be[e[now]][l]);
                  }
                siz[x]+=siz[e[now]];
                for (int k=1; k<=siz[x]; k++) {dp[x][j][k]=DP[k];DP[k]=1000;}
            }
            now=next[now];
        }
    }
    for (int j=1; j<=n; j++) for (int k=1; k<=siz[x]; k++) Be[x][k]=min(Be[x][k],dp[x][j][k]);
}
void add(int a,int b,int c,int d)
{
    e[a]=c;
    next[a]=head[b];
    head[b]=a;
    chang[a]=d;
}
int f[1005];
int getf(int k) {return f[k]==k?f[k]:f[k]=getf(f[k]);}
int main()
{
    freopen("tree.in","r",stdin);
    freopen("tree.out","w",stdout);
    scanf("%d%d",&n,&m);assert(1<=n && n<=500 && 1<=m && m<=1000000000);
    for (i=1; i<=n; i++)
    {
        scanf("%d",&a[i]); assert(0<=a[i] && a[i]<2);
        if (a[i]) sum++;
    }
    for (i=1; i<=n; i++) f[i]=i;
    for (i=1; i<n; i++)
    {
        scanf("%d%d%d",&A,&B,&C);
        assert(1<=A && A<=n && 1<=B && B<=n && 1<=C && C<=1000000000);
        f[getf(A)]=getf(B);
        add(++o,A,B,C);
        add(++o,B,A,C);
    }
    for (i=2; i<=n; i++) assert(getf(i)==getf(1));
    for (i=1; i<=n; i++)
    {
        for (j=1; j<=n; j++) v[j]=false;
        v[i]=true;
        dfs(i,0);
    }
    for (i=1; i<=n; i++) v[i]=false;
    v[1]=true;
    for (k=0; k<=n; k++) DP[k]=1000;
    for (i=0; i<=n; i++) for (j=0; j<=n; j++) Be[i][j]=1000;
    for (i=0; i<=n; i++)
      for (j=0; j<=n; j++)
        for (k=0; k<=n; k++)
          dp[i][j][k]=1000;
    for (i=1; i<=n; i++) T[i]=1-a[i];
    dfs2(1,1);
    ans=1000;
    for (i=1; i<=sum; i++) ans=min(ans,(int)Be[1][i]);
    if (ans>=1000) cout<<-1; else cout<<ans;
    return 0;
}
