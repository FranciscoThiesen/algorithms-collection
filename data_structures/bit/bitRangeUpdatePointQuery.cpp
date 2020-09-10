/*input

*/
#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define all(v) (v).begin(), (v).end()
#define pb push_back
#define mp make_pair

typedef vector<int> vi;

int lsb(int i) { return i & -i; }

struct BIT
{
	int size;
	vi table;
	BIT(int sz)
	{
		table.resize(sz + 2, 0);
		size = sz + 1;
	}
	// update position pos by delta
	// pos is zero indexed
	void update(int pos, int delta)
	{
		++pos;
		while (pos <= size)
		{
			table[pos] += delta;
			pos += lsb(pos);
		}
	}

	// update the interval [l, r] by delta
	// l and r should be 0-indexed
	void rangeUpdate(int l, int r, int delta)
	{
		update(l, delta);
		update(r + 1, -delta);
	}
	// the i parameter is 0 indexed
	int pointQuery(int i)
	{
		++i;
		int sum = 0;
		while (i > 0)
		{
			sum += table[i];
			i -= lsb(i);
		}
		return sum;
	}
};

int main()
{
	BIT b(5);
	cout << "got here" << endl;
	b.rangeUpdate(0, 2, 5);
	b.rangeUpdate(1, 5, 10);
	cout << b.pointQuery(3);
	return 0;
}
