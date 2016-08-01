#include <cstdio>
#include <cstring>

#define f(x, y, z) for (int x = (y), __ = (z); x < __; ++x)
#define g(x, y, z) for (int x = (y), __ = (z); x <= __; ++x)
#define fd(x, y, z) for (int x = (y), __ = (z); x > __; --x)
#define gd(x, y, z) for (int x = (y), __ = (z); x >= __; --x)

typedef long long LL;
typedef long double real;

int l, r, p;
int pri[] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
int sz = 26;
int solve(int n, int k) {
	
}
int main() {
#ifndef LOCAL
  freopen("calc.in", "r", stdin);
  freopen("calc.out", "w", stdout);
#endif

	scanf("%d%d%d", &l, &r, &p);
	printf("%d\n", solve(r, p) - solve(l - 1, p));

#ifndef LOCAL
  fclose(stdin); fclose(stdout);
#endif
  return 0;
}
