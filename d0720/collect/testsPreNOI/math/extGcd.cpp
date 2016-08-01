/**
 * @author SCaffrey (srius.caffrey@gmail.com)
 * http://poj.org/problem?id=1061
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

int extGcd(int a, int b, LL &x, LL &y) {
	if (b == 0) {
		x = 1; y = 0; return a;
	}
	int res = extGcd(b, a % b, y, x);
	y -= a / b * x;
	return res;
}
LL x, y, m, n, l;
LL s, k, t, d, a, b;
LL gcd(LL x, LL y) {
	if (y) return gcd(y, x % y);
	return x;
}
int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

	
  while (scanf("%lld %lld %lld %lld %lld", &x, &y, &m, &n, &l) != EOF) {
		a = n - m; b = l; d = x - y;
		LL r = gcd(a, b);
		if (d % r) {
			puts("Impossible");
			continue;
		}
		a /= r; b /= r; d /= r;
		extGcd(a, b, s, k);
		s = s * d; k = k * d; t = s / b;
		s -= t * b;
		if (s < 0) s += b;
		printf("%lld\n", s);
	}

#ifdef LOCAL
  fclose(stdin);
  fclose(stdout);
#endif
  return 0;
}


