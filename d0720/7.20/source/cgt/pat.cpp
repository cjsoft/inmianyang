#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define N 100005
using namespace std;
typedef unsigned long long ull;
ull sum,x,now,hash[27][N],mi[N];
int c[N],a[N],b[N],i,j,cnt,p1,num,tot,n,m,p,A[N];
ull get(int x,int l,int r)
{return hash[x][r]-hash[x][l]*mi[r-l];}
int main()
{
	freopen("pat.in","r",stdin);
	freopen("pat.out","w",stdout);
	scanf("%d%d%d",&n,&m,&p);p1=6662333;
	for (i=1;i<=n;i++)scanf("%d",&a[i]);
	for (i=1;i<=m;i++)scanf("%d",&b[i]),c[i]=b[i];
	for (mi[0]=1,i=1;i<=n;i++)mi[i]=mi[i-1]*p1;
	sort(c+1,c+1+m);
	cnt=unique(c+1,c+1+m)-c-1;
	for (i=1;i<=m;i++)b[i]=lower_bound(c+1,c+1+cnt,b[i])-c;
	for (i=1;i<=m;i++)now=now*p1+b[i];
	for (i=1;i<=p;i++)
		for (j=1;j<=n;j++)
			hash[i][j]=hash[i][j-1]*p1+(a[j]==i);
	for (i=1;i<=n-m+1;i++)
	{
		num=0;sum=0;
		for (j=1;j<=p;j++)
		{
			x=get(j,i-1,i+m-1);
			if (x!=0)
			{
				num++;
				sum+=x*num;
			}
		}
		if (sum==now)A[++tot]=i;
	}
	printf("%d\n",tot);
	for (i=1;i<=tot;i++)printf("%d\n",A[i]);
}
