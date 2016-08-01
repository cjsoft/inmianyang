#include<cstdio>
#include<cstring>

long long a,b;
int l,r,p;
bool vis[1100000];

void dfs(int now){
	if (now==p+1) return;
	vis[a]=true;
	++b;
	dfs(now+1);
	--b;
	if (a*b<=r && b!=0){
		a*=b;
		dfs(now+1);
		a/=b;
	}
}

int main(){
	freopen("calc.in","r",stdin);
	freopen("calc.out","w",stdout);
	memset(vis,false,sizeof(vis));
	scanf("%d%d%d",&l,&r,&p);
	a=1;b=0;
	dfs(1);
	int cnt=0;
	for (int i=l;i<=r;i++) if (vis[i]) ++cnt;
	printf("%d\n",cnt);
	return 0;
}
