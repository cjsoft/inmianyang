#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define N 2000005
using namespace std;
int i,n,m,t,l,r,mid,ans,pp;
int p[N],a[N];
int main()
{
	freopen("array.in","r",stdin);
	freopen("array.out","w",stdout);
	scanf("%d%d%d",&n,&m,&t);
	for (i=1;i<=n;i++)scanf("%d",&a[i]);
	if (n*t<=2000000)
	{
		for (i=n+1;i<=n*t;i++)
			a[i]=a[i-n];
		n=n*t;
		for (i=1;i<=n;i++)p[i]=1e9;
		//for (i=1;i<=n;i++)printf("%d ",a[i]);puts("");
		for (i=1;i<=n;i++)
		{
			l=1;r=i;
			while (l<r)
			{
				mid=(l+r)/2;
				if (p[mid]<a[i])
					l=mid+1;else r=mid;
			}
			p[l]=a[i];
		}
		//for (i=1;i<=n;i++)printf("%d ",p[i]);puts("");
		for (i=n;i;i--)
			if (p[i]!=1e9)
			{
				printf("%d\n",i);
				return 0;
			}
	}else
	{
		pp=0;
		for (i=2;i<=n;i++)
			if (a[i-1]<a[i]){pp=1;break;}
		if (!pp){printf("%d\n",t);return 0;}
		sort(a+1,a+1+n);
		ans=n;
		for (i=2;i<=n;i++)
			if (a[i]==a[i-1])ans--;
		printf("%d\n",ans);
	}
}
