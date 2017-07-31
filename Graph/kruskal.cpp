/* 
	I'd like to thank for the help of Daniel Fleischman, who called 
	my attention to several errors on previous UnionFind implementations
*/
#include <bits/stdc++.h>

using namespace std;

#define fr(i,a,b) for(int (i) = (a); (i) < (b); ++(i))
#define rp(i,n) fr(i,0,n)
#define fi first
#define se second
#define all(v) (v).begin(), (v).end()
#define pb push_back
#define mt make_tuple
#define mp make_pair
#define sz(a) (int)(a.size())

typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;

const int inf = 0x3f3f3f3f;
const int neginf = 0xc0c0c0c0;

vector<tuple<int, int, int> > edges;
int n, m, a, b, c;

struct UF{
	vi parent, rank;
	
	UF(int n){
		parent.resize(n);
		rank.assign(n, 0);
		iota(all(parent), 0);
	}
	int findParent(int v){
		if(parent[v] != v) parent[v] = findParent(parent[v]);
		return parent[v];
	}
	bool unite(int a, int b){
		a = findParent(a);
		b = findParent(b);
		if(a == b) return false;
		if(rank[a] < rank[b]) parent[a] = b;
		else parent[b] = a;
		rank[a] += (rank[a] == rank[b]);
		return true;
	}
};

int main(){
	scanf("%d %d", &n, &m);
	UF gp(n);
	rp(i, m){
		scanf("%d %d %d", &a, &b, &c);
		edges.pb(mt(c,a-1,b-1));
	}
	sort(all(edges));
	int resp = 0;
	for(auto e : edges){
		if(gp.unite(get<1>(e), get<2>(e)))
			resp += get<0>(e);
	}
	printf("%d\n", resp);
	return 0;
}

