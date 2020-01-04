#include <bits/stdc++.h>
#define rep(i,a,b) for(int (i) = (a); (i) < (b); ++(i))
using namespace std;

// Foi testado para o seguinte problema ( https://codeforces.com/contest/52/problem/C )
template <typename T>
struct SegmentTree {
    vector<T> tree, lazy;
    T id;
    T neutral;
    int n;
    SegmentTree(int _n, T _id, T _neutral) : n(_n), id(_id), neutral(_neutral) {
        tree.assign(4*n, id);
        lazy.assign(4*n, neutral); // it is not necessary for the leaves.. should decrease this array size
    }

    // This must change accodingly to the problem
    T combine( const T& a, const T& b) { return min(a, b); }
    
    inline void buildTree( vector<T>& src, int idx, int l, int r) {
        if(l == r) tree[idx] = src[l];
        else {
            int mid = (l + r)/2;
            buildTree( src, 2 * idx, l, mid);
            buildTree( src, 2 * idx + 1, mid + 1, r);
            tree[idx] = combine( tree[2*idx], tree[2*idx + 1] ); 
        }
    }
    
    void push(int idx) {
        tree[2 * idx] += lazy[idx];
        tree[2*idx+1] += lazy[idx];
        lazy[2 * idx] += lazy[idx];
        lazy[2*idx+1] += lazy[idx];
        lazy[idx] = 0;
    }
    void update(int idx, int tl, int tr, int l, int r, T delta) {
        if(l > r) return;
        if(tl == l && tr == r) {
            tree[idx] += delta;
            lazy[idx] += delta;
        }
        else {
            push(idx);
            int tm = (tl + tr) / 2;
            update( idx * 2, tl, tm, l, min(r, tm), delta);
            update( idx * 2 + 1, tm + 1, tr, max(l, tm + 1), r, delta);
            tree[idx] = combine(tree[idx * 2], tree[idx * 2 + 1] );
        }
    }

    T query(int idx, int tl, int tr, int l, int r) {
        if(l > r) return id;
        if(l <= tl && tr <= r) return tree[idx];
        push(idx);
        int tm = (tl + tr) / 2;
        return combine( query( idx * 2, tl, tm, l, min(r, tm) ),
                        query( idx*2 + 1, tm + 1, tr, max(l, tm + 1), r) );
    }
};
