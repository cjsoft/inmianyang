#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

const int N=100005;
int n,M,m,t;
int a[N],aa[N];
int ans=0;
int shu[N];
void add(int x,int w)
{
	while(x<=m)
	{
		shu[x]=max(shu[x],w);
		x+=x&(-x);
	}
}
int qur(int x)
{
	int an=0;
	while(x)
	{
		an=max(an,shu[x]);
		x-=x&(-x);
	}
	return an;
}
int main()
{
	freopen("array.in","r",stdin);
	freopen("array.out","w",stdout);
	scanf("%d%d%d",&n,&m,&t);
	for(int i=1;i<=n;++i)
	{
		scanf("%d",a+i);
		aa[i]=a[i];
	}
	sort(aa+1,aa+n+1);
	M=1;
	for(int i=2;i<=n;++i)
		if(aa[i]!=aa[i-1]) M++;
	if(t>=n||t>=M)
	{
		printf("%d",min(n,M));
		return 0;
	}
	int w;
	for(int i=1;i<=t;++i)
		for(int j=1;j<=n;++j)
		{
			w=qur(a[j]-1)+1;
			ans=max(ans,w);
			add(a[j],w);
		}
	printf("%d",ans);
	return 0;
}

