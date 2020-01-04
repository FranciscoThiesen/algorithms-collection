template <typename T>
int lis(const vector<T>& arr)
{
    vector<T> st; 
    for(const T& elem : arr)
    {
        auto it = lower_bound(all(st), elem);
        if(it == st.end()) st.push_back(elem);
        else *it = elem;
    }
    return sz(pilha);
}
