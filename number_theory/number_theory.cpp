////////////////////////////////////////////////////////////////////////////////
// Compute GCD and LCM
template <typename T> T gcd(T a, T b) { return __gcd(a, b); }

template <typename T> T lcm(T a, T b) { return a * b / (gcd<T>(a, b)); }

////////////////////////////////////////////////////////////////////////////////
// Primality check in O(sqrt(n) / 6)
bool is_prime(int n)
{
	if (n < 0) return is_prime(-n);
	if (n < 5 || n % 2 == 0 || n % 3 == 0) return (n == 2 || n == 3);
	int max_p = sqrt(n) + 2;
	for (int p = 5; p < max_p; p += 6)
		if (n % p == 0 || n % (p + 2) == 0) return false;
	return true;
}

////////////////////////////////////////////////////////////////////////////////
// Prime factorization of n -> O(sqrt(n)/6)
unordered_map<int, int> prime_map;
void squeeze(unordered_map<int, int>& M, int& n, int p)
{
	for (; n % p == 0; n /= p) M[p]++;
}

unordered_map<int, int> factor(int n)
{
	unordered_map<int, int> M;
	if (n < 0) return factor(-n);
	if (n < 2) return M;
	squeeze(M, n, 2);
	squeeze(M, n, 3);
	int max_p = sqrt(n) + 2;
	for (int d = 5; d < max_p; d += 6)
	{
		squeeze(M, n, d);
		squeeze(M, n, d + 2);
	}
	if (n > 1) M[n]++;
	return M;
}

////////////////////////////////////////////////////////////////////////////////
// Get all divisors from prime factors
vi divisors(const unordered_map<int, int>& factors)
{
	vi divs = {1};
	for (const auto& p: factors)
	{
		int SZ = sz(divs);
		for (int i = 0; i < SZ; ++i)
		{
			int cur = divs[i];
			for (int j = 0; j < p.second; ++j)
			{
				cur *= p.first;
				divs.push_back(cur);
			}
		}
	}
	// uncomment to get sorted list
	// sort(all(divisors));
	return divs;
}

////////////////////////////////////////////////////////////////////////////////
// Finds a e b, such that a*x + b*y == gcd(x, y) ( Bezout )
template <typename T> pair<T, T> find_bezout(T x, T y)
{
	if (y == 0) return {1, 0};
	auto go = find_bezout(y, x % y);
	return {go.second, go.first - (x / y) * go.second};
}

////////////////////////////////////////////////////////////////////////////////
// Finds smallest non-negative solution of a*x = b ( mod m )
template <typename T> T mod(T x, T m) { return x % m + (x < 0) ? m : 0; }

template <typename T> T solve_mod(T a, T b, T m)
{
	if (m < 0) return solve_mod<T>(a, b, -m);
	if (a < 0 || a >= m || b < 0 || b >= m)
		return solve_mod(mod(a, m), mod(b, m), m);
	auto bezout = find_bezout<T>(a, m);
	T d = bezout.first * a + bezout.second * m;
	if (b % d) return -1;
	else
		return mod<T>(bezout.first * (b / d), m);
}

////////////////////////////////////////////////////////////////////////////////
// Pascal Triangle
struct pascal_triangle
{
	int SIZE; // be careful
	vector<vector<int>> V;
	pascal_triangle(int _SIZE) : SIZE(_SIZE)
	{
		V.resize(SIZE);
		V.assign(SIZE, vector<int>(SIZE, 0));
		for (int i = 0; i < SIZE; ++i)
		{
			V[i][0] = V[i][i] = 1;
			for (int j = 1; j < i; ++j) V[i][j] = V[i - 1][j - 1] + V[i - 1][j];
		}
	}
};

////////////////////////////////////////////////////////////////////////////////
// Find all prime numbers up to MAXN
constexpr int MAXN = 100010;
vi min_f(MAXN, 0);
vi primes;

void linear_sieve()
{
	for (int i = 2; i < MAXN; ++i)
	{
		if (min_f[i] == 0)
		{
			min_f[i] = i;
			primes.push_back(i);
		}
		for (int j = 0; j < (int) primes.size() && primes[j] <= min_f[i] &&
						i * primes[j] < MAXN;
			 ++j)
			min_f[i * primes[j]] = primes[j];
	}
}
