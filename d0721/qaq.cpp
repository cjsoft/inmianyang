#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
double f[11][11];
int n, m, T;
int main() {
    freopen("qaq.in", "r", stdin);
    freopen("qaq.out", "w", stdout);
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d", &n, &m);
        memset(f, 0, sizeof(f));
        for (int i = 1; i <= n; ++i) f[1][i] = 1. / n;
        for (int i = 2; i <= m; ++i) {
            int x = min(m, i * n);
            for (int j = i; j <= x; ++j) {
                for (int k = max(i - 1, j - n); k < j; ++k) {
                    f[i][j] += f[i - 1][k] / n;
                }
            }
        }
        double ans = 0;
        for (int i = 1; i <= m; ++i) ans += f[i][m];
        printf("%lf\n", ans);
    }
    return 0;
}