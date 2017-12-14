#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define pb push_back
#define all(v) (v).begin(), (v).end()
#define mp make_pair

template <typename T>

struct SegTree{
	int N;
	T dummy;
	vector<T> st;
	T op(const T& a, const T& b){
		return min(a,b);
	}
	SegTree(int _N, T _dummy) : N(_N), dummy(_dummy){
		st.assign(4*_N, dummy);
	}
	void update(int node, int start, int end, int idx, T val){
		if(start > idx || end < idx) return;
		if(start == end && start == idx){ st[node] = val; return;}
		update(2*node, start, (start+end)/2, idx, val);
		update(2*node+1, (start+end)/2+1, end, idx, val);
		st[node] = op(st[2*node], st[2*node+1]);
	}
	T query(int node, int start, int end, int l, int r){
		if(start > r || end < l) return dummy;
		if(start >= l && end <= r) return st[node];

		return op(query(2*node, start, (start+end)/2, l, r), query(2*node+1, (start+end)/2 + 1, end, l, r));
	}
};

main(){
	int n, q, x, a, b;
	char c;
	cin >> n >> q;
	SegTree<int> seg(n, (int)1e9);
	for(int i = 0; i < n; ++i){
		cin >> x;
		seg.update(1, 0, n-1, i, x);
	}
	for(int i = 0; i < q; ++i){
		cin >> c >> a >> b;
		--a;
		--b;
		if(c == 'q') cout << seg.query(1, 0, n-1, a, b) << endl;
		else{ seg.update(1,0,n-1, a, ++b);}
	}
}
