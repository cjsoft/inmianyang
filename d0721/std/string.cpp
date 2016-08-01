#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
typedef unsigned long long ll;
const int N=100010,D=13331;
int T,n,m,i,j,k,x,y,A,B,L,ans,st,en;char a[N];ll pow[N],f[N];
inline ll hash(int l,int r){return f[r]-f[l-1]*pow[r-l+1];}
inline int min(int a,int b){return a<b?a:b;}
inline int lcp(int x,int y){
  if(a[x]!=a[y])return 0;
  int l=2,r=min(n-x,n-y)+1,mid,t=1;
  while(l<=r){
    mid=(l+r)>>1;
    if(hash(x,x+mid-1)==hash(y,y+mid-1))l=(t=mid)+1;else r=mid-1;
  }
  return t;
}
inline int lcs(int x,int y){
  int l=2,r=x,mid,t=1;
  while(l<=r){
    mid=(l+r)>>1;
    if(hash(x-mid+1,x)==hash(y-mid+1,y))l=(t=mid)+1;else r=mid-1;
  }
  return t;
}
inline void up(int x,int y){
  if(k>ans){ans=k,st=x,en=y;return;}
  int l0=en-st+1,l1=y-x+1,t=min(lcp(x,st),min(l0,l1));
  if((t<l1?a[x+t]:0)<(t<l0?a[st+t]:0))st=x,en=y;
}
int main(){
    freopen("string.in","r",stdin);
    freopen("string.out","w",stdout);
  scanf("%d",&T);
  for(pow[0]=i=1;i<N;i++)pow[i]=pow[i-1]*D;
  while(T--){
    scanf("%s",a+1);n=strlen(a+1);
    for(ans=i=st=en=1;i<=n;i++)if(a[i]<a[st])st=en=i;
    for(i=1;i<=n;i++)f[i]=f[i-1]*D+a[i];
    for(i=1;i+i<=n;i++)for(j=i;j<=n;j+=i){
      x=j+i;
      if(x>n)break;
      if(a[j]!=a[x])continue;
      A=lcp(j,x),B=lcs(j,x),k=(A+B-1)/i+1;
      if(k>=ans&&k>1)for(L=k*i,y=j-B+1;y+L<=i+j+A;y++)up(y,y+L-1);
    }
    for(i=st;i<=en;i++)putchar(a[i]);puts("");
  }
  return 0;
}
