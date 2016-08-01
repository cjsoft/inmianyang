#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#define iterate(_x, _i) for (edge *_i = head[_x]; _i; _i = _i->prev)

struct edge {
    edge *prev;
    int to, flow;
} buf[MXM << 1 | 1], *head[MXN], *cur;

inline void addedge(int a, int b, int flow) {
    cur->prev = head[a];
    cur->to = b;
    cur->flow = flow;
    head[a] = cur++;
    cur->prev = head[b];
    cur->to = a;
    cur->flow = 0;
    head[b] = cur++;
}
int S, T;
int dis[MXN], gap[MXN];
int dfs(int root, int flow_avaliable) {
    if (root == T) return flow_avaliable;
    int flow_used = 0;
    int min_dis = n - 1;
    iterate(root, i) {
        if (i->w) {
            if (dis[root] == dis[i->to] + 1) {
                int temp = dfs(i->to, min(flow_avaliable - flow_used, i->flow));
                i->flow -= temp;
                (buf + ((i - buf) ^ 1))->flow += temp;
                if (dis[1] >= n) return flow_used;
                if (flow_used == flow_avaliable) break;
            }
            min_dis = min(min_dis, dis[i->to]);
        }
    }
    if (!flow_used) {
        --gap[dis[root]];
        if (!gap[dis[root]]) dis[1] = n;
        ++gap[dis[root] = min_dis + 1];
    }
    return flow_used;
}
int max_flow() {
    int resu = 0;
    gap[0] = n;
    while (dis[1] < n) resu += dfs(S, INF);
    return resu;
}
using namespace std;

int main() {

    return 0;
}