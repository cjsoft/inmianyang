/**
 * @author SCaffrey (srius.caffrey@gmail.com)
 * http://hihocoder.com/problemset/problem/1089
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

struct node {
	int t, w, x;
} e[MAXN * 20];
int head[MAXN], cnt = 1;
inline void add(int s, int t, int w) {
	e[++cnt].t = t; e[cnt].x = head[s]; head[s] = cnt; e[cnt].w = w;
	e[++cnt].t = s; e[cnt].x = head[t]; head[t] = cnt; e[cnt].w = w;
}
std::queue<int> Q;
int dis[MAXN];
int n, m;
int u, v, w;
bool bfs() {
	while (!Q.empty()) Q.pop();
	int x;
	Q.push(1);
	memset(dis, -1, sizeof dis);
	dis[1] = 0;
	while (!Q.empty()) {
		u = Q.front(); Q.pop();
		for (int i = head[u]; i; i = e[i].x) {
			if (e[i].w && dis[e[i].t] == -1) {
				dis[e[i].t] = dis[u] + 1;
				Q.push(e[i].t);
			}
		}
	}
	return dis[n] != -1;
}
int dfs(int x, int fl) {
	if (x == n) return fl;
	int w, used = 0;
	for (int i = head[x]; i; i = e[i].x) {
		if (e[i].w && dis[e[i].t] == dis[x] + 1) {
			w = dfs(e[i].t, std::min(fl - used, e[i].w));
			e[i].w -= w; e[i ^ 1].w += w; used += w;
			if (used == fl) return fl;
		}
	}
	if (!used) dis[x] = -1;
	return used;
}
void dinic() {
	int ans = 0;
	while (bfs()) ans += dfs(1, oo);
	printf("%d\n", ans);
}
int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

	while (~scanf("%d%d", &m, &n)) {
		memset(head, 0, sizeof head); cnt = 1;
		f(i, 0, m) {
			scanf("%d%d%d", &u, &v, &w);
			add(u, v, w);
		}
		dinic();
	}

#ifdef LOCAL
  fclose(stdin);
  fclose(stdout);
#endif
  return 0;
}


