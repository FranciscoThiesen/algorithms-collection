#include <bits/stdc++.h>

using namespace std;
#define TRACE(x)  
#define rep(i, a, b) for(int (i) = (a); (i) < (b); ++(i))
#define rp(i, a) rep(i, 0, a)
#define all(v) (v).begin(), (v).end()
#define sz(v) (int) (v).size()

using vi = vector<int>;
using pii = pair<int, int>;
using ll = long long;
using vll = vector<ll>;

constexpr int oo = 0x3f3f3f3f;
constexpr long long mod = 1e9 + 7ll;

struct centroid_decomposition {
    
    centroid_decomposition() {}

    int centroid(int root, const vector<vi>& g, const deque<bool>& dead) {
        static vector<int> subtree_sz( sz(g) );
         
        function< void(int, int)> get_sz = [&] (int loc, int par) {
            subtree_sz[loc] = 1;
            for(auto& nei : g[loc]) {
                if( nei != par && !dead[nei]) {
                    get_sz(nei, loc);
                    subtree_sz[loc] += subtree_sz[nei];
                }
            }
        };

        get_sz(root, -1);
        int n = subtree_sz[root];

        function<int(int, int)> dfs = [&] (int loc, int par ) {
            for(auto& v : g[loc]) {
                if( v != par && !dead[v] ) {
                    if(subtree_sz[v] > n / 2) {
                        return dfs(v, loc);
                    }
                }
            }
            return loc;
        };

        return dfs(root, -1);
    }

    long long doit( const vector< vi >& g, const int k ) {
        int n = sz(g);
        long long ans = 0; 
        deque<bool> dead(n, false);
        
        function< map<int, long long> (int, int) > process_subtree = [&] ( int root, int parent ) {
            map<int, long long> path_count;
            
            function< void(int, int, int) > explore = [&] (int root, int parent, int dist) { 
                if( dist <= k ) path_count[dist]++;
                else return;
                for(const auto& nei : g[root] ) {
                    if( !dead[nei] && nei != parent ) {
                        explore( nei, root, dist + 1); 
                    }
                } 
            };
            explore( root, parent, 1);
            
            return path_count;
        };

        function< void(int) > rec = [&] (int start) {
            int c = centroid(start, g, dead);
            dead[c] = true;
            map<int, long long> general_count;
            general_count[0] = 1ll;
            TRACE( cout << " primeiro centroid = " << c << endl; ) 
            for(const int& nei : g[c] ) {
                if( !dead[nei] ) {
                    auto fuark = process_subtree(nei, c);
                    TRACE( cout << "estou processando o filho do 0 = " << nei << endl; )
                    TRACE( 
                        for(const auto& v : fuark) cout << v.first << " " << v.second << endl; )
                    for(const auto& val : fuark) {
                        int complemento = k - val.first; 
                        TRACE( cout << " val = " << val.first << " comp = " << complemento << endl; )
                        ans = ( ans + (val.second * general_count[complemento]) );
                        ans = (ans % mod );
                    }
                    TRACE ( cout << " apos processar " << nei << " ans = " << ans << endl; )
                    for(const auto& val : fuark) general_count[val.first] += val.second;
                }
            }
            for(auto u : g[c]) if( !dead[u] ) rec(u);
        };
    
        rec(0);
        TRACE( cout << " ANS = " << ans << endl; ) 
        long long mult = ( (1LL * k * (k + 1 ) ) / 2LL ) % mod;
        mult = (mult * ans) % mod;
        return mult;
    }

};

int main() {
    ios::sync_with_stdio( false ); cin.tie(NULL);
    int n, k;
    cin >> n >> k;
    vector< vi > g(n);
    for(int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    centroid_decomposition x;
    cout << x.doit(g, k ) << endl; 
}
