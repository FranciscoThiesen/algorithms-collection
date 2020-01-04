// Implementation provided by github.com/danielf !!
struct UF 
{
    vi p, rank;
    UF(int n) 
    {
        p = vi(n);
        rank = vi(n, 0);
        iota(all(p), 0);
    }
    
    int find(int v) 
    {
        if( p[v] != v) p[v] = find(p[v]);
        return p[v];
    }

    bool unio(int a, int b) {
        a = find(a); b = find(b);
        if(a == b) return false;
        if(rank[a] < rank[b]) p[a] = b;
        else p[b] = a;
        if(rank[a] == rank[b]) rank[a]++;
        return true;
    }
};

