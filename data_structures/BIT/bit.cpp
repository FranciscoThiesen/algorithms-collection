template <typename T>
struct BIT {
    vector<T> table;
    int sz;
    T id;

    BIT(int _sz, T _id) : sz(_sz + 1), id(_id) { table.resize(sz); }

    void modify(int idx, T delta)
    {
        ++idx;
        while(idx < sz)
        {
            table[idx] += delta;
            idx |= (idx + 1);
        }
    }

    T get(int idx)
    {
        ++idx;
        T resp = id;
        while(idx > 0)
        {
            resp += table[idx];
            idx = (idx & (idx + 1)) - 1;
        }
    }

    T get(int l, int r) { return get(r) - get(l - 1); }
};
