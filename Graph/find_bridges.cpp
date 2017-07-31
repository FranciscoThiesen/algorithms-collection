#include <bits/stdc++.h>

using namespace std;

#define F(i, a, n) for(int i = a; i < n; ++i)
#define FD(i, n, a) for(int i = n; i >= a; --i)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define sz(x) ((int)(x).size())
#define mod 1000 * 1000 * 1000 + 7
#define MAXN 10010

typedef vector<int> vi;
typedef long long ll;
typedef unsigned long long ull;

vector<vector<int> > adjList(MAXN);

void find_aps(int u, vector<bool>& visited, vector<int>& discoveryTime, vector<int>& low, vector<int>& parent, vector<bool>& articulationPoint, vector<vector<int>>& adjList)
{
	static int time = 0;
	int children = 0;
	visited[u] = true;
	discoveryTime[u] = low[u] = ++time;

	for(auto& p : adjList[u])
	{
		if(!visited[p])
		{
			children++;
			parent[p] = u;
			find_aps(p, visited, discoveryTime, low, parent, articulationPoint, adjList);

			// Checando se a subarvore com raiz p tem uma conexao com algum dos ancestrais de u
			low[u] = min(low[u], low[p]);

			// Checando se u eh articulation point, sao dois casos possiveis

			if(parent[u] != -1 && low[p] > discoveryTime[u])
				cout << "Existe uma ponte entre " << u << " " << p << endl;

		}

		else if( p != parent[u])
			low[u] = min(low[u], discoveryTime[p]);
	}
}

int main()
{
	vector<bool> visited(MAXN, false);
	vector<int> discoveryTime(MAXN, 0);
	vector<int> low(MAXN, 0);
	vector<int> parent(MAXN, -1);
	vector<bool> articulationPoint(MAXN, false);
	int nodes = 1, edges = 1;	
	while(edges + nodes > 0)
	{
		cin >> nodes >> edges;
		if(nodes + edges == 0)
			break;

		for(int i = 0; i < edges; ++i)
		{
			int x, y;
			cin >> x >> y;
			adjList[x].pb(y);
			adjList[y].pb(x);

		}	

		for(int i = 1; i <= nodes; ++i)
		{
			if(!visited[i])
			{
				find_aps(i, visited, discoveryTime, low, parent, articulationPoint, adjList);	
			}
		}
		int ans = 0;
		for(int i = 1; i <= nodes; ++i)
		{
			if(articulationPoint[i] == true)
				ans++;
		}

		printf("%d\n", ans);

		fill(visited.begin(), visited.end(), false);
		fill(discoveryTime.begin(), discoveryTime.end(), 0);
		fill(low.begin(), low.end(), -1);
		fill(parent.begin(), parent.end(), -1);
		fill(articulationPoint.begin(), articulationPoint.end(), false);

		for(int i = 0; i < adjList.size(); ++i)
			adjList[i].clear();
	}
	return 0;
}
