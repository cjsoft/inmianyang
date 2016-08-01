#include <cstdio>
#include <cstring>
#include <algorithm>
#define f(x, y, z) for(int x = (y), asdf = (z); x <= asdf; ++x)
inline int mm(int x, int y){return x < y ? x : y;}
inline int nn(int x, int y){return x > y ? x : y;}
int min[4200000], mark[4200000];
void sdec(int idx, int l, int r, int ll, int rr, int x){
    if(ll < l) ll = l; if(rr > r) rr = r; if(ll > rr) return;
    if(l == ll && r == rr){mark[idx] += x; min[idx] -= x;}
    else{
        int lson = idx << 1; int rson = lson + 1, mid = (l + r) >> 1;
        mark[lson] += mark[idx]; min[lson] -= mark[idx];
        mark[rson] += mark[idx]; min[rson] -= mark[idx]; mark[idx] = 0;
        if(rr <= mid) sdec(lson, l, mid, ll, rr, x);
        else if(ll > mid) sdec(rson, mid + 1, r, ll, rr, x);
        else{sdec(lson, l, mid, ll, mid, x); sdec(rson, mid + 1, r, mid + 1, rr, x);}
        min[idx] = mm(min[lson], min[rson]);
    }
}
int gmin(int idx, int l, int r, int ll, int rr){
    if(l == ll && r == rr) return min[idx];
    int lson = idx << 1; int rson = lson + 1, mid = (l + r) >> 1;
        mark[lson] += mark[idx]; min[lson] -= mark[idx];
        mark[rson] += mark[idx]; min[rson] -= mark[idx];mark[idx] = 0;
    if(rr <= mid) return gmin(lson, l, mid, ll, rr);
    else if(ll > mid) return gmin(rson, mid + 1, r, ll, rr);
    else return mm(gmin(lson, l, mid, ll, mid), gmin(rson, mid + 1, r, mid + 1, rr));
}
struct Mummy{int x, y;} m[100086];
inline bool operator<(const Mummy &a, const Mummy &b){return a.x < b.x;}
int n;
bool run(int ran){
    memset(min, 0, sizeof(min)); memset(mark, 0, sizeof(mark));
    int lpt = 1, rpt = 1, cx = -ran, las = -ran;
    for(;lpt <= n && m[lpt].x <= 0; ++lpt) sdec(1, -ran, ran, m[lpt].y - ran, m[lpt].y + ran, -1);
    for(;rpt <= n && m[rpt].x + ran + 1 <= -ran; ++rpt) sdec(1, -ran, ran, m[rpt].y - ran, m[rpt].y + ran, 1);
    if(min[1] == 0) return true;
    las = cx; cx = mm(m[lpt].x - ran, m[rpt].x + ran + 1);
    while((lpt <= n || rpt <= n) && cx <= ran){
        for(;lpt <= n && m[lpt].x - ran == cx; ++lpt) sdec(1, -ran, ran, m[lpt].y - ran, m[lpt].y + ran, -1);
        for(;rpt <= n && m[rpt].x + ran + 1 == cx; ++rpt) sdec(1, -ran, ran, m[rpt].y - ran, m[rpt].y + ran, 1);
        if(min[1] == 0) return true;
        las = cx; cx = mm(m[lpt].x - ran, m[rpt].x + ran + 1);
    }
    if(las < ran){
        for(;lpt <= n && m[lpt].x - ran == ran; ++lpt) sdec(1, -ran, ran, m[lpt].y - ran, m[lpt].y + ran, -1);
        for(;rpt <= n && m[rpt].x == -1; ++rpt) sdec(1, -ran, ran, m[rpt].y - ran, m[rpt].y + ran, 1);
        if(min[1] == 0) return true;
    }
    return false;
}
int main(){
	freopen("mummy.in", "r", stdin);
	freopen("mummy.out", "w", stdout);
    int id = 1;
    for(;;){
        scanf("%d", &n); if(n == -1) break;
        f(i, 1, n) scanf("%d%d", &m[i].x, &m[i].y);
        m[n + 1].x = m[n + 1].y = 0x1f1f1f1f;
        m[n + 2].x = m[n + 2].y = -0x1f1f1f1f; n += 2;
        std::sort(m + 1, m + n + 1);
        printf("Case %d: ", id++);
        int l = 0, r = 1000086;
        while(l < r){
            int nm = (l + r + 1) >> 1;
            if(run(nm)) l = nm; else r = nm - 1;
        }
        if(l == 1000086) printf("never\n"); else printf("%d\n", l + 1);
    }
    return 0;
}
