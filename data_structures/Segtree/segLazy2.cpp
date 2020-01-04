/*input

*/
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for(int (i) = (a); (i) < (n); ++(i))
#define per(i,a,n) for(int (i) = (n-1); (i) >= (a); --(i))
#define fi first
#define se second
#define pb push_back
#define mt make_tuple
#define mp make_pair
#define all(v) (v).begin(), (v).end()
#define SZ(a) ((int)(a.size()))
#define init() ios::sync_with_stdio(0);cin.tie(0);
#define left(x) ((x) << 1)
#define right(x) (left(x) + 1)

typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
const int inf = 0x3f3f3f3f;
const int neginf = 0xc0c0c0c0;
const int mod = 1000000007;
const int maxn = 100005;


vi tree[4*maxn];
int lazy[4*maxn];

void propagate(int node, int lo, int hi){
	tree[node] += lazy[node] * (hi - lo + 1);
	if(lo != hi){
		lazy[left(node)] += lazy[node];
		lazy[right(node)] += lazy[node];
	}
	lazy[node] = 0;
}

void update(int node, int lo, int hi, int a, int b, int val){
	if(a <= lo && hi <= b){
		lazy[node] += val;
		return;
	}
	propagate(node, lo, hi);
	int mid = (lo + hi) >> 1;
	if(a <= mid) update(left(node), lo, mid, a, b, val);
	if(b > mid) update(right(node), mid+1, hi, a, b, val);
	propagate(left(node), lo, mid);
	propagate(right(node), mid+1, hi);
	tree[node] = tree[left(node)] + tree[right(node)];
}

ll query(int node, int lo, int hi, int a, int b){
	propagate(node, lo, hi);
	if(a <= lo && hi <= b){
		return tree[node];
	}
	ll ret = 0;
	int mid = (lo + hi)>>1;
	if(a <= mid) ret = query(left(node), lo, mid, a, b);
	if(b > mid) ret = query(right(node), mid+1, hi, a, b);
	return ret;
}

ll powmod(ll a, ll b){ ll res = 1; a %= mod; assert(b>=0); for(;b;b>>=1){ if(b&1) res = (res*a)%mod; a = (a*a)%mod;} return res; }


int main(){
	return 0;
}

