// Tested with UVA - Interval Product

#include <bits/stdc++.h>

using namespace std;

using vi = vector<int>;

constexpr int ms = 1e5;

template <typename T>
struct SegmentTree {
    vector< T > tree;
    T id = 0;
    int N;
    
    SegmentTree(int n, T dummy) {
        id = dummy;
        N = n;
        tree.assign(4 * N, id);
    }
    
    T combine(const T& a, const T& b) { return a * b; }
    
    void buildTree( const vector< T >& arr, int stIndex, int lo, int hi) {
        if(lo == hi) {
            tree[stIndex] = arr[lo];
            return;
        }
        int left = 2 * stIndex, right = 2 * stIndex + 1, mid = (lo + hi) / 2;
        buildTree( arr, left, lo, mid);
        buildTree( arr, right, mid + 1, hi);
        tree[stIndex] = combine( tree[left], tree[right] );
    }
    
    void upd(const int stIndex, const int lo, const int hi, const int position, const T delta) {
        if(lo == hi) { 
            tree[stIndex] = delta; // can be +=, depends on the problem
            return;
        }
        int left = 2 * stIndex, right = 2 * stIndex + 1, mid = (lo + hi) / 2;
        if(position <= mid) upd(left, lo, mid, position, delta);
        else upd(right, mid + 1, hi, position, delta);
        tree[stIndex] = combine( tree[left], tree[right] );
    }
    
    // Closed-interval queries [lo, hi]
    T query(int stIndex, int left, int right, int lo, int hi) {
        if(left >= lo && right <= hi) return tree[stIndex];
        int mid = (left + right) / 2;
        if(lo > mid) return query( 2 * stIndex + 1, mid + 1, right, lo, hi);
        if(hi <= mid) return query( 2 * stIndex, left, mid, lo, hi);
        return combine( query(2 * stIndex, left, mid, lo, hi) ,
                        query(2 * stIndex + 1, mid + 1, right, lo, hi) );
    }
};

int main()
{
    //ios::sync_with_stdio(0);
    //cin.tie(0);
    int n, q;
    while(cin >> n >> q)
    {
        vector<int> orig(n);
        for(int& x : orig) {
            cin >> x;
            if(x > 0) x = 1;
            if(x < 0) x = -1;
        }
        SegmentTree<int> seg(n, 0);
        seg.buildTree(orig, 1, 0, n - 1);
        for(int i = 0; i < q; ++i)
        {
            char c; int x, y;
            cin >> c >> x >> y;
            if(c == 'C') {
                --x;
                if( y < 0) seg.upd(1, 0, n - 1, x, -1);
                else if(y == 0) seg.upd(1, 0, n - 1, x, 0);
                else seg.upd(1, 0, n - 1, x, 1);
            }
            else {
                --x;--y;
                int res = seg.query(1, 0, n - 1, x, y);
                if( res > 0) cout << '+';
                else if(res < 0) cout << '-';
                else cout << 0;
            }
        }
        cout << endl;
    } 
    
    return 0;
}
