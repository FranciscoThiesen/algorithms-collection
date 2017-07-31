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
		return sum(r) - sum(l-1);
	}
};

// given an array count the number of inversions
// inversion -> pair of elements (A[i], A[j]) such that 
// i < j && A[i] > A[j]

int countInversion(vector<int>& vec){
	
	int mx = - (1e9);
	for(auto v : vec) mx = max(mx, v);
	BIT x(mx);
	int resp = 0;
	for(auto v : vec){		
		resp += x.sum(mx) - x.sum(v);
		x.update(v, 1);
	}
	return resp;
}

int main(){
	vector<int> st{1,2,3,4,5};
	vector<int> inv{7,6,2,3,1,4,5};
	BIT b(5);
	for(int i = 0; i < st.size(); ++i)
		b.update(i, st[i]);

	for(int i = 0; i < 5; ++i)
		cout << b.sum(i) << " soma ate i = " << i << endl;
	
	cout << b.rangeSum(1,2) << endl;
	//cout << "total Inversions = " << countInversion(inv) << endl;
	return 0;
}

