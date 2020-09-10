#include <bits/stdc++.h>

using namespace std;

template <typename T> struct FenwickTree
{
	vector<T> ft1, ft2;
	int N;

	FenwickTree(int n)
	{
		ft1.resize(n + 1, 0);
		ft2.resize(n + 1, 0);
		N = n + 1;
	}
	T internalQuery(vector<T>& ft, int i)
	{
		T sum = 0;
		++i;
		while (i > 0)
		{
			sum += ft[i];
			i -= (i & -i);
		}
		return sum;
	}

	void update(vector<T>& ft, int i, T v)
	{
		++i;
		while (i < N)
		{
			ft[i] += v;
			i += (i & -i);
		}
	}

	void update(int i, int j, T v)
	{ // 0-indexed
		update(ft1, i, v);
		update(ft1, j + 1, -v);
		update(ft2, i, v * (i - 1));
		update(ft2, j + 1, -v * j);
	}
	T query(int i)
	{ // 0-indexed
		return internalQuery(ft1, i) * i - internalQuery(ft2, i);
	}

	T query(int i, int j)
	{ // queries for a closed interval [i, j]   0-indexed
		return query(j) - query(i - 1);
	}
};

// small test program!
/*
int vet[10009];
int sum(int a, int b){
	int ans = vet[a];
	for(int i=a+1; i<=b; i++) ans += vet[i];
	return ans;
}

void update(int a, int b, int k){
	for(int i=a; i<=b; i++) vet[i] += k;
}


int main() {
	int N = 10000, a, b, k;
	srand(time(NULL));
	FenwickTree<int> ft(N);
	for(int i=1; i<=N; i++){
		vet[i] = rand()%N;
		ft.update(i, i, vet[i]);
	}
	for(int q=0; q<100; q++){

		printf("test #%d:", q+1);
		a = (rand()%N);
		b = (rand()%N);
		if (a>b) swap(a, b);
		k = rand()%100;
		printf(" %d to %d plus %d\n", a, b, k);

		update(a, b, k);
		ft.update(a, b, k);

		a = (rand()%N);
		b = (rand()%N);
		if (a>b) swap(a, b);

		if (sum(a, b) != ft.query(a, b)) printf("test failed\n");
	}
	return 0;
}
*/
