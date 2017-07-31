#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define all(v) (v).begin(), (v).end()
#define pb push_back
#define mp make_pair

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef long long ll;

int lsb(int i){ return i & -i;}
struct BIT2D{
	int size;
	vvi table;
	int N, M;
	BIT2D(int n, int m){
		table.resize(n+1, vector<int>(m+1, 0)); // 0-indexed
		N = n+1;
		M = m+1;
	}
	
	int query(int i, int j){ // 0-indexed, returns sum of the rectangle defined by (0,0) (i, j)
		++i;++j;
		int sum = 0, tmpJ = j;
		while(i > 0){
			j = tmpJ;
			while(j > 0){
				sum += table[i][j];
				j -= lsb(j);
			}
			i -= lsb(i);
		}
		return sum;
	}

	void update(int i, int j, int delta){ // 0-indexed
		++i;++j;
		int tmpJ = j;
		while(i < N){
			j = tmpJ;
			while(j < M){
				table[i][j] += delta;
				j += lsb(j);
			}
			i += lsb(i);
		}
	}
};



const int N = 500;
vector<vector<int> > A(N+1, vector<int>(N+1));

int rsq(int x, int y) {
	int ans = 0;
	for(int i=0; i<=x; i++){
		for(int j=0; j<=y; j++){
			ans += A[i][j];
		}
	}
	return ans;
}

void update(int x, int y, int v) {
	A[x][y] += v;
}

// Testing function
bool test(){
	cout << "what" << endl;
	int nTests = 10000;
	int x, y, v;
	BIT2D ft(N, N);
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			A[i][j] = rand() % N;
			ft.update(i, j, A[i][j]);
		}
	}
	cout << "Comecando os testes " << endl;
	cout << "Comecando os testes 2 " << endl;
	for(int q=0; q < nTests; q++){
		x = rand()%N;
		y = rand()%N;
		v = rand()%N;
		ft.update(x, y, v);
		update(x, y, v);
		cout << "passei " << endl;
		x = rand()%N;
		y = rand()%N;
		int q1 = rsq(x, y);
		int q2 = ft.query(x, y);
		if (q1 != q2){
			printf("Failed test %d, q1 = %d, q2 = %d\n", q, q1, q2);
			return false;
		}
	}
	printf("all tests passed\n");
	return true;
}

int main() {
	test();
	return 0;
}