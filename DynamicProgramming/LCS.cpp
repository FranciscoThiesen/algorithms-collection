#include <cstdio>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;
int arr[101][101] = {0};

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    int vecn[101];
    int vecm[101];
    for(int i = 0; i < n; ++i)
        scanf("%d", &vecn[i]);
    for(int j = 0; j < m;++j)
        scanf("%d", & vecm[j]);
    vector<int> ans;
    for(int y = 1; y <=m; ++y)
    {
        for(int x = 1; x <= n; ++x)
        {
            if(vecn[x-1] == vecm[y-1])
            {
                arr[x][y] = arr[x-1][y-1] + 1;
            }
            else
                arr[x][y] = max(arr[x-1][y], arr[x][y-1]);
        }
    }
    int cur = arr[n][m];
    int curN = n;
    int curM = m;
    while(cur > 0)
    {
        if(cur > arr[curN-1][curM] && cur > arr[curN][curM-1])
        {
            ans.push_back(vecm[curM-1]);
            cur--;
            if(arr[curN][curM-1] == cur)
                curM--;
            else
                curN--;
        }
        else if(cur == arr[curN][curM-1] && cur >= arr[curN-1][curM])
        {
            curM--;
        }
        else
        {
            curN--;
        }
    }
    reverse(ans.begin(),ans.end());
    for(int q = 0; q < (int)ans.size(); q++)
    {
        cout << ans[q] << " ";
    }
    cout << endl;
    return 0;
}
