#include<cstdio>
#include<algorithm>
using namespace std;
typedef unsigned long long ull;
int n,m,p,tot;
int a[100010],b[25010],P[25010],s[30],Ans[100010];
ull Hash,mi,HH,H[30][100010];
int main()
{
	freopen("pat.in","r",stdin);
	freopen("pat.out","w",stdout);
	scanf("%d%d%d",&n,&m,&p);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	for (int i=1;i<=m;i++){scanf("%d",&b[i]);P[i]=b[i];}
	sort(P+1,P+m+1);
	tot=unique(P+1,P+m+1)-P-1;
	for (int i=1;i<=m;i++) b[i]=lower_bound(P+1,P+tot+1,b[i])-P;
	for (int i=1;i<=m;i++) Hash=Hash*6662333+b[i];
	for (int i=1;i<=p;i++)
		for (int j=1;j<=n;j++) H[i][j]=H[i][j-1]*6662333+(a[j]==i);
	for (int i=1;i<m;i++)
		s[a[i]]++;
	mi=1;for (int i=1;i<=m;i++) mi=mi*6662333;
	for (int i=m;i<=n;i++)
	{
		s[a[i]]++;s[a[i-m]]--;
		int tot=0;
		HH=0;
		for (int j=1;j<=p;j++) if (s[j])
		{
			tot++;
			HH+=(ull)tot*(H[j][i]-H[j][i-m]*mi);
		}
		if (HH==Hash) Ans[++Ans[0]]=i-m+1;
	}
	printf("%d\n",Ans[0]);
	for (int i=1;i<=Ans[0];i++) printf("%d\n",Ans[i]);
}
