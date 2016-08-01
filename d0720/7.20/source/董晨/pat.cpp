#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define N 100005
#define M 666233
#define P 6662333
#define ll unsigned long long
int n,m,k,l,t,s,ans,x,y;
int a[N],b[N],c[N],p[30],flag[30];
ll f[26][N],g[26][N],h[N],K;
ll que(int x,int l,int r){
	return f[x][r]-f[x][l-1]*h[m];
}
int main(){
	freopen("pat.in","r",stdin);
	freopen("pat.out","w",stdout);
	scanf("%d%d%d",&n,&m,&k);
	for (int i=1;i<=n;i++)scanf("%d",&a[i]);
	for (int i=1;i<=m;i++)scanf("%d",&b[i]);
	h[0]=1;
	for (int i=1;i<=n;i++)h[i]=h[i-1]*M;
	for (int j=1;j<=k;j++)
		for (int i=1;i<=n;i++)f[j][i]=f[j][i-1]*M+(a[i]==j); // 对a做j出现过的位置进行hash
	for (int i=1;i<=m;i++)flag[b[i]]=1;
	for (int i=1;i<=k;i++)
		if(flag[i])p[i]=++t; // 对b做离散化
	for (int j=1;j<=k;j++)
		for (int i=1;i<=m;i++)g[j][i]=g[j][i-1]*M+(p[b[i]]==j); // 对b做j出现过的位置进行hash
	K=1;
	for (int i=1;i<=t;i++)K=K*P+g[i][m]*i; // 再做一次hash？
	memset(flag,0,sizeof(flag));
	for (int i=1;i<m;i++)flag[a[i]]++; // a和b放在一起
	for (int i=m;i<=n;i++){
		flag[a[i]]++;
		flag[a[i-m]]--; // 字符串向后移动一下
		t=0;
		ll w=1;
		for (int j=1;j<=k;j++)if(flag[j]){
			t++;
			w=w*P+que(j,i-m+1,i)*t;
		}
		if(w==K)c[++ans]=i-m+1;
	}
	printf("%d\n",ans);
	for (int i=1;i<=ans;i++)printf("%d\n",c[i]);
}
