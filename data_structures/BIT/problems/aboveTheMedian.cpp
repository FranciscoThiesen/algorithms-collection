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
		while(pos < size){
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

main(){
	int n, k, x;
	scanf("%d %d", &n, &k);
	vector<int> v(n);
	vector<int> accu(n+1, 0);
	BIT arv(2*n + 1);
	accu[0] = n;
	ll resp = 0;
	arv.update(n, 1);

	for(int i = 0; i < n; ++i){
		scanf("%d", &x);
		x = (x >= k)? 1 : -1;
		accu[i+1] = accu[i] + x;
		resp += arv.rangeSum(0, accu[i+1]);
		arv.update(accu[i+1], 1);
	}
	printf("%lld\n", resp);
}

