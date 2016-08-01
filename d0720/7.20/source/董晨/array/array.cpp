#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define N 100005
int n,m,k,l,t,s,ans,x,y;
int f[N],a[N],b[N],c[N],flag[N];
int que(int l,int r,int x){
	if(l==r)return l;
	int mid=l+r>>1;
	if(f[mid]<x)return que(mid+1,r,x);
	else return que(l,mid,x);
}
int main(){
	freopen("array.in","r",stdin);
	freopen("array.out","w",stdout);
	scanf("%d%d%d",&n,&m,&k);
	for (int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		flag[a[i]]=1;
	}
	m=0;
	for (int i=1;i<=100000;i++)if(flag[i])m++;
	if(k>=m){printf("%d\n",m);return 0;}
	for (int i=1;i<=m+1;i++)f[i]=100000000;
	for (int j=1;j<=k;j++)
		for (int i=1;i<=n;i++){
			t=que(1,ans+1,a[i]);
			ans=max(ans,t);
			f[t]=a[i];
		}
	printf("%d\n",ans);
}
