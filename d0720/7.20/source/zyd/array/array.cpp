#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

const int N = 500000;
int n, m, T, a[N], f[N], g[N], ans, A[N];
int main()
{
	freopen("array.in", "r", stdin);
	freopen("array.out", "w", stdout);
	scanf("%d%d%d", &n, &m, &T);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]), A[i] = a[i];
	sort(A + 1, A + n + 1);
	A[0] = unique(A + 1, A + n + 1) - A - 1;
	for (int i = 1; i <= n; i++) a[i] = lower_bound(A + 1, A + A[0] + 1, a[i]) - A;
	m = A[0];
	T = min(T, m);
	memset(f, 0x3f, sizeof f);
	f[0] = 0;
	for (int i = 1; i <= m; i++) g[i] = 1;
	while (T--)
		for (int i = 1; i <= n; i++)
		{
			while (f[g[a[i]]] < a[i]) g[a[i]]++;
			ans = max(ans, g[a[i]]);
			f[g[a[i]]] = a[i];
		}
	printf("%d\n", ans);
}
