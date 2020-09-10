#include <bits/stdc++.h>

using namespace std;

#define fr(i, a, b) for (int(i) = (a); (i) < (b); ++(i))
#define rp(i, n) fr(i, 0, n)
#define fi first
#define se second
#define all(v) (v).begin(), (v).end()
#define pb push_back
#define mt make_tuple
#define mp make_pair
#define sz(a) (int) (a.size())

typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;

const int maxn = 2002;

int n, m;
vector<int> g[maxn];
int lbl[maxn], low[maxn], idx, cnt_scc;
stack<int> st;
bool inSt[maxn];

void dfs(int u) { lbl[u] = low[u] = idx++; }

int main() { return 0; }
