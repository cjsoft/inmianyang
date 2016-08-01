#include <cstdio>

typedef long long ll;

int l, r, p, ans = 0;
bool vis[1000005];

void DFS(ll a, ll b, int t) {
	if (a > r || t > p) return;
	ans += (vis[a] == 0 && a >= l && a <= r); vis[a] = 1;
	DFS(a * b, b, t + 1);
	DFS(a, b + 1, t + 1);
}

int main() {
#ifndef LOCAL
	freopen("calc.in", "r", stdin), freopen("calc.out", "w", stdout);
#endif

	scanf("%d%d%d", &l, &r, &p);
	DFS(1, 0, 0);

	return printf("%d\n", ans), 0;
}
