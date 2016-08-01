#include<cstdio>
#include<map>
#define MG make_pair
using namespace std;
typedef long long ll;
struct node{int x,y,z;}q[5000010];
int l,r,p,p1,p2,A,B,ans,f[110];
int prime[25]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
map<int,int> mp;
map<pair<int,int>,int> flag;
int main()
{
	freopen("calc.in","r",stdin);
	freopen("calc.out","w",stdout);
	scanf("%d%d%d",&l,&r,&p);
	p1=0;p2=1;q[1].x=1;q[1].y=0;q[1].z=0;mp[1]=1;
	flag[MG(1,0)]=1;
	while (p1<p2)
	{
		p1++;
		if (q[p1].z>=p) break;
		A=q[p1].x;B=q[p1].y;
		if ((ll)A*(B+1)<=r&&!flag[MG(A,B+1)])
		{
			flag[MG(A,B+1)]=1;
			q[++p2].x=A;q[p2].y=B+1;q[p2].z=q[p1].z+1;
		}
		if ((ll)A*B<=r&&!flag[MG(A*B,B)])
		{
			flag[MG(A*B,B)]=1;
			q[++p2].x=A*B;
			q[p2].y=B;
			q[p2].z=q[p1].z+1;
			if (!mp[A*B]){mp[A*B]=1;if (A*B>=l) ans++;}
		}
	}
	printf("%d\n",ans);
}
