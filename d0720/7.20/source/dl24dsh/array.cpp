#include<cstdio>
#include<iostream>
#include<vector>
using namespace std;

int seq[300001];
int n,m,t,l,r,mid;
vector<int>sum;

#define now sum.size()-1

int main(){
	freopen ("array.in","r",stdin);
	freopen ("array.out","w",stdout);
	ios::sync_with_stdio(false);
	cin>>n>>m>>t;
	for (int i=1;i<=n;i++){
		cin>>seq[i];
	}
	for (int i=1;i<t;i++){
		for (int j=1;j<=n;j++){
			seq[i*n+j]=seq[j];
		}
	}
	
	n=n*t;
	
	sum.push_back(seq[1]);
	
	for (int i=2;i<=n;i++){
		//cout<<seq[i]<<" ";
		if (seq[i]>sum[now]) sum.push_back(seq[i]);
		else{
			l=0;
			r=now;
			while (l<r){
				mid=(l+r)/2;
				if (sum[mid]<seq[i]) l=mid+1;
				else r=mid;
			}
			sum[l]=seq[i];
		}
	}
	cout<<now+1<<endl;
	
	return 0;
}











