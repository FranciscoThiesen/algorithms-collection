// Heavily based on the Algorithms Live! video about String Hashing
ll powmod(ll a, ll b, ll mod)
{
	a %= mod;
	assert(b >= 0);
	ll res = 1;
	for (; b; b >>= 1)
	{
		if (b & 1) res = (res * a) % mod;
		a = (a * a) % mod;
	}
	return res;
}

template <ll MOD> ll norm(ll val)
{
	val %= MOD;
	if (val < 0) val += MOD;
	return val;
}

constexpr ll p0 = 1000'000'033;
constexpr ll p1 = 1000'000'007;
constexpr int ms = 100100; // used for calcuating table of powers
constexpr int base = 31;   // should be a little bit larger than the alphabet..

long long ppow[2][ms];

// Remember to call init() function!
struct Hash
{
	// check if length matters to the specific problem!

	int len = 0; // does not always matter, depends on the problem
	long long H[2] = {0LL, 0LL};
	bool operator!=(const Hash& rhs) const
	{
		return (H[0] != rhs.H[0] || H[1] != rhs.H[1]);
	}

	// check if len should be using in this operator.. depends on the problem
	bool operator==(const Hash& rhs) const
	{
		return ((H[0] == rhs.H[0] && H[1] == rhs.H[1]) && len == rhs.len);
	}

	Hash(ll h0 = 0, ll h1 = 0)
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
		ll invMod = powmod(ppow[0][len - 1], p0 - 2, p0);
		H[0] = (H[0] * invMod) % p0;
		H[1] = norm<p1>(H[1] - (c - 'a' + 1));
		invMod = powmod(ppow[1][len - 1], p1 - 2, p1);
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
