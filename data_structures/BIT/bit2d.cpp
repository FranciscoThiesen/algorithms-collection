template <typename T>
struct BIT2D {
    vector< vector<T> > table;
    int n, m;
    T id;

    BIT2D(int _n, int _m, T _id) : n(_n + 1), m(_m + 1), id(_id)
    {
        table.assign(n, vector<T>(m));
    }
    
    // 0-indexed!
    inline void modify(int i, int j, T delta)
    {
        ++i, ++j;
        int x = i;
        while(x < n)
        {
            int y = j;
            while(y < m)
            {
                table[x][y] += delta;
                y |= (y + 1);
            }
            x |= (x + 1);
        }
    }

    inline T get(int i, int j)
    {
        T v = id;
        int x = i + 1, y = j + 1;
        
        while(x > 0)
        {
            while(y > 0)
            {
                v += table[x][y];
                y = (y & (y + 1) ) - 1;
            }
            x = (x & (x + 1) ) - 1;
        }
        return v;
    }
};
