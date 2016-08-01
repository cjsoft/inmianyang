#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <map>
#define f(x, y, z) for(int x = (y); x <= (z); ++x)
#define g(x, y, z) for(int x = (y); x < (z); ++x)
#define h(x, y, z) for(int x = (y); x >= (z); --x)
#define foreach(x, y) for(__typeof(y.begin()) x = y.begin(); x != y.end(); ++x)

int n, m, q, w[200086];
std::vector<int> adj[100086];

bool cut[100086], vis[100086];
int dep[100086], low[100086];

//non-recursive segment tree
struct SGT{
	int n, EX, *tree;
	inline SGT(){}
	inline SGT(int nn){
		n = nn; EX = 1;
		while(EX < n + 2) EX <<= 1;
		int treesize = sizeof(int) * (EX << 1);
		tree = (int *) malloc(treesize);
		memset(tree, 0x3f, treesize);
	}
	inline void chg(int x, int y){
		tree[x += EX] = y;
		for(x >>= 1; x; x >>= 1) tree[x] = std::min(tree[x << 1], tree[x << 1 | 1]);
	}
	inline int gmin(int l, int r){
		int ans = 0x3f3f3f3f;
		for(l += EX - 1, r += EX + 1; l ^ r ^ 1; l >>= 1, r >>= 1){
			if((!(l & 1)) && tree[l ^ 1] < ans) ans = tree[l ^ 1];
			if((r & 1) && tree[r ^ 1] < ans) ans = tree[r ^ 1];
		}
		return ans;
	}
	inline int gmin(){
		return gmin(1, n);
	}
};

//find all cut-vertices
inline void dfs_cut(int x, int fa){
	low[x] = dep[x] = dep[fa] + 1;
	int CN = 0;
	foreach(it, adj[x]){
		int t = *it;
		if(t == fa) continue;
		if(dep[t]){
			if(dep[t] < low[x]) low[x] = dep[t];
		}else{
			dfs_cut(t, x);
			++CN;
			if(low[t] < low[x]) low[x] = low[t];
		}
	}
	if(x == 1) cut[x] = (CN > 1); else{
		foreach(it, adj[x]){
			int t = *it;
			if(dep[t] == dep[x] + 1 && low[t] >= dep[x]){
				cut[x] = 1; break;
			}
		}
	}
}

int col_n = 0;
int col[100086], id[100086], n_col[100086];
SGT col_tree[100086], hld_tree[200086];

std::vector<int> treeson[200086];
int treedep[200086], treefa[18][200086], treesize[200086], hldfa[200086], hlddep[200086];

int st[200086], sn = 0;

//find all biconnected components and build the tree
//the son of a cut-vertex are blocks, and the son of blocks are all cut-vertices
//even if the block only contains a cut-vertex
inline void dfs_col(int x, int fa){
	low[x] = dep[x] = dep[fa] + 1;
	st[++sn] = x;
	foreach(it, adj[x]){
		int t = *it;
		if(t == fa) continue;
		int lsn = sn;
		if(dep[t]){
			if(dep[t] < low[x]) low[x] = dep[t];
		}else{
			dfs_col(t, x);
			if(low[t] < low[x]) low[x] = low[t];
		}
		if(low[t] >= dep[x] && sn > lsn){
			++col_n; n_col[col_n] = 0;
			treefa[0][col_n + 100008] = x;
			treeson[x].push_back(col_n + 100008);
			for(; sn > lsn; --sn){
				int c = st[sn];
				col[c] = col_n; id[c] = ++n_col[col_n];
				if(cut[c]){
					treefa[0][c] = col_n + 100008;
					treeson[col_n + 100008].push_back(c);
				}
			}
			col_tree[col_n] = SGT(n_col[col_n]);
		}
	}
}

//initialize heavy-light decomposition
inline void dfs_hld(int x){
	hldfa[x] = x; treedep[x] = treedep[treefa[0][x]] + 1;
	treesize[x] = 1;
	int msize = -1, mson;
	foreach(it, treeson[x]){
		int son = *it;
		dfs_hld(son);
		treesize[x] += treesize[son];
		if(treesize[son] > msize){
			msize = treesize[son];
			mson = son;
		}
	}
	if(msize > -1) hldfa[mson] = x;
}
inline void dfs_hld_2(int x){
	if(hldfa[x] != x) hldfa[x] = hldfa[hldfa[x]];
	hlddep[x] = 1;
	foreach(it, treeson[x]){
		int son = *it;
		dfs_hld_2(son);
		if(hldfa[son] != son) hlddep[x] = hlddep[son] + 1;
	}
	if(hldfa[x] == x) hld_tree[x] = SGT(hlddep[x]);
}

