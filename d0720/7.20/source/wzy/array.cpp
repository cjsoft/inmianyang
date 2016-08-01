#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
void IO(){
	freopen("array.in","r",stdin);
	freopen("array.out","w",stdout);
}
const int N=1e5+5,K=5e7+5;
int n,m,r,t;
int a[N],pos[N];
bool comp(int x,int y){return a[x]<a[y];}
int f[K],g[K];
inline int idx(int u,int v){return (u-1)*m+v;}
int c[N];
void Add(int p,int x){
	for(;p<=m;p+=p&-p) c[p]=max(c[p],x);
}
int Query(int p){
	int ans=0;
	for(;p;p-=p&-p) ans=max(ans,c[p]);
	return ans;
}
int left[N];
int mx[N];
void DP(){
	for(int i=1;i<=r;i++){
		for(int j=1;j<=m;j++){
			int k=idx(i,j);
			f[k]=g[idx(i-1,j-1)]+1;
			g[k]=max(g[idx(i,j-1)],f[k]);
		}
		memset(c,0,sizeof(int)*(m+1));
		for(int j=1;j<=n;j++){
			int k=idx(i,a[j]);
			f[k]=max(f[k],Query(a[j]-1)+1);
			g[k]=max(g[k],f[k]);
			Add(a[j],f[k]);
		}
	}
}
void Init(){
	scanf("%d%*d%d",&n,&t);
	for(int i=1;i<=n;i++) scanf("%d",a+i),pos[i]=i;
	sort(pos+1,pos+n+1,comp);
	for(int i=1;i<=n;i++){
		if(a[pos[i-1]]!=a[pos[i]]) m++;
		a[pos[i]]=m;
	}
	r=min(m,t);
}
int main(){
	IO();
	Init();
	DP();
	int ans=0;
	for(int i=1;i<=m;i++) ans=max(ans,f[idx(r,i)]);
	printf("%d\n",ans);
	return 0;
}
