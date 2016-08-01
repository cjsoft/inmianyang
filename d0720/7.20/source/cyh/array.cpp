#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MXN 300007
using namespace std;
int dp[MXN];
int seq[MXN];
int n, m, t;
inline int getint();
int main() {
    freopen("array.in", "r", stdin);
    freopen("array.out", "w", stdout);
    n = getint(); m = getint(); t = getint();
    for (int i = 0; i < n; ++i) seq[i] = getint();
    for (int i = 1; i < t; ++i) {
        for (int j = 0; j < n; ++j) {
            seq[i * n + j] = seq[j];
        }
    }
    for (int i = 0; i < n * t; ++i) dp[i] = 1;
    for (int i = 0; i < n * t - 1; ++i) {
        for (int j = i + 1; j < n * t; ++j) {
            if (seq[j] > seq[i]) dp[j] = max(dp[j], dp[i] + 1);
        }
    }
    int ans = 1;
    for (int i = 1; i < n * t; ++i) ans = max(ans, dp[i]);
    printf("%d\n", ans);
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