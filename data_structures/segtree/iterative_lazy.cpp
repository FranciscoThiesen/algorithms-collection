// Ja foi testado....
template <typename T> struct seg
{
	int N;
	vector<T> Tree;
	vector<T> lazy;
	T id;
	int h;

	// mudar de acordo com o problema!
	T combine(const T& a, const T& b) { return min(a, b); }

	seg(int n, T dummy) : N(n), id(dummy)
	{
		Tree.assign(2 * N, id);
		lazy.assign(N, id);
		h = sizeof(int) * 8 - __builtin_clz(N);
	}

	// aplica uma mudanca
	void apply(int p, T value)
	{
		Tree[p] += value;
		if (p < N) lazy[p] += value;
	}

	// designed for update all the parents of a given node
	void build()
	{
		for (int idx = N - 1; idx > 0; --idx)
			Tree[idx] =
				combine(Tree[(idx << 1)], Tree[(idx << 1) | 1]) + lazy[idx];
	}

	// propaga dos pais para os filhos as mudancas
	void push(int p)
	{
		for (int s = h; s > 0; --s)
		{
			int i = p >> s;
			if (lazy[i] != 0)
			{
				apply(i << 1, lazy[i]);
				apply(i << 1 | 1, lazy[i]);
				lazy[i] = 0;
			}
		}
	}

	// faz o update do segmento [l, r)
	void update(int l, int r, T value)
	{
		l += N, r += N;
		int l0 = l, r0 = r;
		for (; l < r; l >>= 1, r >>= 1)
		{
			if (l & 1) apply(l++, value);
			if (r & 1) apply(--r, value);
		}
	}
	// Query of [i, j)
	T query(int l, int r)
	{
		l += N, r += N;
		push(l);
		push(r);
		T res = id;
		for (; l < r; l >>= 1, r >>= 1)
		{
			if (l & 1) res = combine(res, Tree[l++]);
			if (r & 1) res = combine(res, Tree[--r]);
		}
		return res;
	}
};

int main() { return 0; }
