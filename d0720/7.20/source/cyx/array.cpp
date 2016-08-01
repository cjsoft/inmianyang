#include<bits/stdc++.h>

using namespace std;

const int N = 100000 + 10, INF = ~0u >> 1;

int a[N], C[N], n, m;

/*
void add(int x, int d) {
	for(; 0 < x && x <= m; x += x & -x) {
		if(C[x] < d) C[x] = d;
	}
}
*/

#define add(y, z) {\
	for(int x = y, d = z; 0 < x && x <= m; x += x & -x) {\
		if(C[x] < d) C[x] = d;\
	}\
}

int query(int x) {
	int res = 0;
	for(; 0 < x && x <= m; x ^= x & -x) {
		if(res < C[x]) res = C[x];
	}
	return res;
}

int main() {
	freopen("array.in", "r", stdin);
	freopen("array.out", "w", stdout);

	int times;
	scanf("%d%d%d", &n, &m, &times);
	for(int i = 1; i <= n; i++) {
		scanf("%d", a + i);
	}
	times = min(min(n, m), times);

	while(times--) for(int i = 1; i <= n; i++) {
		add(a[i], query(a[i]-1) + 1);
	}

	printf("%d\n", query(m));

#ifdef DEBUG
	cerr << clock() << endl;
#endif
	return 0;
}
