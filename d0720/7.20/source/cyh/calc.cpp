#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;
typedef pair<int, int> pii;
int p, l, r;
int global_resu = 0;
char tag[1000007];
void dfs(int step, pii data) {
    if (step > p || data.first > r) return;
    tag[data.first] = 1;
    dfs(step + 1, make_pair(data.first, data.second + 1));
    dfs(step + 1, make_pair(data.first * data.second, data.second));
}

int main() {
    freopen("calc.in", "r", stdin);
    freopen("calc.out", "w", stdout);
    scanf("%d %d %d", &l, &r, &p);
    dfs(0, make_pair(1, 0));
    int ans = 0;
    for (int i = l; i <= r; ++i) if (tag[i]) ++ans;
    printf("%d\n", ans);
    return 0;
}