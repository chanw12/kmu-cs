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

struct BNode* root; // root ��� �⺻ ����(�����ͷ�)
BNode* getBTNode(int m,int val)
{
	struct BNode* newNode; // ���ο� node ����ü ����
	newNode = (struct BNode*)malloc(sizeof(struct BNode)); // node�� �����Ҵ�
	newNode->leaf = false; // ó���� �������δ� �ʱⰪ false��
	newNode->key[0] = val; // �� node�� 1��° key ���� �޾ƿ� ������ �ֱ�
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
