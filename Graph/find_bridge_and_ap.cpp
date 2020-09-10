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

const int inf = 0x3f3f3f3f;
const int neginf = 0xc0c0c0c0;
const int maxn = 10001;

vi adjList[maxn];
// low[u] = vertice de menor indice da dfs tree que consigo alcancar via aresta
// de retorno d[u] = tempo de descoberta f[u] = tempo que terminei de processar
// o vertice u seen[u] ..
int d[maxn], f[maxn], low[maxn], seen[maxn];

int globalTime = 0;
int root = 0, n, m, a, b;
vector<ii> bridge;
vi ap;

void dfs(int u, int parent)
{
	seen[u] = 1;
	int kids = 0;
	d[u] = low[u] = globalTime++;
	bool noReturn = false;
	for (int v: adjList[u])
	{
		if (!seen[v])
		{
			dfs(v, u);
			kids++;
			if (low[v] >= d[u]) noReturn = true;
			low[u] = min(low[u], low[v]);
			if (low[v] > d[u]) bridge.pb(mp(u, v));
		}
		else if (v != parent)
			low[u] = min(low[u], d[v]); // aresta de retorno
	}
	if (u == root && kids >= 2) ap.pb(u);
	else if (u != root && noReturn)
		ap.pb(u);
}

main()
{
	memset(d, 0, sizeof d);
	memset(f, 0, sizeof f);
	memset(low, inf, sizeof low);
	memset(seen, 0, sizeof seen);
	scanf("%d %d", &n, &m);
	rp(i, m)
	{
		scanf("%d %d", &a, &b);
		adjList[a].pb(b);
		adjList[b].pb(a);
	}
	rp(i, n)
	{
		if (!seen[i]) { dfs(i, -1); }
	}
	printf("%d\n", sz(ap));
	sort(all(ap));
	for (int v: ap) printf("%d ", v);
	puts("");
	printf("%d\n", sz(bridge));
	sort(all(bridge));
	for (ii e: bridge) { printf("%d %d\n", e.fi, e.se); }
}
