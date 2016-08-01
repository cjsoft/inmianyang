#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
#define N 1000005
#define ll long long
int n,m,k,l,t,s,tot,ans,r,x,y,p;
int a[N],b[N],flag[N],pri[N];
bool shit(int s,int L){
	int l=L,r=p-1;
	for (int i=l;i<=r;i++)if(s%i==0){
		int k=0;
		int t=i,x=s;
		while(x>1){
			while(x%t==0){
				x/=t;
				k++;
			}
			t=min(x,t-1);
		}
		if(k+i<=p)return 1;
	}
	return 0;
}
void dfs(int x,int s,int y,int z){
	if(x>tot){
		k++;
		if(s>=l)if(shit(s,pri[z])){
			ans++;
		}
		return;
	}
	int t=1;
	int w=y/s,ww=z;
	for (int i=0;w/t>0;i++){
		a[x]=i;
		dfs(x+1,s*t,y,ww);
		t=t*pri[x];
		ww=x;
	}
}
void dfs(int x,int a,int b){
	if(a>r)return;
	if(x>p){
		flag[a]++;
		return;
	}
	dfs(x+1,a,b+1);
	dfs(x+1,a*b,b);
}
int main(){
	freopen("calc.in","r",stdin);
	freopen("calc.out","w",stdout);
	scanf("%d%d%d",&l,&r,&p);
	if(r<=1000000){
		dfs(1,1,0);
		for (int i=l;i<=r;i++)if(flag[i]){
			ans++;
		}
		printf("%d\n",ans);
		return 0;
	}
	flag[1]=1;
	for (int i=2;i<=p;i++)if(!flag[i]){
		pri[++tot]=i;
		for (int j=2;j<=p/i;j++)flag[i*j]=1;
	}
	dfs(1,1,r,0);
	printf("%d\n",ans);
}
