#include <iostream>
#include <cstring>
#include <algorithm>


using namespace std;

int main() {
    int t;
    cin >> t;

    for (int c = 0; c < t; c++)
    {
        char input1[101];
        char input2[101];
        int Dp[101][101];
        cin >> input1;
        cin >> input2;

        for (int i = 0; i <= strlen(input1); i++)
        {
            Dp[i][0] = 0;
        }
        for (int i = 0; i <= strlen(input2); i++)
        {
            Dp[0][i] = 0;
        }
        for (int i = 1; i <= strlen(input1); i++)
        {
            for (int j = 1; j <= strlen(input2); j++)
            {
                if (input1[i-1] == input2[j-1])
                    Dp[i][j] = Dp[i - 1][j - 1] + 1;
                else
                {
                    Dp[i][j] = max(Dp[i][j - 1], Dp[i - 1][j]);
                }
            }
        }
        cout << Dp[strlen(input1)][strlen(input2)] << endl;
        
    }
    return 0;
}
