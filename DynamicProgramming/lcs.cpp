string lcs(const string& s, const string& t)
{
    int n = sz(s), m = sz(t);
    vvi dp(n + 1, vi(m + 1, 0));
    for(int j = 1; j <= m; ++j)
    {
        for(int i = 1; i <= n; ++i)
        {
            dp[i][j] = max( dp[i - 1][j], dp[i][j - 1] );
            if(s[i - 1] == t[j - 1]) dp[i][j] = max( dp[i][j], dp[i - 1][j - 1] + 1);
        }
    }

    // uncomment for recovering answer 
    string ans;
    int cur = dp[n][m];
    int curN = n, curM = m;
    while(cur > 0)
    {
        if(cur > dp[curN - 1][curM] && cur > dp[curN][curM - 1])
        {
            ans += t[curM-1];
            --cur;
            curN--; curM--; 
        }
        else
        {
            if(dp[curN - 1][curM] >= dp[curN][curM - 1]) curN--;
            else curM--;
        }
    }
    //reverse(all(ans));
    return ans;
}

// usage!
int main()
{
    string a = "AGGTAB", b = "GXTXAYB";
    cout << lcs(a, b) << endl;
    return 0;
}
