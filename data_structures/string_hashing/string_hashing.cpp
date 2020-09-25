// Heavily based on the Algorithms Live! video about String Hashing
long long powmod(long long a, long long b, long long mod)
{
	a %= mod;
	assert(b >= 0);
	long long res = 1;
	for (; b; b >>= 1)
	{
		if (b & 1) res = (res * a) % mod;
		a = (a * a) % mod;
	}
	return res;
}

template <long long MOD> long long norm(long long val)
{
	val %= MOD;
	if (val < 0) val += MOD;
	return val;
}

constexpr long long p0 = 1000'000'033;
constexpr long long p1 = 1000'000'007;
constexpr int ms = 100100; // used for calcuating table of powers
constexpr int base = 31;   // should be a little bit larger than the alphabet..

long long ppow[2][ms];

// Remember to calong long init() function!
struct Hash
{
	// check if length matters to the specific problem!

	int len = 0; // does not always matter, depends on the problem
	long long H[2] = {0, 0};
	bool operator!=(const Hash& rhs) const
	{
		return (H[0] != rhs.H[0] || H[1] != rhs.H[1]);
	}

	// check if len should be using in this operator.. depends on the problem
	bool operator==(const Hash& rhs) const
	{
		return ((H[0] == rhs.H[0] && H[1] == rhs.H[1]) && len == rhs.len);
	}

	Hash(long long h0 = 0, long long h1 = 0)
	{
		H[0] = norm<p0>(h0);
		H[1] = norm<p1>(h1);
	}

	inline void addBack(char c)
	{
		H[0] = (H[0] + (c - 'a' + 1) * ppow[0][len]) % p0;
		H[1] = (H[1] + (c - 'a' + 1) * ppow[1][len]) % p1;
		++len;
	}

	inline void addFront(char c)
	{
		H[0] = (H[0] * base + (c - 'a' + 1)) % p0;
		H[1] = (H[1] * base + (c - 'a' + 1)) % p1;
		++len;
	}

	inline void removeBack(char c)
	{
		// assert( len > 0);
		H[0] = norm<p0>(H[0] - (c - 'a' + 1) * ppow[0][len]);
		H[1] = norm<p1>(H[1] - (c - 'a' + 1) * ppow[1][len]);
		--len;
	}

	inline void removeFront(char c)
	{
		// assert(len > 0);
		H[0] = norm<p0>(H[0] - (c - 'a' + 1));
		long long invMod = powmod(base, p0 - 2, p0);
		H[0] = (H[0] * invMod) % p0;
		H[1] = norm<p1>(H[1] - (c - 'a' + 1));
		invMod = powmod(base, p1 - 2, p1);
		H[1] = (H[1] * invMod) % p1;
		--len;
	}

	void addString(const string& s)
	{
		for (const char& c: s) addBack(c);
	}
};

void init()
{
	ppow[0][0] = ppow[1][0] = 1;
	rep(i, 1, ms)
	{
		ppow[0][i] = (ppow[0][i - 1] * base) % p0;
		ppow[1][i] = (ppow[1][i - 1] * base) % p1;
	}
}

int main()
{

	init();
	return 0;
}
