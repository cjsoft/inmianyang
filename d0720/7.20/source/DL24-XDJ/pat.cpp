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

int n, m, A;
int a[100033], b[25033];
inline void read(int &x) {
	x = 0;
	char c = getchar();
	while (c < '0' || c > '9') c = getchar();
	while (c >= '0' && c <= '9') {
		x = (x << 3) + (x << 1) + c - 48;
		c = getchar();
	}
}
int res[100033], num;
char t[100033], p[25033];
int d[100033];
void solve() {
	f(i, 1, n) {
		if (a[i] > a[i - 1]) t[i - 1] = '>';
		else if (a[i] == a[i - 1]) t[i - 1] = '=';
		else t[i - 1] = '<';
	}
	t[n - 1] = '\0';
//	puts(t);
	f(i, 1, m) {
		if (b[i] > b[i - 1]) p[i - 1] = '>';
		else if (b[i] == b[i - 1]) p[i - 1] = '=';
		else p[i - 1] = '<';
	}
	p[m - 1] = '\0';
//	puts(p);
	d[1] = 0;
	int j;
	f(i, 1, m - 1) {
		j = d[i];
		while (j && p[i] != p[j]) j = d[j];
		if (p[i] == p[j]) d[i + 1] = j + 1;
		else d[i + 1] = 0;
	}
	num = 0;
	j = 0;
	f(i, 0, n - 1) {
		while (j && t[i] != p[j]) j = d[j];
		if (t[i] == p[j]) ++j;
		if (j == m - 1) {
			res[num++] = i - j + 2;
		}
	}
	printf("%d\n", num);
	f(i, 0, num) printf("%d\n", res[i]);
}
int main() {
#ifndef LOCAL
  freopen("pat.in", "r", stdin);
  freopen("pat.out", "w", stdout);
#endif

	read(n); read(m); read(A);
	f(i, 0, n) read(a[i]);
	f(i, 0, m) read(b[i]);
	solve();

#ifndef LOCAL
  fclose(stdin);
  fclose(stdout);
#endif
  return 0;
}


