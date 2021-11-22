#include<iostream>
#include<algorithm>
#include<vector>
#include<cmath>
#include<queue>
#include<string>
#include<map>

using namespace std;

int getParent(int Parent[],int x)
{
	if (Parent[x] == x) return x;
	else return getParent(Parent, Parent[x]);
}

void unionParent(int Parent[], int a, int b)
{
	a = getParent(Parent, a);
	b = getParent(Parent, b);
	if (a < b) Parent[b] = a;
	else Parent[a] = b;
	
}
bool findParent(int Parent[], int a, int b)
{
	a = getParent(Parent, a);
	b = getParent(Parent, b);
	if (a == b)return true;
	else return false;
}
class Edge {
public:
	int distance;
	int node[2];

	Edge(int a, int b, int distance)
	{
		this->node[0] = a;
		this->node[1] = b;
		this->distance = distance;
	}
	bool operator <(Edge& edge)
	{
		return this->distance < edge.distance;
	}
};

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int t;
	cin >> t;
	for (int z = 0; z < t; z++)
	{
		
		int n, k,m;
		cin >> n;
		vector<Edge> e;
		for (int i = 1; i <=n; i++)
		{
			cin >> k >> m;
			for (int j = 1; j <= m; j++)
			{
				int temp1, temp2;
				cin >> temp1>> temp2;
				e.push_back(Edge(k, temp1, temp2));
			}	
		}
		sort(e.begin(), e.end());

		int Parent[1001];
		for (int i = 1; i <= n; i++) Parent[i] = i;

		int sum=0;
		for (int i = 0; i < e.size(); i++)
		{
			if (findParent(Parent, e[i].node[0], e[i].node[1])) continue;
			else
			{
				sum += e[i].distance;
				unionParent(Parent, e[i].node[0], e[i].node[1]);
			}
		}
		cout << sum << endl;
		
		
	}

	return 0;
}

