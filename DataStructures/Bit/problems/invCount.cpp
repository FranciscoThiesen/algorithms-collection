#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define all(v) (v).begin(), (v).end()
#define pb push_back
#define mp make_pair

typedef vector<int> vi;
typedef long long ll;

int lsb(int i){ return i & -i;}
struct BIT{
	int size;
	vi table;
	BIT(int sz){
		table.resize(sz+1, 0);
		size = sz+1;
	}
	
	void update(int pos, int delta){
		++pos;
		while(pos <= size){
			table[pos] += delta;
			pos += lsb(pos);
		}
	}
	int sum(int i){
		++i;
		int sum = 0;
		while(i > 0){
			sum += table[i];
			i -= lsb(i);
		}
		return sum;
	}
	int rangeSum(int l, int r){
		return sum(r) - sum(l-1);
	}
};

const int maxn = 2 * 1e5 + 5;

main(){
	ll resp = 0;
	int t, n, x;
	scanf("%d", &t);
	while(t--){
		resp = 0;
		scanf("%d", &n);
		BIT arv(maxn);
		for(int i = 0; i < n; ++i){
			scanf("%d", &x);
			resp += arv.rangeSum(x, maxn);
			arv.update(x, 1);
		}
		printf("%lld\n", resp);
	}
}