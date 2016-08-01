#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>

using namespace std;

typedef long long ll;
typedef pair<int,int> pint;
int l,r,p;

int pri[105],topp;
bool isp(int x)
{
	for(int i=2;i*i<=x;++i)
		if(x%i==0) return 0;
	return 1;
}

queue <pint> que;
int ans=0;
int ys[30],topy;
bool jud(int x,int mp)
{
	for(int i=mp;i<=p;++i)
	{
		int w=x,an=i;
		for(int j=i;j>1;--j)
		{
			while(w%j==0)
			{
				w/=j,an++;
				if(an>p) break;
			}
			if(an>p||w==1) break;
		}
		if(an<=p&&w==1) return 1;
	}
	return 0;
}
int main()
{
	freopen("calc.in","r",stdin);
	freopen("calc.out","w",stdout);
	scanf("%d%d%d",&l,&r,&p);
	for(int i=2;i<=p;++i)
		if(isp(i))
			pri[++topp]=i;
	que.push(make_pair(1,1));
	pint Now;
	while(!que.empty())
	{
		Now=que.front();que.pop();
		for(int j=1;j<=topp;++j)
			if(Now.second<=pri[j]&&(ll)Now.first*pri[j]<=(ll)r) 
			{
				que.push(make_pair(Now.first*pri[j],pri[j]));
					if(Now.first*pri[j]>=l&&jud(Now.first*pri[j],pri[j]))
						ans++;	
			}
	}
	printf("%d",ans);
	return 0;
}

