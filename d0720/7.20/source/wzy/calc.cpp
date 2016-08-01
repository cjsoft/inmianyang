#include<cstdio>
#include<algorithm>
using namespace std;
void IO(){
	freopen("calc.in","r",stdin);
	freopen("calc.out","w",stdout);
}
typedef long long ll;
const int N=3e6+5;
const int p[]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
int l,r,k;
ll mul;
int a[N],n;
void DFS(int u,int v){
	if(u>=25 || v<=0) return;
	for(int i=0;i<=v;i++){
		ll t=mul;
		if(i) a[++n]=mul;
		DFS(u+1,v-i-(p[u+1]-p[u]));
		mul=t*p[u];
		if(mul>r) break;
	}
}
void Init(){
	scanf("%d%d%d",&l,&r,&k);
}
int main(){
	IO();
	Init();
	mul=1;
	a[n=1]=1;
	DFS(0,k-2);
	sort(a+1,a+n+1);
	int ans=upper_bound(a+1,a+n+1,r)-a-1;
	ans-=lower_bound(a+1,a+n+1,l)-a-1;
	printf("%d\n",ans);
	return 0;
}
