#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>

using namespace std;

int n,m,p,mm;
int s1[100005],s2[25005];
bool fi(int x)
{
	for(int i=1;i<=m;++i)
		if(s2[i]==x) 
			return 1;
	return 0;
}
struct A{
	A *to[2],*fail;
	int w;
}ac[630005],*root;int topa;
A *node()
{
	++topa;ac[topa].to[0]=ac[topa].to[1]=0;
	ac[topa].w=0;
	return &ac[topa];
}
void ins(A *&wz,int t,int i)
{
	if(!wz) wz=node();
	if(i>m) 
	{
		wz->w=mm;
		return ;
	}
	if(s2[i]==t) ins(wz->to[1],t,i+1);
	else ins(wz->to[0],t,i+1);
}
queue<A*> que;

void build()
{
	root->fail=root;
	if(root->to[0])
	{
		que.push(root->to[0]);
		root->to[0]->fail=root;
	}
	else root->to[0]=root;
	if(root->to[1])
	{
		que.push(root->to[1]);
		root->to[1]->fail=root;
	}
	else root->to[1]=root;
	A *wz;
	while(!que.empty())
	{
		wz=que.front();que.pop();
		if(wz->to[0])
		{
			que.push(wz->to[0]);
			wz->to[0]->fail=wz->fail->to[0];
		}
		else wz->to[0]=wz->fail->to[0];
		if(wz->to[1])
		{
			que.push(wz->to[1]);
			wz->to[1]->fail=wz->fail->to[1];
		}
		else wz->to[1]=wz->fail->to[1];
	}
}
int pp[100005],ans=0;

void find(A *wz,int t,int i)
{
	if(i-m>0&&wz->w==pp[i-m]+1)
		pp[i-m]++;	
	if(i>n) return ;
	if(s1[i]==t) find(wz->to[1],t,i+1);
	else find(wz->to[0],t,i+1);
	return ;
}

int main()
{
	freopen("pat.in","r",stdin);
	freopen("pat.out","w",stdout);
	scanf("%d%d%d",&n,&m,&p);
	for(int i=1;i<=n;++i)
		scanf("%d",&s1[i]);
	for(int i=1;i<=m;++i)
		scanf("%d",&s2[i]);
	mm=0;
	for(int i=1;i<=p;++i)
	if(fi(i))
	{
		mm++;
		ins(root,i,1);
	}
	build();
	for(int i=1;i<=p;++i)
		find(root,i,1);
	for(int i=1;i<=n;++i)
		if(pp[i]==mm)
			ans++;
	printf("%d\n",ans);
	for(int i=1;i<=n;++i)
		if(pp[i]==mm)
			printf("%d\n",i);
	return 0;
}

