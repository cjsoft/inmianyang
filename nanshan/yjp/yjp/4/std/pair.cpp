#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <cstdlib>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <string>
#define f(x, y, z) for(int x = (y); x <= (z); ++x)
#define g(x, y, z) for(int x = (y); x < (z); ++x)
#define h(x, y, z) for(int x = (y); x >= (z); --x)
#define foreach(x, y) for(__typeof(y.begin()) x = y.begin(); x != y.end(); ++x)
#define rforeach(x, y) for(__typeof(y.rbegin()) x = y.rbegin(); x != y.rend(); ++x)
using std::string;
using std::map;
using std::vector;
typedef long long LL;
typedef std::pair<int, int> PII;
typedef long double real;
#define a first
#define b second
map<string, int> S;
inline string gg(){
    char s[12]; scanf("%s", s); return string(s);
}
int n, cn = 0;
PII inv[508];
inline bool cross(PII x, PII y){
    return
    (x.a < y.a && y.a < x.b && x.b < y.b)
    ||
    (y.a < x.a && x.a < y.b && y.b < x.b)
    ;
}
inline bool contain(PII x, PII y){
    return x.a < y.a && y.b < x.b;
}
inline bool bylen(PII x, PII y){
    return x.b - x.a < y.b - y.a;
}
int col[508];
struct Tuo;
vector<Tuo *> tuos;
typedef std::pair<Tuo *, PII> PTP;
#define INF 10086
//a Tuo of intervals 233
struct Tuo{
    int dp[2][508];
    vector<PII> ins[2];
    PII first;
    vector<PTP> children;
    int maxx, minx, len;
    bool root;
    inline Tuo(){
        root = true; maxx = 0; minx = INF;
    }
    inline void dfs(int x, int c){
        // printf("dfs %d %d\n", x, c);
        if(col[x] != -1){
            if(col[x] != c) throw 233;
            return;
        }else{
            col[x] = c; first = inv[x];
            ins[c].push_back(first);
            if(first.a < minx) minx = first.a;
            if(first.b > maxx) maxx = first.b;
            len = maxx - minx;
            f(i, 1, n) if(i != x && cross(inv[i], inv[x])) dfs(i, 1 - c);
        }
    }
    inline void findChildren(){
        foreach(it, tuos){
            Tuo *tuo = *it;
            if(tuo == this) break;
            if(!tuo->root) continue;
            int height[2]; height[0] = height[1] = 0;
            f(id, 0, 1) foreach(it2, ins[id]) if(contain(*it2, tuo->first)){
                tuo->root = false; ++height[id];
            }
            if(height[0] || height[1]) children.push_back(PTP(tuo, PII(height[0], height[1])));
        }
    }
    inline void dfs(){
        foreach(it, children) it->first->dfs();
        int base[2]; base[0] = base[1] = 0;
        f(id, 0, 1){
            std::sort(ins[id].begin(), ins[id].end(), bylen);
            int size = ins[id].size();
            int tmpdp[508]; memset(tmpdp, 0, sizeof(tmpdp));
            g(i, 0, size){
                tmpdp[i] = 0;
                g(j, 0, i) if(contain(ins[id][i], ins[id][j]) && tmpdp[j] > tmpdp[i]) tmpdp[i] = tmpdp[j];
                ++tmpdp[i];
                if(tmpdp[i] > base[id]) base[id] = tmpdp[i];
            }
        }
        // printf("base %d %d\n", base[0], base[1]);
        f(id, 0, 1){
            f(i, 0, n){
                if(i >= base[id]) dp[id][i] = base[!id]; else dp[id][i] = INF;
                foreach(it, children){
                    Tuo *tuo = it->first; int a[2];
                    a[0] = it->second.first; a[1] = it->second.second;
                    int cans = std::min(
                    i >= a[id] ? (tuo->dp[id][i - a[id]] + a[!id]) : INF
                    ,
                    /*i >= a[!id] ? (tuo->dp[!id][i - a[!id]] + a[id]) :*/ INF
                    );
                    if(cans > dp[id][i]) dp[id][i] = cans;
                    // printf("child %d | height %d %d\n", tuo->len, a[0], a[1]);
                }
                // printf("dp %d | %d %d = %d\n", len, id, i, dp[id][i]);
            }
            g(i, 0, n) if(dp[id][i] < dp[id][i + 1]) dp[id][i + 1] = dp[id][i];
        }
        f(id, 0, 1){
            int lt = INF, l2 = n;
            f(i, 0, n) if(dp[id][i] != lt){
                lt = dp[id][i];
                while(l2 >= lt){
                    // printf("dp %d %d = %d\n", !id, l2, i);
                    dp[!id][l2--] = i;
                }
            }
        }
        f(i, 0, n) dp[0][i] = dp[1][i] = std::min(dp[0][i], dp[1][i]);
        // f(id, 0, 1) f(i, 0, n) printf("realdp %d %d = %d\n", id, i, dp[id][i]);
    }
};
inline bool cmp(Tuo *x, Tuo *y){
    return x->len < y->len;
}
int main(){
	freopen("pair.in", "r", stdin);
	freopen("pair.out", "w", stdout);
    int ___; scanf("%d", &___);
    f(__, 1, ___){
        memset(col, 0xff, sizeof(col));
        S.clear(); cn = 0;
        foreach(tuostar, tuos) delete *tuostar;
        tuos.clear();
        scanf("%d", &n);
        f(i, 1, n << 1){
            int &tar = S[gg()];
            if(tar){
                inv[++cn] = PII(tar, i);
            }else tar = i;
        }
        // f(i, 1, n) printf("inv %d %d\n", inv[i].a, inv[i].b);
        try{
            f(i, 1, n) if(col[i] == -1){
                Tuo *tuo = new Tuo;
                tuo->dfs(i, 0);
                tuos.push_back(tuo);
            }
            std::sort(tuos.begin(), tuos.end(), cmp);
            foreach(tuostar, tuos) (*tuostar)->findChildren();
            foreach(tuostar, tuos){
                Tuo *tuo = (*tuostar);
                if(tuo->root) tuo->dfs();
            }
            int bans = INF;
            f(top, 0, n){
                int cans = 0;
                foreach(tuostar, tuos){
                    Tuo *tuo = (*tuostar);
                    if(tuo->root){
                        int cc = std::min(tuo->dp[0][top], tuo->dp[1][top]);
                        if(cc > cans) cans = cc;
                    }
                }
                cans += top;
                // printf("top %d cans %d\n", top, cans);
                if(cans < bans) bans = cans;
            }
            printf("Case #%d: %d\n", __, bans);
        }catch(int){
            printf("Case #%d: -1\n", __);
        }
    }
    return 0;
}
