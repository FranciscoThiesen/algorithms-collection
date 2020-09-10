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

// Works on DAG
const int maxn = 11;

vi adjList[maxn];
int visited[maxn] = {0};

vector<int> validSequence;

void dfsTopSort(int root)
{
	visited[root] = 1;
	for (int v: adjList[root])
	{
		if (!visited[v]) { dfsTopSort(v); }
	}
	validSequence.pb(root);
}
int main()
{
	int n, m, a, b;
	scanf("%d %d", &n, &m);
	rp(i, m)
	{
		scanf("%d %d", &a, &b);
		adjList[--a].pb(--b);
	}
	rp(i, n) if (!visited[i]) dfsTopSort(i);
	reverse(all(validSequence)); // crucial step!!
	for (int v: validSequence) printf("%d ", v + 1);
	return 0;
}
