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

const int maxn = 401;

int dist[maxn][maxn];
int n, m, q, a, b, c;

void floydWarshall(){
	rp(z, n){
		rp(x, n){
			rp(y,n){
				if(dist[x][z] != inf && dist[z][y] != inf){
					dist[x][y] = min(dist[x][y], dist[x][z] + dist[z][y]);
				}
			}
		}
	}
}

int main(){
	memset(dist, inf, sizeof dist);
	scanf("%d %d", &n, &m);
	rp(i, m){
		scanf("%d %d %d", &a, &b, &c);
		dist[--a][--b] = min(dist[a][b], c); 
	}
	floydWarshall();
	return 0;
}

