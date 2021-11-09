#include <iostream>
#include <cstring>
#include <climits>
#include <algorithm>

#define Max(a,b) ((a)>(b)?(a):(b))
using namespace std;

int main() {
    int t;
    cin >> t;
    for (int c = 0; c < t; c++)
    {
        int Dp[101][101] = { 0, };
        int n;
        int num[101];
        cin >> n;
        for (int i = 0; i < n+1; i++)cin >> num[i];
        
        for (int i = 0; i < n + 1; i++)
        {
            for (int j = 1; j+i < n + 1; j++)
            {
                Dp[j][j + i] = INT_MAX;
                if (i == 0)
                    Dp[j][j + i] = 0;

                for (int k = j; k <= i + j - 1;k++)
                {
                    int temp = Dp[j][k] + Dp[k + 1][j + i] + num[j - 1] * num[k]* num[i + j];

                    if (temp < Dp[j][j + i])
                        Dp[j][j + i] = temp;
                }
            }
        }

        cout << Dp[1][n] << endl;
    }
  
    return 0;
}


