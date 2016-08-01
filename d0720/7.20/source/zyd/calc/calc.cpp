#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;
typedef unsigned long long ull;

set<int> S;
void dfs(int u, int rem, int s, int Lim)
{
	S.insert(s);
	if (rem - u == 0) return ;
	for (int i = u; i <= rem - 1; i++)
		if (1LL * s * i <= Lim)
			dfs(i, rem - 1, s * i, Lim);
}
int Main(int a, int b)
{
	S.clear();
	dfs(2, b, 1, a);
	return S.size();
}
int main()
{
	freopen("calc.in", "r", stdin);
	freopen("calc.out", "w", stdout);
	int l, r, p;
	scanf("%d%d%d", &l, &r, &p);
	printf("%d\n", Main(r, p) - Main(l - 1, p));
}
