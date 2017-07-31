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

constexpr int maxn = 1001;

vi adjList[maxn];
int dist[maxn];

void bfs(int root){
	memset(dist, inf, sizeof dist);
	
	dist[root] = 0;
	queue<int> q;
	q.push(root);

	while(!q.empty()){
		int u = q.front();
		q.pop();
		for(int v : adjList[u]){
			if(dist[v] == inf){
				dist[v] = dist[u] + 1;
				q.push(v);
			}
		}
	}
}
