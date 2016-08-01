#include <cstdio>
#include <cstring>
#include <algorithm>
#define f(x, y, z) for(int x = (y); x <= (z); ++x)
#define g(x, y, z) for(int x = (y); x < (z); ++x)
#define h(x, y, z) for(int x = (y); x >= (z); --x)

typedef unsigned long long ULL;

char buf[233];
inline ULL read_bin(){
	scanf("%s", buf);
	ULL ans = 0; int n = strlen(buf);
	g(i, 0, n) ans = ans * 2ull + (ULL) (buf[i] - '0');
	return ans;
}
inline void write_bin(int x){
	int i = 30;
	while(!(x >> i & 1)) --i;
	h(j, i, 0) putchar('0' + (x >> j & 1));
	putchar('\n');
}

int _popcnt[1 << 16];
inline int popcnt(ULL x){
	return _popcnt[x & 65535ull] + _popcnt[x >> 16 & 65535ull] + _popcnt[x >> 32 & 65535ull] + _popcnt[x >> 48 & 65535ull];
}

/*
	send n: 9 bytes
	each number:
		way 0: 65 bytes
		way 1: 16 + 6 * diff bytes
*/

struct edge{
	int s, t, w;
} e[233333]; int en = 0;
inline bool operator <(const edge &x, const edge &y){
	return x.w < y.w;
}

int _fa[555];
inline int fa(int x){
	if(_fa[x] == x) return x; else return _fa[x] = fa(_fa[x]);
}

ULL a[555];
int main(){
	freopen("binc.in", "r", stdin);
	freopen("binc.out", "w", stdout);
	_popcnt[0] = 0;
	g(i, 1, 1 << 16) _popcnt[i] = _popcnt[i >> 1] + (i & 1);
	
	int n = read_bin();
	f(i, 1, n) a[i] = read_bin();
	
	f(i, 1, n) e[++en] = (edge) {0, i, 65};
	f(i, 1, n) f(j, i + 1, n) e[++en] = (edge) {i, j, 16 + popcnt(a[i] ^ a[j]) * 6};
	std::sort(e + 1, e + en + 1);
	
	f(i, 0, n) _fa[i] = i;
	int ans = 9, tm = 0;
	f(i, 1, en){
		int fs = fa(e[i].s), ft = fa(e[i].t);
		if(fs != ft){
			_fa[fs] = ft;
			ans += e[i].w;
			if(e[i].w == 65) ++tm;
		}
	}
	write_bin(ans);
	return 0;
}
