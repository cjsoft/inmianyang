#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
#define N 1050000
#define ll long long
int n,m,k,l,t,s,tot,ans,r,x,y,p;
int flag[N],pri[N];
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
	freopen("baoli.out","w",stdout);
	scanf("%d%d%d",&l,&r,&p);
	dfs(1,1,0);
	for (int i=l;i<=r;i++)if(flag[i]){
		ans++;
		printf("%d\n",i);
	}
	printf("%d\n",ans);
}
