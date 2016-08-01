#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#define MOD 998244353LL
#define INV6 166374059LL
using namespace std;
typedef long long ll;

inline int getint();
inline ll getll();
int T;
ll a, b, k, p;
// ans=\sum_{i=0}^{\frac{k}{2}}(2i+1)^2(a^2+b^2)
// ans=\lfloor\frac{k}{2}\rfloor+1
int main() {
    freopen("we.in", "r", stdin);
    freopen("we.out", "w", stdout);
    T = getint();
    while (T--) {
        a = getll(); b = getll(); k = getll(); p = getll();
        if (k & 1) {
            puts("0");
            continue;
        }
        if (p) {
            ll ans = 0;
            ll tp = k >> 1;
            ll tmp = 4 * tp % MOD * (tp + 1) % MOD * (2 * tp % MOD + 1) % MOD * INV6 % MOD;
            ans = a * a % MOD * tmp % MOD; 
            ans = (ans + b * b % MOD * tmp % MOD) % MOD;
            ans = (ans + 2 * tp  % MOD * (tp + 1) % MOD * ((a * a % MOD + b * b % MOD) % MOD) % MOD) % MOD;
            ans = (ans + (tp + 1) * ((a * a % MOD + b * b % MOD) % MOD) % MOD) % MOD;
            // for (int i = 0; i <= tp; ++i) {
            //     ll w = i << 1, h = k - w;
            //     ll o = (b * w % MOD + b) % MOD;
            //     ans = ((ans + (h + 1) * a % MOD * (h + 1) % MOD * a % MOD) % MOD + o * o % MOD) % MOD;
            // }
            printf("%lld\n", ans);
        } else {
            printf("%lld\n", (k >> 1) + 1);
        }
    }
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
ll getll() {
    static ll rtn, f;
    static char ch;
    rtn = 0; f = 1;
    while ((ch = getchar()) < '0' || ch > '9') if (ch == '-') f = -f;
    rtn = ch - '0';
    while ((ch = getchar()) >= '0' && ch <= '9') rtn = rtn * 10 + ch - '0';
    return rtn * f;
}