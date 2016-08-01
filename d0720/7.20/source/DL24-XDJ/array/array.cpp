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

inline void read(int &x) {
	char c = getchar(); x = 0;
	while (c < '0' || c > '9') c = getchar();
	while (c >= '0' && c <= '9') {
		x = (x << 3) + (x << 1) + c - 48;
		c = getchar();
	}
}
int n, m, t;
int b[100033];
int dp[300033];
void novice() {
	memset(dp, 0x1f, sizeof dp);
	int mx = dp[0];
	g(i, 1, t) {
		g(j, 1, n) {
			*std::lower_bound(dp + 1, dp + n * t + 1, b[j]) = b[j];
		}
	}
	int ans = 0;
	g(i, 1, n * t) if (dp[i] != mx) ans = i;
	else break;
	printf("%d\n", ans);
}
int c[100033];
void magic() {
	g(i, 1, n) c[i] = b[i];
	std::sort(c + 1, c + n + 1);
	int sz = std::unique(c + 1, c + n + 1) - c;
	if (sz <= t) {
		printf("%d\n", sz);
		return;
	}
	t = sz;
  novice();
}
int main() {
#ifndef LOCAL
  freopen("array.in", "r", stdin);
  freopen("array.out", "w", stdout);
#endif

//	scanf("%d%d%d", &n, &m, &t);
	read(n); read(m); read(t);
	g(i, 1, n) read(b[i]);
//	g(i, 1, n) scanf("%d", b + i);
	if ((LL)n * t <= 300000LL) novice();
	else magic();

#ifndef LOCAL
  fclose(stdin);
  fclose(stdout);
#endif
  return 0;
}


