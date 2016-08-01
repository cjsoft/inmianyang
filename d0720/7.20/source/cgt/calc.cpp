#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define N 1000005
using namespace std;
int l,r,p,i,ans,flag[N];
void dfs(int A,int B,int k)
{
	if (A==0)return;
	if (A>r)return;
	flag[A]=1;
	if (k>p)return;
	dfs(A*B,B,k+1);
	dfs(A,B+1,k+1);
}
int main()
{
	freopen("calc.in","r",stdin);
	freopen("calc.out","w",stdout);
	scanf("%d%d%d",&l,&r,&p);
	dfs(1,0,1);
	for (i=l;i<=r;i++)ans+=flag[i];
	printf("%d\n",ans);
}
