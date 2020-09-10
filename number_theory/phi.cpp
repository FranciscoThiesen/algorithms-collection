////////////////////////////////////////////////////////////////////////////////
// Find phi(i) from all i <= MAXN in O(n log n)
vector<int> phi;

void calc_phi(int n)
{
	phi.resize(n + 1);
	iota(all(phi), 0);
	for (int i = 1; i <= n; ++i)
	{
		// pre-calculating all the primes leads to a speedup
		if (is_prime(i) == true)
		{
			for (int j = i; j <= n; j += i) phi[j] -= (phi[j] / i);
		}
	}
}
////////////////////////////////////////////////////////////////////////////////
// Find phi(x) in O(sqrt(n))
int phi(int n)
{
	int result = n;
	for (int i = 2; i * i <= n; ++i)
	{
		if (n % i == 0)
		{
			while (n % i == 0) n /= i;
			result -= result / i;
		}
	}
	if (n > 1) result -= result / n;
	return result;
}
