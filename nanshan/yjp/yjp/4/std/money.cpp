#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
#define LL long long
namespace discre{
	int a[1000001], n, tot;
	void add(int A) { a[++n] = A; }
	void init() { sort(a + 1, a + n + 1); tot = unique(a + 1, a + n + 1) - a - 1; }
	int big(int x) //return the first element which is greater than or equal to x
	{
		int p = lower_bound(a + 1, a + tot + 1, x) - a;
		if (p == tot + 1) return -1;
		return p;
	}
	int small(int x) // return the last element which is less than or equal to x
	{
		int p = upper_bound(a + 1, a + tot + 1, x) - a - 1;
		if (p == 0) return -1;
		return p;
	}
};
int n;
namespace SGT{
	const int MAXN = 2000001;
	LL sum[MAXN], sum2[MAXN];
	int minnum[MAXN], maxnum[MAXN];
	int _cover[MAXN];
void docover(int idx)
{
	_cover[idx] = true;
	minnum[idx] = n + 1; maxnum[idx] = 0;
	sum[idx] = sum2[idx] = 0;
}
void push(int idx)
{
	if (_cover[idx]){
		docover(idx * 2);
		docover(idx * 2 + 1);
		_cover[idx] = false;
	}
}
void init(int n)
{
	for (int i = 1; i < MAXN; i++) maxnum[i] = 0;
	for (int i = 1; i < MAXN; i++) minnum[i] = n + 1;
}
void update(int idx)
{
	sum[idx] = sum[idx * 2] + sum[idx * 2 + 1];
	sum2[idx] = sum2[idx * 2] + sum2[idx * 2 + 1];
	minnum[idx] = min(minnum[idx * 2], minnum[idx * 2 + 1]);
	maxnum[idx] = max(maxnum[idx * 2], maxnum[idx * 2 + 1]);
}
void add(int idx, int l, int r, int x, int d)
{
	if (l == r){
		sum[idx] += d;
		sum2[idx] += discre::a[x] * d;
		if (sum[idx]) minnum[idx] = maxnum[idx] = l;
		else { minnum[idx] = n + 1; maxnum[idx] = 0; }
		return;
	}
	push(idx);
	int m = l + r >> 1;
	if (x <= m) add(idx * 2, l, m, x, d);
	else add(idx * 2 + 1, m + 1, r, x, d);
	update(idx);
}
void add(int idx, int delta)
{
	add(1, 1, n, idx, delta);
}
LL queryAt(int idx, int l, int r, int x)
{
	if (l == r) return sum[idx];
	int m = l + r >> 1;
	push(idx);
	if (x <= m) return queryAt(idx * 2, l, m, x);
	else return queryAt(idx * 2 + 1, m + 1, r, x);
}
LL queryAt(int idx)
{
	return queryAt(1, 1, n, idx);
}
bool empty() { return sum[1] == 0; }
LL size() { return sum[1]; }
int getkth(int idx, int l, int r, int k)
{
	if (l == r) return l;
	int m = l + r >> 1;
	push(idx);
	if (sum[idx * 2] >= k) return getkth(idx * 2, l, m, k);
	else return getkth(idx * 2 + 1, m + 1, r, k - sum[idx * 2]);
}
int getkth(int k)
{
	return getkth(1, 1, n, k);
}
int getbig(int idx, int l, int r, int x)
{
	if (l == r) return minnum[idx];
	int m = l + r >> 1;
	push(idx);
	if (x <= m){
		int t = getbig(idx * 2, l, m, x);
		if (t < x) t = n + 1;
		return min(t, minnum[idx * 2 + 1]);
	}
	else return getbig(idx * 2 + 1, m + 1, r, x);
}
int getbig(int x)
{
	return getbig(1, 1, n, x);
}
int getsmall(int idx, int l, int r, int x)
{
	if (l == r) return maxnum[idx];
	int m = l + r >> 1;
	push(idx);
	if (x >= m){
		int t = getsmall(idx * 2 + 1, m + 1, r, x);
		if (t > x) t = 0;
		return max(t, maxnum[idx * 2]);
	}
	else return getsmall(idx * 2, l, m, x);
}
int getsmall(int x)
{
	return getsmall(1, 1, n, x);
}
LL getsum(int idx, int l, int r, int ll, int rr)
{
	if (ll <= l && rr >= r) return sum2[idx];
	int m = l + r >> 1;
	push(idx);
	LL ret = 0;
	if (ll <= m) ret += getsum(idx * 2, l, m, ll, rr);
	if (rr > m) ret += getsum(idx * 2 + 1, m + 1, r, ll, rr);
	return ret;
}
int getnum(int idx, int l, int r, int ll, int rr)
{
	if (ll <= l && rr >= r) return sum[idx];
	int m = l + r >> 1;
	push(idx);
	LL ret = 0;
	if (ll <= m) ret += getnum(idx * 2, l, m, ll, rr);
	if (rr > m) ret += getnum(idx * 2 + 1, m + 1, r, ll, rr);
	return ret;
}
int getnum(int l, int r)
{
	return getnum(1, 1, n, l, r);
}
LL getsum(int l, int r)
{
	return getsum(1, 1, n, l, r);
}
void cover(int idx, int l, int r, int ll, int rr)
{
	if (ll <= l && rr >= r){
		docover(idx);
		return;
	}
	int m = l + r >> 1;
	push(idx);
	if (ll <= m) cover(idx * 2, l, m, ll, rr);
	if (rr > m) cover(idx * 2 + 1, m + 1, r, ll, rr);
	update(idx);
}
void cover(int l, int r)
{
	cover(1, 1, n, l, r);
}
int getrank(int idx, int l, int r, int x)
{
	if (l == r) return sum[idx];
	int m = l + r >> 1;
	push(idx);
	if (x <= m) return getrank(idx * 2, l, m, x);
	else return getrank(idx * 2 + 1, m + 1, r, x) + sum[idx * 2];
}
int getrank(int x)
{
	return getrank(1, 1, n, x);
}
}
const int MAXN = 1000001;
int op[MAXN], a[MAXN], b[MAXN], c[MAXN], d[MAXN];
int main()
{
freopen("money.in", "r", stdin);
freopen("money.out", "w", stdout);
int Q; scanf("%d", &Q);
for (int ti = 1; ti <= Q; ti++){
	scanf("%d", &op[ti]);
	switch(op[ti]){
		case 1 : scanf("%d", &a[ti]); discre::add(a[ti]); break;
		case 2 : scanf("%d", &a[ti]); break;
		case 3 : case 4 : break;
		case 5 : case 6 : case 7 : scanf("%d%d", &a[ti], &b[ti]); break;
		case 8 : scanf("%d%d%d%d", &a[ti], &b[ti], &c[ti], &d[ti]); break;
	}
}
	discre::init();
	n = discre::tot;
	SGT::init(n);
for (int ti = 1; ti <= Q; ti++){
	switch(op[ti]){
		case 1 : {
					puts("OK");
					int x = discre::big(a[ti]);
					SGT::add(x, 1);
					break;
				 }	
		case 2 : {
					puts("OK");
					scanf("%d", &a[ti]);
					int x = discre::big(a[ti]);
					if (x < 0) break;
					if (discre::a[x] != a[ti]) break;
					int at = SGT::queryAt(x);
					if (at <= 0) break;
					SGT::add(x, -1);
					break;	 
				 }
		case 3 : {
					 if (SGT::empty()) puts("0");
					 else printf("%lld\n", (LL)SGT::sum2[1]);
					 break;
				 }
		case 4 : {
					 if (SGT::empty()) puts("0");
					 else printf("%lld\n", (LL)discre::a[SGT::getkth(1)]);
					 break;
				 }
		case 5 : {
					puts("OK");
					int L = discre::big(a[ti]), R = discre::small(b[ti]);
					if (L == -1 || R == -1) break;
					if (L > R) break;
					SGT::cover(L, R);
					break;
				 }
		case 6 : {
					 puts("OK");
					 int L = discre::big(a[ti]), R = discre::small(b[ti]);
					 if (L == -1 || R == -1 || L > R) break;
					 int x = SGT::getsmall(R);
					 if (x < L) break;
					 SGT::add(x, -1);
					 break;
				 }
		case 7 : {
					 int L = discre::big(a[ti]), R = discre::small(b[ti]);
					 if (L == -1 || R == -1 || L > R) { puts("0"); break; }
					 int x = SGT::getbig(L);
					 if (x > R) puts("0");
					 else printf("%lld\n", (LL)discre::a[x]);
					 break;
				 }
		case 8 : {
					 int L = discre::big(a[ti]), R = discre::small(b[ti]);
				     if (L == -1 || R == -1 || L > R || c[ti] > d[ti]) { puts("0"); break; }
					 int x = SGT::getbig(L);
					 int y = SGT::getsmall(R);
					 if (x > y) { puts("0"); break; }
					 int t = SGT::getnum(x, y);
					 if (c[ti] > t) { puts("0"); break; }
					 d[ti] = min(d[ti], t);
					 int s = SGT::getrank(x);
					 swap(c[ti], d[ti]);
					 c[ti] = t - c[ti] + 1;
					 d[ti] = t - d[ti] + 1;
					 x = SGT::getkth(s + c[ti] - 1);
					 y = SGT::getkth(s + d[ti] - 1);
					 printf("%lld\n", SGT::getsum(x, y));
					 break;
				 }
	}
}
}