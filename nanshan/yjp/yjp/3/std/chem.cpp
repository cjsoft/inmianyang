#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
int n = 0;
std::vector<int> e[123456];
int h[123456];
int qh, qt, que[123456], inq[123456], pred[123456], dist[123456];
struct nod{
    bool l; nod *next;
}; nod l[123456], r[123456];
struct lis{
    nod *head, *tail; int size;
}; lis ll[123456];
struct st{
    lis *l; int pos;
};
bool operator ==(st a, st b){
    if(a.l->size != b.l->size) return false;
    nod *c = a.l->head, *d = b.l->head;
    while(c->next){
        if(c->l != d->l) return false;
        c = c->next; d = d->next;
    }
    return true;
}
bool operator <(st a, st b){
    if(a.l->size < b.l->size) return true;
    if(a.l->size > b.l->size) return false;
    nod *c = a.l->head, *d = b.l->head;
    while(c->next){
        if(c->l < d->l) return true;
        if(c->l > d->l) return false;
        c = c->next; d = d->next;
    }
    return false;
}
void dfsread(int idx){
    int tt = 3;
    while(tt--)
        if(getchar() == 'C'){
            e[idx].push_back(++n);
            e[n].push_back(idx);
            dfsread(n);
        }else
            ++h[idx];
}
int ans[123456];
void dfs(int idx){
    inq[idx] = 1; st lll[5]; int ln = 0;
    for(std::vector<int>::iterator it = e[idx].begin(); it != e[idx].end(); ++it) if(!inq[*it]) {
        lll[ln].pos = *it; lll[ln++].l = &ll[*it];
    }
    for(int i = 0; i < ln; ++i) dfs(lll[i].pos);
    ans[idx] = h[idx] > 0 ? 1 : 0;
    for(int i = 0; i < ln; ++i){
        int ss = 1;
        for(int j = 0; j < i; ++j)
            if(lll[i] == lll[j]){
                ss = 0; break;
            }
        if(ss) ans[idx] = (ans[idx] + ans[lll[i].pos]) % MOD;
    }
    std::sort(lll, lll + ln);
    ll[idx].head = &l[idx];
    ll[idx].size = 2;
    nod *c = ll[idx].head;
    for(int i = 0; i < ln; ++i){
        c->next = lll[i].l->head;
        c = lll[i].l->tail;
        ll[idx].size += lll[i].l->size;
    }
    ll[idx].tail = c->next = &r[idx];
}
int main(){
    freopen("chem.in", "r", stdin);
    freopen("chem.out", "w", stdout);
    //Initialize
    memset(h, 0, sizeof(h));
    h[0] = 1;
    getchar(); getchar();
    dfsread(0);
    //1st BFS
    qh = qt = que[0] = 0;
    memset(inq, 0, sizeof(inq));
    inq[0] = 1;
    while(qh <= qt){
        for(std::vector<int>::iterator it = e[que[qh]].begin(); it != e[que[qh]].end(); ++it) if(!inq[*it]){
            inq[*it] = 1; que[++qt] = *it;
        }
        ++qh;
    }
    //2nd BFS
    que[0] = que[qt]; dist[que[qt]] = 0;
    qh = qt = 0;
    memset(inq, 0, sizeof(inq));
    inq[que[qh]] = 1;
    while(qh <= qt){
        for(std::vector<int>::iterator it = e[que[qh]].begin(); it != e[que[qh]].end(); ++it) if(!inq[*it]){
            inq[*it] = 1; que[++qt] = *it;
            pred[*it] = que[qh];
            dist[*it] = dist[que[qh]] + 1;
        }
        ++qh;
    }
    //Find Center
    int cen;
    if(dist[que[qt]] % 2){
        int c = que[qt], tt = dist[que[qt]] / 2;
        while(tt--) c = pred[c];
        int d = pred[c]; ++n;
        for(std::vector<int>::iterator it = e[c].begin(); it != e[c].end(); ++it) if(*it == d){
            e[c].erase(it); break;
        }
        for(std::vector<int>::iterator it = e[d].begin(); it != e[d].end(); ++it) if(*it == c){
            e[d].erase(it); break;
        }
        e[c].push_back(n);
        e[d].push_back(n);
        e[n].push_back(c);
        e[n].push_back(d);
        cen = n;
    }else{
        int c = que[qt], tt = dist[que[qt]] / 2;
        while(tt--) c = pred[c];
        cen = c;
    }
    //DFS
    for(int i = 0; i <= n; ++i){
        l[i].l = 1; r[i].l = 0;
        l[i].next = r[i].next = NULL;
    }
    memset(inq, 0, sizeof(inq));
    dfs(cen);
    printf("%d\n", ans[cen]);
    return 0;
}
