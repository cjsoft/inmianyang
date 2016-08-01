#include<cstdio>
#include<iostream>
#include<algorithm>
#include<map>
#include<vector>
#include<cstring>
using namespace std;

int next[100001];
int a[100001],tmp[100001],t2[100001],b[25001],ib[25001];
int la,lb,p,ta,tb,sum,ns;
map<int,int>lva;
map<int,int>lvb;
vector<int>sumseq;

void init(){
	freopen ("pat.in","r",stdin);
	freopen ("pat.out","w",stdout);
	ios::sync_with_stdio(false);
	
	cin>>la>>lb>>p;
	for (int i=1;i<=la;i++){
		cin>>a[i];
	}
	for (int i=1;i<=lb;i++){
		cin>>ib[i];
		b[i]=ib[i];
	}
	sort(ib+1,ib+lb+1);
	for (int i=1;i<=lb;i++){
		if (ib[i]!=ib[i-1]){
			tb++;
			lvb[ib[i]]=tb;
		}
	}
	for (int i=1;i<=lb;i++){
		b[i]=lvb[b[i]];
	}

}

bool once(int x){
	for (int i=x;i<=x+lb-1;i++){
		tmp[i-x+1]=a[i];
		t2[i-x+1]=tmp[i-x+1];
		//cout<<t2[i-x+1]<<" ";
	}
	//cout<<endl;
	//cout<<"---";
	
	sort(tmp+1,tmp+lb+1);

	ta=0;
	for (int i=1;i<=lb;i++){
		if (tmp[i]!=tmp[i-1]){
			ta++;
			lva[tmp[i]]=ta;
		}
	}
	for (int i=1;i<=lb;i++){
		t2[i]=lva[t2[i]];
		//cout<<x<<" "<<i<<" "<<t2[i]<<" "<<b[i]<<endl;
		if (t2[i]!=b[i]){
			//cout<<x<<" "<<i<<" "<<t2[i]<<" "<<b[i]<<endl;
			return 0;
		}
		//cout<<t2[i]<<" ";
	}
	
	//cout<<endl;
	return 1;
	//cout<<endl;
}

int kmp(int x[],int y[],int lx,int ly,int s){
	int now=s,t1=0;
	while (1){
		if (t1==0){
			for (int i=now;i<=lx;i++){
				if (x[i]==y[1]){
					t1=1;
					now=i;
					break;
				}
			}
		}

		if (t1==0) return -1;
		
		for (int i=now+1;i<=lx;i++){
			if (x[i]==y[t1+1]){
				t1++;
			}
			else break;
			if (t1==ly) break; 
		}
		if (t1==ly){
			return now;
		}
		else{
			//printf ("%d %d %d\n",now,t1,next[t1]);
			now+=t1-next[t1];
			t1=0;
		}
		if (now>lx-ly+1){
			return -1;
		}
	}
}

int main(){
	init();
	for (int i=1;i<=la-lb+1;i++){
		if (once(i)){
			sum++;
			sumseq.push_back(i);
		}
	}
	
	cout<<sum<<endl;
	for (int i=0;i<sum;i++) cout<<sumseq[i]<<endl;
	
	return 0;
}





