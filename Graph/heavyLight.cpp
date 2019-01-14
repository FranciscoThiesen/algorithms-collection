#include <bits/stdc++.h>

using namespace std;

#define all(v) (v).begin(), (v).end()

using vi = vector<int>;
using ll = long long;

// Anudeep Implementation

constexpr int N = 100100;
int chainNo = 0, chainHead[N], chainPos[N], chainInd[N], chainSize[N];

void hld(int cur) {
    if( chainHead[chainNo] == -1) chainHead[chainNo] = cur;
    chainInd[cur] = chainNo;
    chainPos[cur] = chainSize[chainNo];
    chainSize[chainNo]++;

    int ind = -1, mai = -1;

    for(int i = 0; i < (int) adj[cur].size(); ++i) {
        if(subsize[ adj[cur][i] ] > mai) {
            mai = subsize[ adj[cur][i] ];
            ind = i;
        }
    }

    if( ind >= 0) hld( adj[cur][ind] );

    for(int i = 0; i < (int) adj[cur].size(); ++i) {
        if(i != ind) {
            chainNo++;
            hld( adj[cur][i] );
        }
    }
}

// v is an ancestor of u
int query_up(int u, int v) {
    if(u == v) return 0;
    
    int uchain, vchain = chainInd[v], ans = -1;
    while(1) {
        uchain = chainInd[u];
        if(uchain == vchain) {
            int cur = query_tree(1, 0, posInBase[v] + 1, posinBase[u] + 1);
            if( cur > ans ) ans = cur;
            break;
        }
        int cur = query_tree(1, 0, ptr, posInBase[chainHead[uchain]], posInBase[u] + 1);
        if( cur > ans) ans = cur;
        u = chainHead[uChain];
        u = parent(u);
    }
    return ans;
}
