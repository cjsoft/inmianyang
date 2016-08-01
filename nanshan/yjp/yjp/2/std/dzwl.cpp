#include <cstdio>
#include <vector>
#define f(x, y, z) for(int x = (y); x <= (z); ++x)

std::vector<int> son[100086];
int n, m, w[100086];

inline double dfs(int x, int &t){
	if(x == n) return 0;
	else if(w[x] == 0){
		if(son[x].size() == 1){
			t = son[x][0]; return 0;
		}else{
			double ans1 = dfs(son[x][0], t), ans2 = dfs(son[x][1], t);
			return ans1 * ans2 / (ans1 + ans2) + dfs(t, t);
		}
	}else return dfs(son[x][0], t) + 1;
}

int main(){
	freopen("dzwl.in", "r", stdin);
	freopen("dzwl.out", "w", stdout);
	scanf("%d%d", &n, &m);
	while(m--){
		int a, b, c; scanf("%d%d%d", &a, &b, &c);
		son[a].push_back(b); w[a] = c;
	}
	int foo;
	printf("%.3lf\n", dfs(1, foo));
	return 0;
}
