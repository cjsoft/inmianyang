#include <cstdio>
#include <cstring>
#include <map>
#include <cmath>
#define f(x, y, z) for(int x = (y), asdf = (z); x <= asdf; ++x)
#define g(x, y, z) for(int x = (y), asdf = (z); x < asdf; ++x)
int type[52], dt[52], en;
std::map<int, int> avnum;
int main(){
	freopen("money.in", "r", stdin);
	freopen("money.out", "w", stdout);
    for(;;){
        avnum.clear();
        en = 0;
        int n; scanf("%d", &n); if(!n) break;
        char buf[25]; int q, paid = 0, paynum = 0;
        while(n--){
            scanf("%s%d", buf, &q);
            if(buf[0] == 'C') continue;
            else if(buf[0] == 'P') paid += q;
            else{
                if(en && paid){type[en] = 1; dt[en] = paid; ++en; ++paynum;}
                type[en] = 0; dt[en] = (buf[0] == 'I') ? q : (-q);
                ++en; paid = 0;
            }
        }
        int cur = 0, min = 0;
        g(i, 0, en){
            if(type[i]){
                f(j, 1, sqrt(dt[i])) if(!(dt[i] % j)){
                    if(j > cur) ++avnum[j - cur];
                    int k = dt[i] / j;
                    if(k != j && k > cur) ++avnum[k - cur];
                }
            }
            else if((cur += dt[i]) < min) min = cur;
        }
        if(paynum){
            bool fir = true;
            for(std::map<int, int>::iterator it = avnum.begin(); it != avnum.end(); ++it)
                if(it->first >= 1 - min && it->second == paynum){
                    if(fir){fir = false; printf("%d", it->first);} else printf(" %d", it->first);
            }
            printf(fir ? "IMPOSSIBLE\n" : "\n");
        }else
            printf("SIZE >= %d\n", 1 - min);
    }
    return 0;
}
