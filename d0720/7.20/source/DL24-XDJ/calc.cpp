#include <cstdio>
#include <cstring>

#define f(x, y, z) for (int x = (y), __ = (z); x < __; ++x)
#define g(x, y, z) for (int x = (y), __ = (z); x <= __; ++x)
#define fd(x, y, z) for (int x = (y), __ = (z); x > __; --x)
#define gd(x, y, z) for (int x = (y), __ = (z); x >= __; --x)

typedef long long LL;
typedef long double real;

int l, r, p;
int ans;
int pri[100033], cnt;
bool vis[100033];
void init() {
  f(i, 2, 100000) {
    if (!vis[i]) {
      pri[cnt++] = i;
    }
    f(j, 0, cnt) {
      if (i * pri[j] > 100000) break;
      vis[i * pri[j]] = 1;
      if (i % pri[j] == 0) break;
    }
  }
}
int calc(int x) {
  int res = 0, mx = 0;
  f(i, 0, cnt) if (x % pri[i] == 0) {
    mx = pri[i];
    while (x % pri[i] == 0) {
      x /= pri[i]; ++res;
    }
  }
  if (x > 1) ++res;
  return res;
}
int main() {
#ifndef LOCAL
  freopen("calc.in", "r", stdin);
  freopen("calc.out", "w", stdout);
#endif

  init();
  scanf("%d%d%d", &l, &r, &p);
  g(i, l, r) if (calc(i) <= p) ++ans;
  printf("%d\n", ans);

#ifndef LOCAL
  fclose(stdin); fclose(stdout);
#endif
  return 0;
}
