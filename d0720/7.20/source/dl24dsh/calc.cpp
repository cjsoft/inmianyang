#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<map>
#include<cmath>
using namespace std;


struct pr{
	long long l,r;
	bool operator <(const pr& a) const{
		if (l<a.l) return 1;
		else if (l==a.l) return r<a.r;
	}
};
map<pr,bool>was;
map<int,bool>s;

int l,r,p;
int ans;

void dfs(int a,int b,int deep){
	if (a>r||b>r||deep>p||a==0) return;
	if (was[(pr){a,b}]) return;
	was[(pr){a,b}]=1;
	if (a>=l&&a<=r&&!s[a]){
		s[a]=1;
		ans++;
	}
	dfs(a*b,b,deep+1);
	dfs(a,b+1,deep+1);
}

int main(){
	freopen ("calc.in","r",stdin);
	freopen ("calc.out","w",stdout);
	cin>>l>>r>>p;
	dfs(1,0,1);
	cout<<ans<<endl;
	
	
	return 0;
}











