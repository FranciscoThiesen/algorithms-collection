#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define all(v) (v).begin(), (v).end()
#define sz(v) (int) (v).size()

using vi = vector<int>;

constexpr int ms = 2 * 1e5 + 13;

struct node
{
    vi sorted_values;
    long long inversions = 0LL;
    node() {}
}


struct mergeSortTree {
    int n;
    vector<node> tree;

    mergeSortTree(int _n) : n(_n) { tree.resize(4 * n); }
    
    void combine(node& destination, const node& a, const node& b ) {
        destination.inversions = (a.inversions + b.inversions); 
        int idxA = 0, idxB = 0; 
        int szA = sz(a.sorted_values), szB = sz(b.sorted_values); 
        while(idxA < szA || idxB < szB) {
            if(idxA == szA) {
                while(idxB < szB) {
                    destination.sorted_values.push_back( b.sorted_values[idxB++] );
                }
            }
            else if( idxB == szB) {
                while(idxA < szA) {
                    destination.sorted_values.push_back( a.sorted_values[idxA++] );
                }
            }
            else
            {
                if( a.sorted_values[idxA] <= b.sorted_values[idxB] ) {
                    destination.sorted_values.push_back( a.sorted_values[idxA++] );
                }
                else {
                    destination.inversions += (szA - idxA + 1);
                    destination.sorted_values.push_back( b.sorted_values[idxB++] ); 
                }
            }
        }
    }

    void build( vector<int>& vals, int idx, int lo, int hi ) {
        if( lo == hi ) {
            node[idx].push_back( vals[lo] );
            return;
        }
        else
        {
            int mid = (lo + hi) / 2;
            build(vals, 2 * idx, lo, mid);
            build(vals, 2 * idx + 1, mid + 1, hi);
            combine( tree[idx], tree[2 * idx], tree[2 * idx + 1] );
        }
    }

    void update( int idx, int lo, int hi, int pos, int val) {
        if(pos < lo || pos > hi) return;
        if(lo == hi) node[idx][0] = val;
        else {
            int mid = (lo + hi) / 2;
            build( 2 * idx, lo, mid, pos, val);
            build( 2 * idx + 1, mid + 1, hi, pos, val);
            
        }
    }
}

int main()
{

}
