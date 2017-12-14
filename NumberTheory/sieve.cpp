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
const int MAXN = 100010;

vector<int> sp(MAXN, -1);


// Sieve that runs in complexity O(n log log n)
vi sieve(int limit){
	vi primes;
	for(int i = 2; i < limit; ++i){
		if(sp[i] == -1){
			sp[i] = i;
			primes.pb(i);
			for(int j = i*i; j < limit; j += i){
				if(sp[j] == -1) sp[j] = i;
			}
		}
	}
	return primes;
}

// near constant time after the sieve
vi primFact1(int x){
	vi ret;
	while(x != 1){
		ret.pb(sp[x]);
		x /= sp[x];
	}
	return ret;
}

// version without the sieve
vi primFact2(int x){
	vi fact;
	for(int i = 2; i <= ceil(sqrt(x)); ++i){
		if(!(x%i)){
			fact.pb(i);
			while(x%i == 0) x /= i;
		}
	}
	if(x != 1) fact.pb(x);
	return fact;
}

int main(){
	vi k = sieve(10000);
	vi tmp = primFact1(2743);
	vi tmp2 = primFact2(2743);
	for(const int& v : tmp){
		cout << v << " ";
	}
	cout << endl;
	for(const int& v : tmp2) cout << v << " ";
	cout << endl;
	return 0;
}

