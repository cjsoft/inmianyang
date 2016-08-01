#include <cstdio>
#include <cstring>
#define f(x, y, z) for(int x = (y), asdf = (z); x <= asdf; ++x)
#define g(x, y, z) for(int x = (y), asdf = (z); x < asdf; ++x)
#define h(x, y, z) for(int x = (y), asdf = (z); x >= asdf; --x)

bool hash[33554432];
int n;
char map[1008][1008];

int main(){
	freopen("zbd.in", "r", stdin);
	freopen("zbd.out", "w", stdout);
	scanf("%d", &n);
	f(i, 1, n){
		scanf("%s", map[i] + 1);
		f(j, 1, n) map[i][j] = (map[i][j] == '1');
	}
	f(m, 1, n){
		int thash = (1 << (m * m));
		memset(hash, 0, thash);
		f(i, 1, n + 1 - m) f(j, 1, n + 1 - m){
			int chash;
			chash = 0;
			g(k, i, i + m) g(l, j, j + m) chash = (chash << 1) + map[k][l];
			hash[chash] = 1;
			chash = 0;
			g(k, i, i + m) h(l, j + m - 1, j) chash = (chash << 1) + map[k][l];
			hash[chash] = 1;
			chash = 0;
			h(k, i + m - 1, i) h(l, j + m - 1, j) chash = (chash << 1) + map[k][l];
			hash[chash] = 1;
			chash = 0;
			h(k, i + m - 1, i) g(l, j, j + m) chash = (chash << 1) + map[k][l];
			hash[chash] = 1;
			
			chash = 0;
			g(l, j, j + m) g(k, i, i + m) chash = (chash << 1) + map[k][l];
			hash[chash] = 1;
			chash = 0;
			h(l, j + m - 1, j) g(k, i, i + m) chash = (chash << 1) + map[k][l];
			hash[chash] = 1;
			chash = 0;
			h(l, j + m - 1, j) h(k, i + m - 1, i) chash = (chash << 1) + map[k][l];
			hash[chash] = 1;
			chash = 0;
			g(l, j, j + m) h(k, i + m - 1, i) chash = (chash << 1) + map[k][l];
			hash[chash] = 1;
		}
		g(chash, 0, thash) if(!hash[chash]){
			printf("%d\n", m);
			int c = 0;
			h(i, m * m - 1, 0){
				if(chash & (1 << i)) putchar('1'); else putchar('0');
				if(!((++c) % m)) putchar('\n');
			}
			return 0;
		}
	}
	return 0;
}
