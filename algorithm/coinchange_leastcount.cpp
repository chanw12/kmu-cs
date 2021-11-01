#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;

int main() {
	
	int t, n, k;
	scanf_s("%d", &t);

	for (int q = 0; q < t; q++)
	{
		int coin[11];
		int Dp[10001];
		scanf_s("%d %d", &n, &k); // n은 거스름돈의 양  k는 동전의 종류
		for (int i = 0; i < k; i++)	scanf_s("%d",&coin[i]);
		
		for (int i = 1; i <= n; i++)
		{
			Dp[i] = 10000000;
		}
		Dp[0] = 0;
		for (int i = 0; i < k; i++)
		{
			for (int j = coin[i]; j <= n; j++)
			{
				Dp[j] = min(Dp[j], Dp[j - coin[i]] + 1);
			}
		}

		printf("%d\n", Dp[n]);
		
	}

}
