#include <iostream>
#include <cstdio>
#include <algorithm>
#include <map>
#define MXN 100007
#define MXM 25007
using namespace std;
int locb[MXM], loca[MXN];
int szb, sza;
int a[MXN], b[MXN];
int tmp[MXN];
int n, m;
int p;
int pos[MXN], tot = 0;
inline int getint();
int main() {
    freopen("pat.in", "r", stdin);
    freopen("pat.out", "w", stdout);
    n = getint(); m = getint(); p = getint();
    for (int i = 1; i <= n; ++i) a[i] = getint();
    for (int i = 1; i <= m; ++i) tmp[i] = b[i] = getint();
    sort(tmp + 1, tmp + 1 + m);
    szb = unique(tmp + 1, tmp + 1 + n) - tmp - 1;
    for (int i = 1; i <= m; ++i) locb[i] = lower_bound(tmp + 1, tmp + 1 + szb, b[i]) - tmp;
    for (int i = 1; i <= n - m + 1; ++i) {
        for (int j = 0; j < m; ++j) {
            tmp[j] = a[i + j];
        }
        sort(tmp, tmp + m);
        sza = unique(tmp, tmp + m) - tmp;
        for (int j = 0; j < m; ++j) {
            loca[j] = lower_bound(tmp, tmp + sza, a[i + j]) - tmp + 1;
        }
        for (int j = 0; j < m; ++j) {
            if (loca[j] != locb[j + 1])
                goto SKP;
        }
        pos[tot++] = i;
        SKP:;
    }
    printf("%d\n", tot);
    for (int i = 0; i < tot; ++i) printf("%d\n", pos[i]);
    return 0;
}

int getint() {
    static int rtn, f;
    static char ch;
    rtn = 0; f = 1;
    while ((ch = getchar()) < '0' || ch > '9') if (ch == '-') f = -f;
    rtn = ch - '0';
    while ((ch = getchar()) >= '0' && ch <= '9') rtn = rtn * 10 + ch - '0';
    return rtn * f;
}