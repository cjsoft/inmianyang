/**
 * @author SCaffrey (srius.caffrey@gmail.com)
 * www.lydsy.com:808/JudgeOnline/problem.php?id=4337
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

int T;
int n, x;
int mx;
struct edge {
	int t, x;
} e[233];
int head[233], cnt = 1;
inline void add(int s, int t) {
	e[++cnt].t = t; e[cnt].x = head[s]; head[s] = cnt;
	e[++cnt].t = s; e[cnt].x = head[t]; head[t] = cnt;
}
std::string h[55], q[55], val[55];
int sz[55], f[55];
void findRoot(int x, int y) {
	sz[x] = 1; f[x] = 0;
	for (int i = head[x]; i; i = e[i].x) if (e[i].t != y) {
		findRoot(e[i].t, x);
		sz[x] += sz[e[i].t];
		if (sz[e[i].t] > f[x]) f[x] = sz[e[i].t];
	}
	if (n - sz[x] > f[x]) f[x] = n - sz[x];
	if (f[x] < mx) mx = f[x];
}
void dfs(int x, int y) {
	h[x] = "(";
	for (int i = head[x]; i; i = e[i].x) if (e[i].t != y) dfs(e[i].t, x);
	int t = 0;
	for (int i = head[x]; i; i = e[i].x) if (e[i].t != y) q[t++] = h[e[i].t];
	if (t > 1) std::sort(q, q + t);
	f(i, 0, t) h[x] += q[i];
	h[x] += ")";
}
std::string solve() {
	std::string t = "";
	scanf("%d", &n);
	cnt = 1;
	mx = n;
	g(i, 1, n) head[i] = 0;
	g(i, 1, n) {
		read(x);
		if (x) add(i, x);
	}
	findRoot(1, 0);
	g(i, 1, n) if (f[i] == mx) {
		dfs(i, 0);
		if (h[i] > t) t = h[i];
	}
	return t;
}
int k;
int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

	scanf("%d", &T);
	g(i, 1, T) val[i] = solve();
	g(i, 1, T) {
		k = i;
		g(j, 1, i) if (val[j] == val[i]) {
			k = j;
			break;
		}
		printf("%d\n", k);
	}

#ifdef LOCAL
  fclose(stdin);
  fclose(stdout);
#endif
  return 0;
}


