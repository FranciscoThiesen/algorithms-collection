/*input

*/
#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define all(v) (v).begin(), (v).end()
#define pb push_back
#define mp make_pair

typedef vector<int> vi;

int lsb(int i){ return i & -i;}
// Classic idea -> Point query, Point update all in O(log n)
struct BIT{
	int size;
	vi table;
	BIT(int sz){
		table.resize(sz+1, 0);
		size = sz+1;
	}
	// update position pos by delta
	// pos is zero indexed
	void update(int pos, int delta){
		++pos;
		while(pos <= size){
			table[pos] += delta;
			pos += lsb(pos);
		}
	}
	//the i parameter is 0 indexed
	int sum(int i){
		++i;
		int sum = 0;
		while(i > 0){
			sum += table[i];
			i -= lsb(i);
		}
		return sum;
	}
	// range sum, l and r are 0-indexed
	int rangeSum(int l, int r){
		return sum(r+1) - sum(l);
	}
};

const int maxn = 1048576;
BIT freq(maxn);
vector<int> f(maxn, 0);
int accuSum = 0;

int query(int kth){
	if(kth > accuSum){
		cout << "Invalid Query" << endl;
		return -1;
	}
	int hi = maxn;
	int lo = 0;
	int mid;
	while(lo < hi){
		mid = (hi + lo) >> 1;
		int sm = freq.sum(mid);
		if(sm == kth) return mid;
		if(sm < kth){
			lo = mid+1;
		}
		else hi = mid;
	}
	return lo;
}

int update(int height, int delta){
	freq.update(height, delta);
	accuSum += delta;
}

int main(){
	// small array for algorithm manual testing
	// and for easier debugging
	vector<int> h(16,0);
	h[0] = 8;
	h[1] = 2;
	h[2] = 10;
	h[3] = 100;
	h[4] = 1;
	h[5] = 2;
	for(int i = 0; i < 16; ++i)
		update(i, h[i]);
	for(int i = 15; i >= 0; --i)
		cout << freq.table[i] << endl;

	cout << query(21) << endl;

}