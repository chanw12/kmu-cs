#include<iostream>
#include<algorithm>
#include<vector>
#include<cmath>
#include<queue>
#include<string>
#include<map>
#include<queue>

using namespace std;
struct BNode {
	bool leaf;
	int max_children;
	int max_keys;
	int key[4];
	int cnt_key;
	struct BNode* child[5];
	int cnt_child;
};

struct BNode* root; // root 노드 기본 설정(포인터로)
BNode* getBTNode(int m,int val)
{
	struct BNode* newNode; // 새로운 node 구조체 선언
	newNode = (struct BNode*)malloc(sizeof(struct BNode)); // node에 동적할당
	newNode->leaf = false; // 처음에 리프여부는 초기값 false로
	newNode->key[0] = val; // 새 node의 1번째 key 값에 받아온 데이터 넣기
	newNode->cnt_key = 1;
	newNode->cnt_child = 0;
	newNode->max_children = m;
	newNode->max_keys = m - 1;
	return newNode;
}
int Search(struct BNode* node,int val)
{
	if (!node)
	{
		cout << "Empty" << endl;
		return 0;
	}
	struct BNode* nNode = node;
	while (true)
	{
		int pos;
		for (pos = 0; pos < nNode->cnt_key; pos++)
		{
			if (val == nNode->key[pos])
			{
				cout << val << "exist" << endl;
				return 1;
			}
			else if (val < nNode->key[pos])
				break;
		}
		if (nNode->leaf)break;
		nNode = nNode->child[pos];
	}
	cout << "not exist" << endl;
}

BNode* divideNode(int pos, BNode* node, BNode* parent)//splitNode
{
	int median;
	median = node->cnt_key / 2;

}
int main() {
	
	return 0;
}
