template <typename T> struct seg_tree
{
	int S;

	T identity;
	vector<T> value;

	seg_tree<T>(int _S, T _identity = T())
	{
		S = _S, identity = _identity;
		value.resize(2 * S + 1, identity);
	}

	void set_leaves(vector<T>& leaves)
	{
		copy(leaves.begin(), leaves.end(), value.begin() + S);

		for (int i = S - 1; i > 0; i--)
			value[i] = value[2 * i] * value[2 * i + 1];
	}

	void upd(int i, T v)
	{
		i += S;
		value[i] = v;
		while (i > 1)
		{
			i /= 2;
			value[i] = value[2 * i] * value[2 * i + 1];
		}
	}

	// query is about closed ranges [i, j]
	T query(int i, int j)
	{
		T res_left = identity, res_right = identity;
		for (i += S, j += S; i <= j; i /= 2, j /= 2)
		{
			if ((i & 1) == 1) res_left = res_left * value[i++];
			if ((j & 1) == 0) res_right = value[j--] * res_right;
		}
		return res_left * res_right;
	}
};
