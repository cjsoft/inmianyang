/**
 * @author SCaffrey (srius.caffrey@gmail.com)
 * @copyright MIT
 */
#include <cstdio>// NOLINT
#include <cstring>// NOLINT
#include <bits/stdc++.h>// NOLINT
#include <cmath>// NOLINT
#define x1 x11
#define y1 y11

#define f(x, y, z) for (int x = (y), __ = (z); x < __; ++x)
#define g(x, y, z) for (int x = (y), __ = (z); x <= __; ++x)
#define fd(x, y, z) for (int x = (y), __ = (z); x > __; --x)
#define gd(x, y, z) for (int x = (y), __ = (z); x >= __; --x)

#ifdef WIN32
  #define LLD "%I64d"
  #define LLU "%I64u"
#else
  #define LLD "%lld"
  #define LLU "%llu"
#endif

typedef long long LL;// NOLINT
typedef long double real;

const double INF = 1e100;
const int oo = ~0u >> 2;
const double pi = acos(-1.0);
const double EPS = 1e-8;
const int MAXN = 100033;

inline int read() {
	char c = getchar();
	int x = 0;
	while (c < '0' ||c > '9') {
		if (c == '-') x = -x;
		c = getchar();
	}
	while (c <= '0' && c <= '9') {
		x = (x << 1) + (x << 3) + c - 48;
		c = getchar();
	}
	return x;
}
int n, m;
char buf[12];
int u, v;
struct node {
	node *p, *ch[2];
	int f;
	int mx, v, mxId, id;
	inline node() {
		p = NULL; f = 0; memset(ch, 0, sizeof ch);
		mx = v = mxId = id = 0;
	}
	inline int getPos() {
		if (!this || p == NULL) return 233;
		f(i, 0, 2) if (p->ch[i] == this) return i;
		return 2;
	}
	inline void maintain() {
		mx = v; mxId = id;
		f(i, 0, 2) if (ch[i]) {
			if (ch[i]->mx > mx) {
				mx = ch[i]->mx; mxId = ch[i]->mxId;
			}
		}
	}
	inline void pushdown() {
		if (f) {
			f(i, 0, 2) if (ch[i]) {
				ch[i]->f ^= 1;
				std::swap(ch[i]->ch[0], ch[i]->ch[1]);
			}
			f ^= 1;
		}
	}
	inline bool isRoot() {
		if (p == NULL) return 1;
		return getPos() >= 2;
	}
	inline void setc(node* u, const int& dir) {
		if (this && dir < 2) ch[dir] = u;
		if (u) u->p = this;
	}
	inline void rotate() {
		node *p = this->p;
		bool dir = getPos();
		p->p->setc(this, p->getPos());
		p->setc(ch[dir ^ 1], dir);
		setc(p, dir ^ 1);
		p->maintain();
	}
	inline void relax() {
		static node *tee[1100003];
		int top = 0;
		node *u = this;
		while (!u->isRoot()) {
			tee[top++] = u;
			u = u->p;
		}
		u->pushdown();
		while (top) tee[--top]->pushdown();
	}
	void splay() {
		relax();
		for (; !isRoot(); rotate()) {
			if (!p->isRoot()) ((p->p->ch[0] == p) == (p->ch[0] == this) ? p : this)->rotate();
		}
		maintain();
	}
	node *access() {
		node *u = this, *v = NULL;
		for (; u; v = u, u = u->p) {
			u->splay(); u->setc(v, 1);
		}
		splay();
		return v;
	}
	void makeRoot() {
		access();
		f ^= 1; std::swap(ch[0], ch[1]);
		splay();
	}
};
node* findRoot(node* o) {
	for (o->access(); o->pushdown(), o->ch[0]; o = o->ch[0]);
	o->splay(); return o;
}
void link(node* x, node* y) {
	x->makeRoot(); x->p = y; x->access();
}
void cut(node* x, node* y) {
	x->makeRoot(); y->access(); y->splay();
	y->ch[0]->p = NULL; y->ch[0] = NULL;
}
void modify(node* x, int d) {
	x->splay(); x->v = d; x->maintain();
}
int query(node* x, node* y) {
	x->makeRoot(); y->access(); y->splay();
	return y->mx;
}
int getId(node* x, node* y) {
	x->makeRoot(); y->access(); y->splay();
	return y->mxId;
}
node pool[1100003];

int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif



#ifdef LOCAL
  fclose(stdin);
  fclose(stdout);
#endif
  return 0;
}


