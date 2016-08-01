#include <cstdio>

int n, m, p, a[100005], b[25005];

namespace PST {
	struct Node {
		Node *ch[2];
		int cnt;

		Node() {
			ch[0] = ch[1] = 0;
			cnt = 0;
		}
	} *root[2][100005];
	int T[2];

	void build(Node *&k, int l, int r) {
		k = new Node();
		if (l == r) return;
		int mid = (l + r) >> 1;
		build(k->ch[0], l, mid);
		build(k->ch[1], mid + 1, r);
	}

	void init() {
		build(root[0][T[0] = 0], 1, p);
		build(root[1][T[1] = 0], 1, p);
	}

	void modify(Node *&k, int l, int r, int pos) {
		k = new Node(*k);
		if (l == r) {
			++k->cnt; return;
		}
		int mid = (l + r) >> 1;
		if (pos <= mid) modify(k->ch[0], l, mid, pos);
		else modify(k->ch[1], mid + 1, r, pos);
		k->cnt = k->ch[0]->cnt + k->ch[1]->cnt;
	}

	void add(int str, int pos) {
		++T[str];
		modify(root[str][T[str]] = root[str][T[str] - 1], 1, p, pos);
	}

	int query(Node *L, Node *R, int l, int r, int key) {
		if (l == r) return 1;
		int mid = (l + r) >> 1;
		if (key <= mid) return query(L->ch[0], R->ch[0], l, mid, key);
		return R->ch[0]->cnt - L->ch[0]->cnt + query(L->ch[1], R->ch[1], mid + 1, r, key);
	}

	int kth(int str, int l, int r, int key) {
		return query(root[str][l - 1], root[str][r], 1, p, key);
	}
}

int fail[100005];
void get_fail() {
	fail[0] = fail[1] = 0;
	for (int i = 2, j; i <= m; ++i) {
		j = fail[i - 1];
		while (j && PST::kth(1, 1, j + 1, b[j + 1]) != PST::kth(1, i - j, i, b[i])) j = fail[j];
		fail[i] = j + 1;
	}
}

int ans[100005];
void KMP() {
	for (int i = 1, j = 0; i <= n; ++i) {
		while (j && PST::kth(1, 1, j + 1, b[j + 1]) != PST::kth(0, i - j, i, a[i])) j = fail[j];
		++j;
		if (j == m) {
			ans[++*ans] = i - m + 1;
			j = fail[j];
		}
	}
}

int main() {
#ifndef LOCAL
	freopen("pat.in", "r", stdin), freopen("pat.out", "w", stdout);
#endif

	scanf("%d%d%d", &n, &m, &p);
	PST::init();
	for (int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		PST::add(0, a[i]);
	}
	for (int i = 1; i <= m; ++i) {
		scanf("%d", b + i);
		PST::add(1, b[i]);
	}

	get_fail();
	KMP();

	printf("%d\n", *ans);
	for (int i = 1; i <= *ans; ++i) printf("%d\n", ans[i]);
	return 0;
}
