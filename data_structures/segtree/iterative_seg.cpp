template <typename T> struct seg
{
	int N;
	vector<T> Tree;
	T id;

	// Change it!
	T combine(const T& a, const T& b) { return min(a, b); }

	seg(int n, T dummy) : N(n), id(dummy) { Tree.assign(2 * N, id); }

	// Remember to call build if leaves have initial values != identity
	void build()
	{
		for (int idx = N - 1; idx > 0; --idx)
			Tree[idx] = combine(Tree[(idx << 1)], Tree[(idx << 1) | 1]);
	}

	void update(int p, T val)
	{
		Tree[p += N] = val;
		while (p > 1)
		{
			Tree[p >> 1] = combine(Tree[p], Tree[p ^ 1]);
			p >>= 1;
		}
	}

	// Query of [l, r)
	T query(int l, int r)
	{
		T res = id;
		for (l += N, r += N; l < r; l >>= 1, r >>= 1)
		{
			if (l & 1) res = combine(res, Tree[l++]);
			if (r & 1) res = combine(res, Tree[--r]);
		}
		return res;
	}
};
