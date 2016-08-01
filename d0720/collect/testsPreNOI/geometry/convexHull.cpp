/**
 * @author SCaffrey (srius.caffrey@gmail.com)
 * http://poj.org/problem?id=1113
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

struct point {
	int x, y;
	inline point(int x = 0, int y = 0):x(x), y(y) {}
};
inline point operator - (const point& a, const point& b) {
	return point(a.x - b., a.y - b.y);
}
inline int cross(const point& a, const point& b) {
	return a.x * b.y - a.y * b.x;
}
inline int dot(const point& a, const point& b) {
	return a.x * b.x + a.y * b.y;
}
inline int dis2(const point& a, const point& b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}
inline bool operator < (const point& a, const point& b) {
	return a.x < b.x || (a.x == b.x && a.y < b.y);
}
inline bool operator == (const point& a, const point& b) {
	return a.x == b.x && a.y == b.y;
}
std::vector<point> convexHull(std::vector<point>& p) {
	std::sort(p.begin(), p.end());
	p.erase(std::unique(p.begin(), p.end()), p.end());
	int n = p.size(), m = 0;
	std::vector<point> ch(n + 1);
	f(i, 0, n) {
		while (m > 1 && cross(ch[m - 1] - ch[m - 2], p[i] - ch[m - 2]) <= 0) --m;
		ch[m++] = p[i];
	}
	int k = m;
	gd(i, n - 2, 0) {
		while (m > k && cross(ch[m - 1] - ch[m - 2], p[i] - ch[m - 2]) <= 0) --m;
		ch[m++] = p[i];
	}
	if (n > 1) --m;
	ch.resize(m);
	return ch;
}
int n, l, x, y;
int getAns(std::vector<point> p) {
	double ans = 0;
	int sz = p.size();
	f(i, 0, sz) {
		ans += sqrt(double(dis2(p[i], p[(i + 1) % sz])));
	}
	ans += 2 * l * acos(-1.0);
	return ans + 0.5;
}
int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

	scanf("%d%d", &n, &l);
	std::vector<point> points;
	f(i, 0, n) {
		scanf("%d%d", &x, &y);
		points.push_back(point(x, y));
	}
	printf("%d\n", getAns(convexHull(points)));

#ifdef LOCAL
  fclose(stdin);
  fclose(stdout);
#endif
  return 0;
}


