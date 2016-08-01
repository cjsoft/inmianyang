#include<cstdio>
#include<cstring>
using namespace std;
void IO(){
	freopen("pat.in","r",stdin);
	freopen("pat.out","w",stdout);
}
const int N=1e5+5,M=25005,K=26;
int n,m,p;
int a[N],b[M];
int pa[N][K],pb[M][K];
int fail[M];
int c[K],d[K];
bool ck(int *x,int u,int *y,int v){
	int num=0;
	for(int i=1;i<x[u];i++) num+=c[i];
	for(int i=1;i<y[v];i++) num-=d[i];
	return !num;
}
void getfail(){
	for(int i=2,j=0;i<=m;i++){
		d[b[i]]++;
		while(j && !ck(b,j+1,b,i)){
			for(int l=1;l<=p;l++){
				c[l]-=pb[j][l]-pb[fail[j]][l];
				d[l]-=pb[i-fail[j]][l]-pb[i-j][l];
			}
			j=fail[j];
		}
		if(ck(b,j+1,b,i)){
			j++;
			c[b[j]]++;
		}
		fail[i]=j;
	}
}
int ans[N],k;
void KMP(){
	getfail();
	memset(c,0,sizeof c);
	memset(d,0,sizeof d);
	for(int i=1,j=0;i<=n;i++){
		d[a[i]]++;
		while(j==m || (j && !ck(b,j+1,a,i))){
			for(int l=1;l<=p;l++){
				c[l]-=pb[j][l]-pb[fail[j]][l];
				d[l]-=pa[i-fail[j]][l]-pa[i-j][l];
			}
			j=fail[j];
		}
		if(ck(b,j+1,a,i)){
			j++;
			c[b[j]]++;
		}
		if(j==m) ans[++k]=i-m+1;
	}
}
void Init(){
	scanf("%d%d%d",&n,&m,&p);
	for(int i=1;i<=n;i++){
		scanf("%d",a+i);
		memcpy(pa[i],pa[i-1],sizeof pa[i]);
		pa[i][a[i]]++;
	}
	for(int i=1;i<=m;i++){
		scanf("%d",b+i);
		memcpy(pb[i],pb[i-1],sizeof pb[i]);
		pb[i][b[i]]++;
	}
}
int main(){
	IO();
	Init();
	KMP();
	printf("%d\n",k);
	for(int i=1;i<=k;i++) printf("%d\n",ans[i]);
	return 0;
}
