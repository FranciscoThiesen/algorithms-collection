#include <bits/stdc++.h>

using namespace std;

#define fr(i, a, b) for (int(i) = (a); (i) < (b); ++(i))
#define rp(i, n) fr(i, 0, n)
#define fi first
#define se second
#define all(v) (v).begin(), (v).end()
#define pb push_back
#define mt make_tuple
#define mp make_pair
#define sz(a) (int) (a.size())

typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
const int inf = 0x3f3f3f3f;
const int neginf = 0xc0c0c0c0;

const int maxn = 10005;

vii adjList[maxn];
int dist[maxn];

void dijkstra(int root)
{
	memset(dist, inf, sizeof dist);
	dist[root] = 0;
	set<ii> pq;
	pq.insert(mp(0, root));

	while (!pq.empty())
	{
		ii tp = *(pq.begin());
		pq.erase(pq.begin());
		for (auto v: adjList[tp.se])
		{
			if (tp.fi + v.fi < dist[v.se])
			{
				if (dist[v.se] != inf)
				{ pq.erase(pq.find(mp(dist[v.se], v.se))); }
				dist[v.se] = tp.fi + v.fi;
				pq.insert(mp(dist[v.se], v.se));
			}
		}
	}
}
