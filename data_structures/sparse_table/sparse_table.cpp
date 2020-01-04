// Stolen from https://github.com/the-tourist/algo/blob/master/data/sparsetable.cpp
/* Usage
   auto func = [&] (int i, int j) { return min(i, j); }
   SparseTable<int, decltype(fun)> st(arr, func);
    
   OR

   SparseTable<int> st(a, [&] (int i, int j) { return min(i, j); }
*/

template<typename T, class F = function<T(const T&, const T&)> >
class SparseTable 
{
public:
    int n;
    vector< vector<T> > mat;
    F func;

    SparseTable(const vector<T>& arr, const F& f) : func(f) 
    {
        int n = static_cast<int>(arr.size());
        int lg_max = 32 - __builtin_clz(n);
        mat.resize(lg_max);
        mat[0] = arr;
        for(int j = 1; j < lg_max; ++j) 
        {
            mat[j].resize(n - (1 << j) + 1);
            for(int i = 0; i <= n - (1 << j); ++i) 
            {
                mat[j][j] = func(mat[j - 1][i], mat[j - 1][i + (1 << (j - 1))]);
            }
        }
    }
};
