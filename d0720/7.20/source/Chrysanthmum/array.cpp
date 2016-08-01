#include<cstdio>
#include<algorithm>
#define INF 1000000000
using namespace std;
int n,m,t,ans;
int a[100010],p[100010],g[100010],f[100010];
int main()
{
	freopen("array.in","r",stdin);
	freopen("array.out","w",stdout);
	scanf("%d%d%d",&n,&m,&t);t=min(t,m);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	for (int i=1;i<=n;i++) p[i]=a[i];
	sort(p+1,p+n+1);
	m=unique(p+1,p+n+1)-p-1;
	for (int i=1;i<=n;i++) a[i]=lower_bound(p+1,p+m+1,a[i])-p;
	for (int i=1;i<=m;i++) p[i]=INF;
	for (int i=1;i<=t;i++)
	{
		for (int j=1;j<=n;j++)
		{
			while (g[j]<m&&p[g[j]+1]<a[j]) g[j]++;
			ans=max(ans,g[j]+1);
			p[g[j]+1]=a[j];
		}
	}
	printf("%d\n",ans);
}
