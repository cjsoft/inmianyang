#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>
#define f(x, y, z) for(int x = (y); x <= (z); ++x)
inline int min(int x, int y){return x < y ? x : y;}

class node{
public:
	int sum;
	node *Q, *W, *A, *S;
	inline node(){sum = 0; Q = W = A = S = NULL;}
	inline node *Q_();
	inline node *W_();
	inline node *A_();
	inline node *S_();
	inline void gsum(int, int, int, int);
} pool[150000], *cp = pool;

#define nodedef(name, attr) inline node *node::name(){if(!attr) attr = cp++; return attr;}
nodedef(Q_, Q)
nodedef(W_, W)
nodedef(A_, A)
nodedef(S_, S)

inline void inc(node *root, int x1, int y1, int x2, int y2, int cx, int cy, int dz){
	while(x1 != x2 || y1 != y2){
		root->sum += dz;
		//printf("SUM %d %d %d %d = %d\n", x1, y1, x2, y2, root->sum);
		int mx = (x1 + x2) >> 1, my = (y1 + y2) >> 1;
		if(cx <= mx){
			x2 = mx;
			if(cy <= my) y2 = my, root = root->Q_();
			else y1 = my + 1, root = root->W_();
		}else{
			x1 = mx + 1;
			if(cy <= my) y2 = my, root = root->A_();
			else y1 = my + 1, root = root->S_();
		}
	}
	root->sum += dz;
	//printf("SUM %d %d %d %d = %d\n", x1, y1, x2, y2, root->sum);
}

int cx1, cx2, cy1, cy2;
#define cross(l1, r1, l2, r2) ((l1) <= (r2) && (l2) <= (r1))
int aans;
inline void node::gsum(int x1, int y1, int x2, int y2){
	//printf("GSUM %d %d %d %d\n", x1, y1, x2, y2);
	if(cx1 <= x1 && x2 <= cx2 && cy1 <= y1 && y2 <= cy2){aans += sum; return;}
	int mx = (x1 + x2) >> 1, my = (y1 + y2) >> 1;
	if(Q && Q->sum && cross(x1, mx, cx1, cx2) && cross(y1, my, cy1, cy2)) Q->gsum(x1, y1, mx, my);
	if(W && W->sum && cross(x1, mx, cx1, cx2) && cross(my + 1, y2, cy1, cy2)) W->gsum(x1, my + 1, mx, y2);
	if(A && A->sum && cross(mx + 1, x2, cx1, cx2) && cross(y1, my, cy1, cy2)) A->gsum(mx + 1, y1, x2, my);
	if(S && S->sum && cross(mx + 1, x2, cx1, cx2) && cross(my + 1, y2, cy1, cy2)) S->gsum(mx + 1, my + 1, x2, y2);
	//printf("GSUMX %d %d %d %d = %d\n", x1, y1, x2, y2, ans);
}

int n, tim = 0, mdep = 0;
std::vector<int> adj[100086];
int id[100086], dep[100086], id2[100086];

inline void dfs(int x){
	id[x] = ++tim;
	for(std::vector<int>::iterator it = adj[x].begin(), end = adj[x].end(); it != end; ++it){
		dep[*it] = dep[x] + 1;
		if(dep[*it] > mdep) mdep = dep[*it];
		dfs(*it);
	}
	id2[x] = tim;
}

struct DP{int id, dep, ran;} dp[100086];
inline bool operator <(const DP &x, const DP &y){
	return x.dep < y.dep || (x.dep == y.dep && x.ran < y.ran);
}
int dil[100086], dir[100086], di[100086];

int main(){
	freopen("unh.in", "r", stdin);
	freopen("unh.out", "w", stdout);
	srand(2345678);
	node *root = new node;
	int q;
	scanf("%d%d", &n, &q);
	f(i, 2, n){
		int cb; scanf("%d", &cb);
		adj[cb].push_back(i);
	}
	dep[1] = 1; dfs(1);
	f(i, 1, n) dp[i].id = i, dp[i].dep = dep[i], dp[i].ran = rand();
	std::sort(dp + 1, dp + n + 1);
	memset(dil, 0, sizeof(dil));
	f(i, 1, n){
		int cd = dp[i].dep;
		if(!dil[cd]) dil[cd] = i; dir[cd] = i;
		di[dp[i].id] = i;
	}
	dir[n] = n;
	f(i, 1, n) if(!dil[i]) dil[i] = (dir[i] = dir[i - 1]) + 1;
	while(q--){
		int cmd; scanf("%d", &cmd);
		if(cmd == 1){
			int w, e; scanf("%d%d", &w, &e);
			inc(root, 1, 1, n, n, di[w], id[w], e);
			printf("-1\n");
		}else{
			int w, e, r; scanf("%d%d%d", &w, &e, &r);
			aans = 0;
			cx1 = dil[min(dep[w] + e, n)]; cx2 = dir[min(dep[w] + r, n)]; cy1 = id[w]; cy2 = id2[w];
			root->gsum(1, 1, n, n);
			printf("%d\n", aans);
		}
	}
	return 0;
}
