#include<bits/stdc++.h>

using namespace std;

const int N = 100000 + 10;

int C[30], n, m, p;

int query(int x) {
	int res = 0;
	for(; 0 < x && x <= p; x ^= x & -x) res += C[x];
	return res;
}

void add(int x, int d) {
	for(; 0 < x && x <= p; x += x & -x) C[x] += d;
}

int f[N], c1[N], c2[N];
int s[N], t[N];

bool same(int a, int b) {
	return query(a - 1) == c1[b] && query(a) == c2[b];
}

void get_fail(const int *s, int n) {
	memset(C, 0, sizeof C);
	for(int j = 0, i = 2; i <= n; i++) {
		while(j && !same(s[i], j + 1)) {
			for(int k = i - j; k < i - f[j]; k++) {
				add(s[k], -1);
			}
			j = f[j];
		}
		if(same(s[i], j + 1)) ++j, add(s[i], 1);
		f[i] = j;
	}
}

vector<int> ans;

void kmp() {
	memset(C, 0, sizeof C);
	for(int j = 0, i = 1; i <= n; i++) {
		while(j && (j == m || !same(s[i], j + 1))) {
			for(int k = i - j; k < i - f[j]; k++) {
				add(s[k], -1);
			}
			j = f[j];
		}
		if(same(s[i], j + 1)) ++j, add(s[i], 1);
		if(j == m) ans.push_back(i - m + 1);
	}
}

int main() {
	freopen("pat.in", "r", stdin);
	freopen("pat.out", "w", stdout);

	scanf("%d%d%d", &n, &m, &p);
	for(int i = 1; i <= n; i++) scanf("%d", s + i);
	for(int i = 1; i <= m; i++) scanf("%d", t + i);

	for(int i = 1; i <= n; i++) {
		c1[i] = query(t[i]-1);
		c2[i] = query(t[i]);
		add(t[i], 1);
	}

	get_fail(t, m);
	kmp();

	printf("%u\n", ans.size());
	for(unsigned i = 0; i < ans.size(); i++) {
		printf("%d\n", ans[i]);
	}

	return 0;
}
