#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MXN 100007
#define MXM 25007
#define MXP 27
#define BASE1 133
#define BASE2 233
typedef unsigned long long ull;
typedef long long ll;
int n, m, k;
ull f[MXP][MXN], g[MXP][MXN], h[MXM];
ull q(int x, int l, int r) {
    return f[x][r] - f[x][l - 1] * h[m];
}
int main() {
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    for (int i = 1; i <= m; ++i) scanf("%d", b + i);
    h[0] = 1;
    for (int i = 1; i < MXM; ++i) h[i] = h[i - 1] * BASE1;
    
    return 0;
}