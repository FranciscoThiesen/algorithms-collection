#include <bits/stdc++.h>

using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

struct centroid_decomposition {
    vvi centroid_graph;
    vvi reverse_graph;
    vi node_mapping;

    int find_centroid(int root, const vvi& g, const deque<bool>& dead) {
        static vi sz( (int) g.size() );
        function<void (int, int) > get_sz = [&] (int loc, int par) {
            for(int nei : g[loc] ) {
                if( nei != par && !dead[nei]) {
                    get_sz(nei, loc);
                    sz[loc] += sz[nei];
                }
            }
            sz[loc]++;
        };

        get_sz(root, -1);
    
        int n = sz[root];

        function<int (int, int) > dfs = [&] (int loc, int par) {
            for(int nei : g[loc]) {
                if( nei != par && !dead[nei]) {
                    if( sz[nei] > n / 2 ) {
                        return dfs(nei, loc);
                    }
                }
            }
            return loc;
        };
        return dfs(root, -1);
    }

    centroid_decomposition(const vvi& g) {
        int N = (int) g.size();
        deque<bool> dead(N, false);
        centroid_graph.resize(N);
        reverse_graph.resize(N);
        function<void (int, int) > rec = [&] (int loc, int par) {
            int nextCentroid = find_centroid(loc, g, dead);
            dead[nextCentroid] = true;
            
            if( par != -1) {
                centroid_graph[par].push_back( nextCentroid );
                reverse_graph[nextCentroid].push_back( par );
            }
            
            for(int nei : g[nextCentroid] ) { 
                if(!dead[nei]) rec(nei, nextCentroid);
            }

            dead[nextCentroid] = false; // ??
        };
        rec(0, -1);
    }
};


struct lca {
    int L, N;
    vector<int> depth, size, link;

    lca(){}
    lca(const vvi &graph, int root = 0) {
        N = graph.size();
        for (L = 0; (1 << L) <= N; L++);
        depth.resize(N), size.resize(N);
        link.resize(L*N);
        init(root, root, graph);
    }
    void init(int loc, int par, const vvi &graph) {
        link[loc] = par;
        for (int l = 1; l < L; l++)
            link[l*N + loc] = link[(l-1)*N + link[(l-1)*N + loc]];
        for (int nbr : graph[loc]) {
            if (nbr == par) continue;
            depth[nbr] = depth[loc] + 1;
            init(nbr, loc, graph);
            size[loc] += size[nbr];
        }
        size[loc]++;
    }
    
    inline int above(int loc, int dist) {
        for (int l = 0; l < L; l++)
            if ((dist >> l)&1)
                loc = link[l*N + loc];
            return loc;
        }

        int find(int u, int v) {
        if (depth[u] > depth[v]) swap(u, v);
        v = above(v, depth[v] - depth[u]);
        if (u == v) return u;

        for (int l = L - 1; l >= 0; l--) {
            if (link[l*N + u] != link[l*N + v])
                u = link[l*N + u], v = link[l*N + v];
        }

        return link[u];
    }
};

inline int calculate_distance(int u, int v, lca& memo) {
    int LCA = memo.find(u, v); 
    return (memo.depth[u] + memo.depth[v] - 2 * memo.depth[LCA] );
}

constexpr int inf = 0x3f3f3f3f;

int main()
{
    int n, q;
    scanf("%d %d", &n, &q);
    vvi g(n);
    for(int i = 0; i < n - 1; ++i) {
        int a, b; cin >> a >> b;
        --a;--b;
        g[a].pb(b);
        g[b].pb(a);
    }
    
    vi closest(n, inf);
    closest[0] = 0;
    
    int L = 0;
    for(L = 0; (1 << L) <= n; ++L);

    vector< vi > dist(n, vector<int>(L, inf) );
    
    lca links = 
    centroid_decomposition CD = centroid_decomposition(g);

    for(int i = 0; i < n; ++i) {
        
    }

    for(int i = 0; i < m; ++i) {

    }
}
