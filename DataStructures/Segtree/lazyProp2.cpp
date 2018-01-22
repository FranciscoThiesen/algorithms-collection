#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i,a,b) for(int (i) = (a); (i) < (b); ++(i))
#define all(v) (v).begin(), (v).end()
#define buff ios::sync_with_stdio(0);cin.tie(0);

typedef vector<int> vi;
typedef pair<int, int> ii;

struct node{
	int vet[9] = {0,0,0,0,0,0,0,0,0};
};
// funcao que retorna o valor de maior frequencia
inline int maisFrequente(const node& a){
	int best = -1;
	int nota = -1;
	rep(i,0,9){
		if(a.vet[i] >= best){
			best = a.vet[i];
			nota = i;
		}
	}
	return nota;
}

struct seg{
	int N;
	vector<node> Tree;
	vector<int> lazy;
	node id;
	int h;

	// combinando 2 nos
	node combine(const node& a, const node& b){
		node unite;
		rep(i,0,9){
			unite.vet[i] = a.vet[i] + b.vet[i];
		}
		return unite;
	}

	void modify(node& a, int chg){
		node s;
		rep(i,0,9){
			s.vet[(i+chg)%9] = a.vet[i];
		}
		a = s;
	}

	seg(int n){
		N = n;
		Tree.assign(2*N, id);
		lazy.assign(2*N, 0);
		h = sizeof(int) * 8 - __builtin_clz(N);
	}

	// aplica uma mudanca
	void apply(int p, int value){
		modify(Tree[p], value);
		// se nao estamos lidando com uma folha
		if(p < N) lazy[p] += value;
	}

	void buildIt(){
		for(int i = N-1; i > 0; --i) Tree[i] = combine(Tree[i<<1], Tree[i<<1 | 1]);
	}

	void build(int p){
		node tmp;
		while(p > 1){
			p >>= 1;
			tmp = combine(Tree[p << 1], Tree[p << 1 | 1]);
			modify(tmp, lazy[p]);
			Tree[p] = tmp;
		}
	}

	void push(int p){
		for(int s = h; s > 0; --s){
			int i = p >> s;
			if(lazy[i] != 0){
				apply(i<<1, lazy[i]);
				apply(i<<1 | 1, lazy[i]);
				lazy[i] = 0;
			}
		}
	}

	void update(int l, int r, int value){
		l += N, r += N;
		int l0 = l, r0 = r;
		for(; l < r; l >>= 1, r >>= 1){
			if(l&1) apply(l++, value);
			if(r&1) apply(--r, value);
		}
		build(l0);
		build(r0 - 1);
	}

	int query(int l, int r){
		l += N, r += N;
		push(l);
		push(r);
		node res = id;
		for(; l < r; l >>= 1, r >>= 1){
			if(l&1) res = combine( res, Tree[l++]);
			if(r&1) res = combine( res, Tree[--r]);
		}
		return maisFrequente(res);
	}
};


int main(){
	int n, q, a, b, x;
	buff;
	cin >> n >> q;
	node tmp;
	tmp.vet[1] = 1;
	seg arv(n);
	rep(i,0,n) arv.Tree[i+n] = tmp;
	arv.buildIt();
	rep(i, 0, q){
		cin >> a >> b;
		x = arv.query(a, b+1);
		arv.update(a, b+1, x);
	}
	rep(i,0,n){
		cout << arv.query(i, i+1) << endl;
	}
	return 0;
}
