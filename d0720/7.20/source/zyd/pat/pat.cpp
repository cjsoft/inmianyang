#include <cstdio>
#include <algorithm>
using namespace std;
typedef unsigned long long ull;

const int N = 300000;
const ull BASE1 = 6662333, BASE2 = 1986202501;
int n, m, p;
int a[N], b[N], A[N];
ull ha1[N], ha2[N], mi1[N], mi2[N];
int vis[N], mir[N], ans[N];
int main()
{
	freopen("pat.in", "r", stdin);
	freopen("pat.out", "w", stdout);
	scanf("%d%d%d", &n, &m, &p);
	if (m > n)
	{
		puts("0");
		return 0;
	}
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= m; i++) scanf("%d", &b[i]), A[i] = b[i];
	sort(A + 1, A + m + 1);
	A[0] = unique(A + 1, A + m + 1) - A - 1;
	for (int i = 1; i <= m; i++) b[i] = lower_bound(A + 1, A + A[0] + 1, b[i]) - A;
	ull t2_1 = 0, t2_2 = 0;
	for (int i = 1; i <= m; i++)
		t2_1 = t2_1 * BASE1 + b[i];
	for (int i = 1; i <= m; i++)
		t2_2 = t2_2 * BASE2 + b[i];
	mi1[0] = 1; for (int i = 1; i <= n; i++) mi1[i] = mi1[i - 1] * BASE1;
	mi2[0] = 1; for (int i = 1; i <= n; i++) mi2[i] = mi2[i - 1] * BASE2;
	for (int i = 1; i <= m; i++)
	{
		vis[a[i]]++;
		ha1[a[i]] += mi1[m - i];
		ha2[a[i]] += mi2[m - i];
	}
	int cnt = 0;
	for (int j = 1; j <= p; j++)
		if (vis[j])
			mir[j] = ++cnt;
	ull t1_1 = 0, t1_2 = 0;
	for (int j = 1; j <= p; j++)
	{
		t1_1 += ha1[j] * mir[j];
		t1_2 += ha2[j] * mir[j];
	}
	if (t1_1 == t2_1 && t1_2 == t2_2)
		ans[++ans[0]] = 1;
	for (int i = 2; i <= n - m + 1; i++)
	{
		ull t1_1 = 0, t1_2 = 0;
		ha1[a[i - 1]] -= mi1[m - 1];
		ha2[a[i - 1]] -= mi2[m - 1];
		for (int j = 1; j <= p; j++)
		{
			ha1[j] *= BASE1;
			ha2[j] *= BASE2;
		}
		ha1[a[i + m - 1]]++;
		ha2[a[i + m - 1]]++;
		vis[a[i - 1]]--;
		vis[a[i + m - 1]]++;
		int cnt = 0;
		for (int j = 1; j <= p; j++)
			if (vis[j])
				mir[j] = ++cnt;
		for (int j = 1; j <= p; j++)
		{
			t1_1 += ha1[j] * mir[j];
			t1_2 += ha2[j] * mir[j];
		}
		if (t1_1 == t2_1 && t1_2 == t2_2)
			ans[++ans[0]] = i;
	}
	printf("%d\n", ans[0]);
	for (int i = 1; i <= ans[0]; i++)
		printf("%d\n", ans[i]);
}
