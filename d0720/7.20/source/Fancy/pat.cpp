#include <algorithm>
#include <cstdio>
const int base=29,N=25005;
int n,m,P,tot,a[N<<2],b[N],c[N],d[26],sum[26],ans[N<<2];
unsigned long long A,B,hash[26],power[N]={1};
int main()
{
	freopen("pat.in","r",stdin);
	freopen("pat.out","w",stdout);
	scanf("%d%d%d",&n,&m,&P);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=m;i++) scanf("%d",&b[i]),c[i]=b[i],power[i]=power[i-1]*base;
	std::sort(c+1,c+m+1);
	for(int i=1,j=0;i<=m;i++)
		if(c[i]!=c[i-1]) d[c[i]]=++j;
	for(int i=1;i<=m;i++) B=B*base+d[b[i]];
	for(int i=1;i<=m;i++) hash[a[i]]+=power[m-i],sum[a[i]]++;
	for(int i=1;i+m-1<=n;i++,A=0)
	{
		if(i!=1)
		{
			hash[a[i-1]]-=power[m-1];sum[a[i-1]]--;
			for(int j=1;j<=P;j++) hash[j]*=base;
			hash[a[i+m-1]]++;sum[a[i+m-1]]++;
		}
		for(int j=1,k=0;j<=P;j++)
			if(sum[j])
				k++,A+=k*hash[j];
		if(A==B) ans[++tot]=i;
	}
	printf("%d\n",tot);
	for(int i=1;i<=tot;i++) printf("%d\n",ans[i]);
}
