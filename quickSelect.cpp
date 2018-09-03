#include <bits/stdc++.h>


using namespace std;

// Implementacao do quickselect, assumindo que todos os elementos do vetor sao distintos entre si

int partition(vector<int>& arr, int l, int r) 
{
    int x = arr[r], i = l;
    for(int j = l; j <= r - 1; ++j)
    {
        if(arr[j] <= x)
        {
            swap(arr[i], arr[j]);
            ++i;
        }
    }
    swap(arr[i], arr[r]);
    return i;
}

int kth(vector<int>& arr, int l, int r, int k)
{
    if(k > 0 && k <= r - l + 1)
    {
        int index = partition(arr, l, r);
        if(index - l == k - 1) return arr[index];
        if(index - l > k - 1) return kth(arr, l, index - 1, k);
        return kth(arr, index + 1, r, k - index + l - 1);
    }
    return -1; // se passarem um k invalido
}

int main()
{
    vector<int> arr(100);
    random_shuffle(arr.begin(), arr.end() );
    iota(arr.begin(), arr.end(), 1);
    for(int i = 1; i < 100; ++i) 
    {
        cout << "vou encontrar o k-esimo = " << kth(arr, 0, 99, i) << " = " << i << endl;
    }
    return 0;
}
