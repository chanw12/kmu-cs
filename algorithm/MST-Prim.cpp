#include<iostream>
#include<algorithm>
#include<vector>
#include<cmath>
#include<queue>
#include<string>
#include<map>
#include<queue>

using namespace std;

const int MAX = 1000000000;

struct pr {
	int  a,b, weight;
};
struct cmp {
	bool operator()(pr n1, pr n2)
	{
		if (n1.weight > n2.weight)
			return true;
		else
			return false;
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	int test_case;
	cin >> test_case;
	for (int t = 0; t < test_case; t++)
	{
		int sum = 0;
		int n,k,m;
		cin >> n;
		vector<bool> visited(n + 1);
		vector<vector<pr>> vr(n + 1);

		priority_queue<pr,vector<pr>,cmp> mini;
		for (int j = 1; j <= n; j++)
		{
			cin >> k >> m;
			for (int s = 1; s <= m; s++)
			{
				pr temp;
				temp.a = k;
				cin >> temp.b >> temp.weight;
				vr[k].push_back(temp);
			}
		}
		
		visited[1] = true;
		for (int i = 0; i < vr[1].size(); i++)
		{
			mini.push(vr[1][i]);
		}
		


		for (int i = 0; i < n-1; i++)
		{
			while (visited[mini.top().b])
			{
				mini.pop();
			}
			int current = mini.top().b;
			sum += mini.top().weight;
			mini.pop();
			visited[current] = true;
			for (int j = 0; j < vr[current].size(); j++)
			{
				if (!visited[vr[current][j].b])
				{
					mini.push(vr[current][j]);
				}
			}

		}
		cout << sum << endl;

	}


	return 0;
}
