#include <bits/stdc++.h>

// Tested for the problem ( https://codeforces.com/contest/342/problem/E )

using namespace std;

#define sz(x) (int) (x).size()
#define all(v) (v).begin(), (v).end()

// Debugging stuff
#define TRACE(x)
#define WATCH(x) TRACE(cout << #x " = " << x << endl;)
#define PRINT(x...) TRACE(printf(x))
#define WATCHR(a, b)                                                           \
	TRACE(for (auto c = a; c != b;) cout << *(c++) << " "; cout << endl;)
#define WATCHC(V)                                                              \
	TRACE({                                                                    \
		cout << #V " = ";                                                      \
		WATCHR(V.begin(), V.end());                                            \
	})
//

using vi = vector<int>;
using vvi = vector<vi>;

constexpr int inf = 0x3f3f3f3f;

struct centroid_decomposition
{
	int N;
	vvi centroid_graph;
	vi node_mapping, reverse_mapping, subtree_size, father;
	int centroid_count = 0;

	centroid_decomposition(const vvi& graph)
	{
		N = sz(graph);
		centroid_graph.resize(N);
		father.assign(N, -1);
		node_mapping.assign(N, -1);
		subtree_size.assign(N, 0);
		decompose(0, -1, graph);
		reverse_mapping.assign(N, -1);
		for (int i = 0; i < N; ++i) reverse_mapping[node_mapping[i]] = i;
	}

	void dfs(int loc, int par, const vvi& graph)
	{
		if (node_mapping[loc] != -1) return;
		for (const int& nxt: graph[loc])
		{
			if (node_mapping[nxt] == -1 && nxt != par)
			{
				dfs(nxt, loc, graph);
				subtree_size[loc] += subtree_size[nxt];
			}
		}

		subtree_size[loc] += 1;
	}

	int find_centroid(int loc, int par, int subtree_node_count,
					  const vvi& graph)
	{
		int largest_size = -1, largest_kid = loc;
		for (const int& nxt: graph[loc])
		{
			if (nxt != par)
			{
				if (subtree_size[nxt] > largest_size)
				{
					largest_size = subtree_size[nxt];
					largest_kid = nxt;
				}
			}
		}
		if (par != -1)
		{
			int total_upwards = subtree_node_count - subtree_size[loc];
			if (total_upwards > largest_size) { largest_kid = par; }
		}

		int tolerance = subtree_node_count / 2;
		if (largest_size <= tolerance) return loc;

		return find_centroid(largest_kid, loc, subtree_node_count, graph);
	}

	void decompose(int loc, const int par, const vvi& graph)
	{

		fill(all(subtree_size), 0);
		dfs(loc, -1, graph);

		int C = find_centroid(loc, -1, subtree_size[loc], graph);

		node_mapping[C] = centroid_count++;

		if (par != -1)
		{
			centroid_graph[node_mapping[par]].push_back(node_mapping[C]);
			father[node_mapping[C]] = node_mapping[par];
		}

		for (const int& nxt: graph[C])
		{
			if (node_mapping[nxt] == -1) decompose(nxt, C, graph);
		}
	}
};

struct lca
{
	int L, N;
	vector<int> depth, size, link;

	lca() {}
	lca(const vvi& graph, int root = 0)
	{
		N = graph.size();
		for (L = 0; (1 << L) <= N; L++)
			;
		depth.resize(N), size.resize(N);
		link.resize(L * N);
		init(root, root, graph);
	}
	void init(int loc, int par, const vvi& graph)
	{
		link[loc] = par;
		for (int l = 1; l < L; l++)
			link[l * N + loc] = link[(l - 1) * N + link[(l - 1) * N + loc]];
		for (int nbr: graph[loc])
		{
			if (nbr == par) continue;
			depth[nbr] = depth[loc] + 1;
			init(nbr, loc, graph);
			size[loc] += size[nbr];
		}
		size[loc]++;
	}
	inline int above(int loc, int dist)
	{
		for (int l = 0; l < L; l++)
			if ((dist >> l) & 1) loc = link[l * N + loc];
		return loc;
	}

	int find(int u, int v)
	{
		if (depth[u] > depth[v]) swap(u, v);
		v = above(v, depth[v] - depth[u]);
		if (u == v) return u;

		for (int l = L - 1; l >= 0; l--)
		{
			if (link[l * N + u] != link[l * N + v])
				u = link[l * N + u], v = link[l * N + v];
		}

		return link[u];
	}
};

inline int calculate_distance(int u, int v, lca& memo)
{
	int LCA = memo.find(u, v);
	return (memo.depth[u] + memo.depth[v] - 2 * memo.depth[LCA]);
}

int main()
{
	int n, q;

	scanf("%d %d", &n, &q);
	vvi g(n);

	for (int i = 0; i < n - 1; ++i)
	{
		int a, b;
		scanf("%d %d", &a, &b);
		--a;
		--b;
		g[a].push_back(b);
		g[b].push_back(a);
	}

	centroid_decomposition xablau(g);

	lca arv(g);

	deque<bool> color(n, 0);

	vector<pair<int, int>> closest(n, pair<int, int>(-1, inf));

	int LGMAX;

	for (LGMAX = 0; (1 << LGMAX) <= n; ++LGMAX)
		;

	vvi ancDist(n, vi(LGMAX, -1));

	// Encontrando as distancias de um no e seus ancestrais da decomposicao, na
	// arvore original
	for (int i = 0; i < n; ++i)
	{
		int old_node_value = xablau.reverse_mapping[i];
		int cur = xablau.father[i];
		ancDist[i][0] = 0;
		int lvl = 1;
		while (cur != -1)
		{
			int old_cur_value = xablau.reverse_mapping[cur];
			ancDist[i][lvl] =
				calculate_distance(old_node_value, old_cur_value, arv);
			cur = xablau.father[cur];
			++lvl;
		}
	}

	// Node 0 is already colored at the beginning
	int x = xablau.node_mapping[0];
	color[x] = 1;
	int lvl = 0, current = x;
	while (current != -1)
	{
		int bestCurr = closest[current].second;
		if (ancDist[x][lvl] < bestCurr)
		{
			bestCurr = ancDist[x][lvl];
			closest[current] =
				make_pair(xablau.reverse_mapping[x] + 1, ancDist[x][lvl]);
		}
		++lvl;
		current = xablau.father[current];
	}
	// End insertion of node 0
	//

	while (q--)
	{
		int t, x;
		scanf("%d %d", &t, &x);
		--x;
		x = xablau.node_mapping[x];
		if (t == 1)
		{
			color[x] = 1;
			int lvl = 0;
			int current = x;
			while (current != -1)
			{
				int bestCurrent = closest[current].second;
				if (ancDist[x][lvl] < bestCurrent)
				{
					closest[current] = make_pair(xablau.reverse_mapping[x] + 1,
												 ancDist[x][lvl]);
					bestCurrent = ancDist[x][lvl];
				}
				current = xablau.father[current];
				++lvl;
			}
		}
		else
		{
			// hora do show porra
			int best = closest[x].second;
			int current = x;
			int lvl = 0;
			while (current != -1)
			{
				if (closest[current].first != -1)
				{
					int top = closest[current].second;
					int inc = ancDist[x][lvl];
					if (top + inc < best) { best = top + inc; }
				}
				++lvl;
				current = xablau.father[current];
			}
			printf("%d\n", best);
		}
	}
	return 0;
}
