#include <cstdio>
#include <queue>
#include <map>
int L,R,P,ans;
std::pair<int,int> x,y;
std::queue<std::pair<int,int> > Q[2];
std::map<std::pair<int,int>,bool> vis;
std::map<int,bool> used;
int main()
{
	freopen("calc.in","r",stdin);
	freopen("calc.out","w",stdout);
	scanf("%d%d%d",&L,&R,&P);
	vis[std::make_pair(1,0)]=1;
	Q[1].push(std::make_pair(1,0));
	for(int i=1,t=0;i<=P;i++,t=!t)
		while(!Q[!t].empty())
		{
			x=y=Q[!t].front();Q[!t].pop();
			x.second++;
			if(!vis[x]) vis[x]=1,Q[t].push(x);
			if((long long)y.first*y.second<=R)
			{
				y.first*=y.second;
				if(!vis[y]) vis[y]=1,Q[t].push(y);
				if(y.first>=L&&!used[y.first]) used[y.first]=1,ans++;
			}
		}
	printf("%d\n",ans);
}
