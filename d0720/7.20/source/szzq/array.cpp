#include <cstdio>
#include <algorithm>

#define __advance __attribute__((optimize("O2")))
#define Max(x, y) if (x < y) x = y

int n, m, t, a[100005], sorted[100005];

namespace BIT {
	int c[100005];

#define lowbit(x) ((x) & -(x))

	__advance void modify(int pos, int val) {
		for (int i = pos; i <= m; i += lowbit(i))
			Max(c[i], val);
	}

	__advance int query(int pos) {
		int ret = 0;
		for (int i = pos; i > 0; i -= lowbit(i))
			Max(ret, c[i]);
		return ret;
	}
}

__advance int main() {
#ifndef LOCAL
	freopen("array.in", "r", stdin), freopen("array.out", "w", stdout);
#endif

	scanf("%d%d%d", &n, &m, &t);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		sorted[i] = a[i];
	}
	std::sort(sorted + 1, sorted + n + 1);
	m = std::unique(sorted + 1, sorted + n + 1) - sorted - 1;

	if (t >= m) return printf("%d\n", m), 0;

	for (int i = 1; i <= n; ++i) a[i] = std::lower_bound(sorted + 1, sorted + m + 1, a[i]) - sorted;
	int ans = t, dpnow;
	while (t--) {
		for (int i = 1; i <= n; ++i) {
			dpnow = BIT::query(a[i] - 1) + 1;
			Max(ans, dpnow);
			BIT::modify(a[i], dpnow);
		}
	}

	return printf("%d\n", ans), 0;
}
