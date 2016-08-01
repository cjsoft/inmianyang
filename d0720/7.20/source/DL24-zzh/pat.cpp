#include<cstdio>
#include<algorithm>

int n,m,p;
int a[1100000],b[1100000];
int s[1100000],top;

int cmp(int a,int b){
	if (a<b) return 0;
	if (a==b) return 1;
	return 2;
}

bool ok(int *a){
	for (int i=1;i<m;i++) for (int j=0;j<i;j++) if (cmp(a[i],a[j]) != cmp(b[i],b[j])) return false;
	return true;
}



int main(){
	freopen("pat.in","r",stdin);
	freopen("pat.out","w",stdout);
	scanf("%d%d%d",&n,&m,&p);
	for (int i=0;i<n;i++) scanf("%d",a+i);
	for (int i=0;i<m;i++) scanf("%d",b+i);
	top=0;
	for (int i=0;i<=n-m;i++) if (ok(a+i)) s[++top]=i+1;
	printf("%d\n",top);
	for (int i=1;i<=top;i++) printf("%d\n",s[i]);
	return 0;
}

