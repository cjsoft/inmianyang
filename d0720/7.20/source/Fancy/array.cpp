#include <algorithm>
#include <iostream>
#include <cstdio>
#include <queue>
const int N=100005;
int n,m,T,ans,a[N],c[N];
std::pair<int,int> b[N];
inline bool Add(int x,int v)
{
	ans=std::max(ans,v);
	bool tag=0;
	for(;x<=m;x+=x&-x) if(v>c[x]) c[x]=v,tag=1;
	return tag;
}
inline int Query(int x)
{
	int answer=0;
	for(;x;x-=x&-x) answer=std::max(answer,c[x]);
	return answer;
}
int main()
{
	freopen("array.in","r",stdin);
	freopen("array.out","w",stdout);
	scanf("%d%d%d",&n,&m,&T);m=0;
	for(int i=1;i<=n;i++) scanf("%d",&b[i].first),b[i].second=i;
	std::sort(b+1,b+n+1);
	for(int i=1;i<=n;a[b[i].second]=m,i++)
		if(b[i].first!=b[i-1].first) m++;
	for(int t=1;t<=T;t++)
	{
		bool tag=0;
		for(int i=1;i<=n;i++)
			tag|=Add(a[i],Query(a[i]-1)+1);
		if(!tag) break;
	}
	printf("%d\n",ans);
}
