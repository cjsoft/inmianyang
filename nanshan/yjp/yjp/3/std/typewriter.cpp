#include <cstdio>
#include <cstring>
#define f(x, y, z) for(int x = (y); x <= (z); ++x)
#define g(x, y, z) for(int x = (y); x < (z); ++x)
#define h(x, y, z) for(int x = (y); x >= (z); --x)

#define MOD 1000000007LL
typedef long long LL;
LL ans = 0;

struct node *nil;
struct node{
	int id; LL sid;
	node *son[26], *fail, *fa;
	inline void init(int _id = -1, node *_fa = nil){
		id = _id; sid = 0; fail = nil; fa = _fa;
		g(i, 0, 26) son[i] = nil;
	}
	inline void dfs(LL cans, node *root, node *tar){
		(cans += tar->sid) %= MOD;
		(ans += sid * cans) %= MOD;
		g(i, 0, 26) if(son[i] != nil){
			node *c = tar;
			while(c != root && c->son[i] == nil) c = c->fail;
			if(c->son[i] != nil) son[i]->dfs(cans, root, c->son[i]); else son[i]->dfs(cans, root, c);
		}
	}
} pool[600007], *cp = pool;
inline node *newnode(int _id = -1, node *_fa = nil){
	cp->init(_id, _fa); return cp++;
}

int qh, qt; node *que[300007];
struct Typewriter{
	node *p[300007], *root, *cp;
	int cid;
	inline void init(){
		root = newnode(); p[0] = cp = root;
		root->fa = root;
		cid = 0;
		int q; scanf("%d", &q);
		while(q--){
			int op; scanf("%d", &op);
			if(op == 1){
				char buf[4]; scanf("%s", buf);
				append(buf[0] - 'a');
			}else{
				int k; scanf("%d", &k);
				back(k);
			}
		}
	}
	inline void append(int x){
		node *&tar = cp->son[x];
		if(tar == nil) tar = newnode(x, cp);
		tar->sid += (++cid);
		p[cid] = cp = tar;
	}
	inline void back(int k){
		node *tar = p[k];
		tar->sid += (++cid);
		p[cid] = cp = tar;
	}
	inline void build_automaton(){
		qh = qt = 0; que[0] = root;
		while(qh <= qt){
			node *x = que[qh];
			if(x->fa == root) x->fail = root;
			else{
				node *c = x->fa->fail;
				while(c != root && c->son[x->id] == nil) c = c->fail;
				if(c->son[x->id] == nil) x->fail = root; else x->fail = c->son[x->id];
			}
			g(i, 0, 26) if(x->son[i] != nil) que[++qt] = x->son[i];
			if(x != root) (x->sid += x->fail->sid) %= MOD;
			++qh;
		}
	}
	inline void dfs(node *other_root){
		root->dfs(0, other_root, other_root);
	}
} A, B;

int main(){
	freopen("typewriter.in", "r", stdin);
	freopen("typewriter.out", "w", stdout);
	nil = newnode(); nil->init();
	A.init(); B.init();
	A.build_automaton(); B.dfs(A.root);
	printf("%I64d\n", ans);
	return 0;
}