//lca, y is no deeper than x, t is the last node from x to LCA(x,y)
//if LCA(x,y)=y then t=y
inline int lca(int x, int y, int &t){
	int dx = treedep[x] - treedep[y];
	h(i, 17, 0) if(dx & (1 << i)) x = treefa[i][x];
	h(i, 17, 0) if(treefa[i][x] != treefa[i][y]){
		x = treefa[i][x]; y = treefa[i][y];
	}
	t = x;
	if(x == y) return x; else return treefa[0][x];
}

//query on the tree, y is on the path from x to root
inline int tree_query(int x, int y){
	int ans = 0x3f3f3f3f;
	while(hldfa[x] != hldfa[y]){
		int til = hldfa[x];
		ans = std::min(ans, hld_tree[til].gmin(1, treedep[x] - treedep[til] + 1));
		x = treefa[0][til];
	}
	int til = hldfa[x];
	return std::min(ans, hld_tree[til].gmin(treedep[y] - treedep[til] + 1, treedep[x] - treedep[til] + 1));
}

int main(){
	//read data
	freopen("tourist.in", "r", stdin);
	freopen("tourist.out", "w", stdout);
	scanf("%d%d%d", &n, &m, &q);
	f(i, 1, n) scanf("%d", w + i);
	while(m--){
		int a, b; scanf("%d%d", &a, &b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	//find cut-vertices, and let a cut-vertex be root
	memset(cut, 0, sizeof(cut));
	memset(dep, 0, sizeof(dep));
	dfs_cut(1, 0);
	int cut_n = 0, root;
	h(i, n, 1) if(cut[i]){
		++cut_n; root = i;
	}
	if(cut_n){
		//the graph is not biconnected, find the biconnected components
		memset(vis, 0, sizeof(vis));
		vis[root] = 1;
		treefa[0][root] = 0; treedep[root] = 1;
		memset(dep, 0, sizeof(dep));
		dfs_col(root, 0);
		//initialize LCA, HLD and segment tree
		//build virtual vertices for blocks (block_number+100008)
		f(j, 1, 17){
			f(i, 1, n) treefa[j][i] = treefa[j - 1][treefa[j - 1][i]];
			f(i, 1 + 100008, col_n + 100008) treefa[j][i] = treefa[j - 1][treefa[j - 1][i]];
		}
		f(i, 1, n) if(i != root) col_tree[col[i]].chg(id[i], w[i]);
		f(i, 1, col_n){
			w[i + 100008] = col_tree[i].gmin();
		}
		dfs_hld(root);
		dfs_hld_2(root);
		f(i, 1, col_n) hld_tree[hldfa[i + 100008]].chg(treedep[i + 100008] - treedep[hldfa[i + 100008]] + 1, w[i + 100008]);
		f(i, 1, n) if(cut[i]) hld_tree[hldfa[i]].chg(treedep[i] - treedep[hldfa[i]] + 1, w[i]);
		while(q--){
			char op[4]; int x, y; scanf("%s%d%d", op, &x, &y);
			if(op[0] == 'C'){
				//modify it in the block, then modify the block on the tree
				//remember the root does not belong to any block
				if(x != root){
					col_tree[col[x]].chg(id[x], w[x] = y);
					hld_tree[hldfa[col[x] + 100008]].chg(treedep[col[x] + 100008] - treedep[hldfa[col[x] + 100008]] + 1, w[col[x] + 100008] = col_tree[col[x]].gmin());
				}
				//modify the cut-vertex on the tree
				if(cut[x]) hld_tree[hldfa[x]].chg(treedep[x] - treedep[hldfa[x]] + 1, w[x] = y);
			}else if(x == y) printf("%d\n", w[x]);
			else{
				//find the block
				if(!cut[x]) x = col[x] + 100008;
				if(!cut[y]) y = col[y] + 100008;
				if(treedep[x] < treedep[y]) std::swap(x, y);
				int t; int l = lca(x, y, t);
				int ans = tree_query(x, t);
				if(l != y) ans = std::min(ans, tree_query(y, l));
				//if LCA is block, take its father into account
				if(l > 100004) ans = std::min(ans, w[treefa[0][l]]);
				printf("%d\n", ans);
			}
		}
	}else{
		//the graph is biconnected, simple task
		SGT tree(n);
		f(i, 1, n) tree.chg(i, w[i]);
		while(q--){
			char op[4]; int x, y; scanf("%s%d%d", op, &x, &y);
			if(op[0] == 'C') tree.chg(x, w[x] = y);
			else if(x == y) printf("%d\n", w[x]);
			else printf("%d\n", tree.gmin());
		}
	}
	return 0;
}
