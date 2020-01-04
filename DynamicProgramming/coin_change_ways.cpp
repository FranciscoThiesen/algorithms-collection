// n is total_value, m is the total number of available coins
// a coin can be used multiple times!

long long int memo[50][250];
int n, m, coins[51];

long long int ways(int type, int value)
{
	if(value == 0)
		return 1;
	if(value < 0 || type == m)
		return 0;
	if(memo[type][value] != -1)
		return memo[type][value];
	else
	{
		return memo[type][value] = ways(type+1,value) + ways(type, value - coins[type]);
	}

}
