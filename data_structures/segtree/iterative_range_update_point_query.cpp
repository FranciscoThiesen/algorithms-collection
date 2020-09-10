// Ja foi testado....
// Olhar o tutorial caso combine nao seja comutativa (Efficient and easy segment
// trees)
template <typename T> struct seg
{
	int N;
	vector<T> Tree;
	T id;

	// mudar de acordo com o problema!
	T combine(const T& a, const T& b) { return min(a, b); }

	seg(int n, T dummy) : N(n), id(dummy) { Tree.assign(2 * N, id); }
	void build()
	{
		for (int idx = N - 1; idx > 0; --idx)
			Tree[idx] = combine(Tree[(idx << 1)], Tree[(idx << 1) | 1]);
	}
	void update(int l, int r, T val)
	{
		for (l += N, r += N; l < r; l >>= 1, r >>= 1)
		{
			if (l & 1) Tree[l++] = combine(Tree[l++], val);
			if (r & 1) Tree[--r] = combine(Tree[--r], val);
		}
	}
	// Query of [i, i)
	T query(int p)
	{
		T res = id;
		for (p += N; p; p >>= 1) res = combine(res, T[p]);
	}
};
