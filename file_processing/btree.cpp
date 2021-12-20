#include <iostream>
#include <stack>
#include <vector>
#include <fstream>

using namespace std;

class Node
{
    int m;
    int n;
    vector<int> key;
    vector<Node *> child;
    vector<int *> C;

public:
    Node *Bestsibling(int idx, bool &LR);
    void insertKey(int newValue);
    void deleteKey(int idx);
    void insertChild(Node *node);
    void deleteChilde(int idx);
    vector<int *> getC() { return C; }
    int *getC(int idx) { return C[idx]; }
    int getN() { return n; }
    int getM() { return m; }
    void setN(int N) { n = N; }
    void setM(int M) { m = M; }
    vector<Node *> getChild() { return child; }
    Node *getChild(int idx) { return child[idx]; }
    int getSizeF() { return child.size(); }
    vector<int> getKey() { return key; }
    int getKey(int idx) { return key[idx]; }
    void setKey(int idx, int value) { key[idx] = value; }
    void NodeDuplicate(Node *dupl);
    void NodeDuplicateFirstHalf(Node *dupl);
    void NodeDuplicateSecondHalf(Node *dupl);
    Node()
    {
        m = 0;
        n = 0;
    }
    Node(int M)
    {
        n = 0;
        m = M;
        child.resize(m, nullptr);
        key.resize(m - 1, 0);
        C.resize(m - 1, nullptr);
    }
};

class BTree
{
    Node *root;
    int m;

public:
    BTree()
    {
        root = nullptr;
        m = 0;
    }
    void setRoot(Node *node) { root = node; }
    void setM(int M) { m = M; }
    Node *getRoot() { return root; }
};

void Node::NodeDuplicate(Node *dupl)
{
    n = dupl->getN();
    for (int i = 0; i < n; i++)
    {
        key[i] = dupl->getKey(i);
        C[i] = dupl->getC(i);
    }
    for (int i = 0; i <= n; i++)
    {
        child[i] = dupl->getChild(i);
    }
}
void Node::NodeDuplicateFirstHalf(Node *dupl)
{
    key.assign(m - 1, 0);
    C.assign(m - 1, nullptr);
    child.assign(m, nullptr);
    n = dupl->getN() / 2;
    for (int i = 0; i < n; i++)
    {
        key[i] = dupl->getKey(i);
        C[i] = dupl->getC(i);
        child[i] = dupl->getChild(i);
    }
    child[n] = dupl->getChild(n);
}
void Node::NodeDuplicateSecondHalf(Node *dupl)
{
    key.assign(m - 1, 0);
    C.assign(m - 1, nullptr);
    child.assign(m, nullptr);
    n = dupl->getN() - dupl->getN() / 2 - 1;
    for (int i = 0; i < n; i++)
    {
        key[i] = dupl->getKey(dupl->getN() / 2 + i + 1);
        C[i] = dupl->getC(dupl->getN() / 2 + i + 1);
        child[i] = dupl->getChild(dupl->getN() / 2 + i + 1);
    }
    child[n] = dupl->getChild(dupl->getN());
}
void Node::insertChild(Node *node)
{
    if (node == nullptr)
        return;
    for (int i = 0; i < n; i++)
    {
        if (key[i] > node->getKey(0))
        {
            child.insert(child.begin() + i, node);
            child.pop_back();
            return;
        }
    }
    child[n] = node;
}

int BinarySearch(vector<int> key, int n, int newKey)
{
    int left = 0;
    int right = n - 1;
    int mid = (left + right) / 2;

    while (left <= right)
    {
        mid = (left + right) / 2;
        if (key[mid] == newKey)
        {
            return mid;
        }
        else if (key[mid] > newKey)
        {
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }
    return left;
}
void Node::insertKey(int newValue)
{
    for (int i = 0; i < n; i++)
    {
        if (key[i] > newValue)
        {
            key.insert(key.begin() + i, newValue);
            n++;
            key.pop_back();
            return;
        }
    }
    key[n] = newValue;
    n++;
}
void insert(BTree *Tree, int m, int newValue)
{
    Node *root = Tree->getRoot();
    Node *newnode = nullptr;
    stack<Node *> Stack;
    stack<int> iStack;

    int a;
    while (root != nullptr)
    {
        a = BinarySearch(root->getKey(), root->getN(), newValue);

        if (a < root->getN() && newValue == root->getKey(a))
            return;

        Stack.push(root);
        iStack.push(a);

        root = root->getChild(a);
    }
    // insert key and node while popping parent node from stack
    while (!Stack.empty())
    {
        root = Stack.top();
        Stack.pop();
        a = iStack.top();
        iStack.pop();

        if (root->getN() < m - 1)
        {
            root->insertKey(newValue);

            if (newnode != nullptr)
            {
                root->insertChild(newnode);
            }
            return;
        }
        // case of overflow
        Node *temp = new Node(m + 1);
        temp->NodeDuplicate(root);
        temp->insertKey(newValue);
        if (newnode != nullptr)
        {
            temp->insertChild(newnode);
        }

        newnode = new Node(m);
        root->NodeDuplicateFirstHalf(temp);
        newnode->NodeDuplicateSecondHalf(temp);
        newValue = temp->getKey(m / 2);
        delete temp;
    }

    Node *n = new Node(m);

    Tree->setRoot(n);
    Tree->getRoot()->insertKey(newValue);
    Tree->getRoot()->insertChild(root);
    Tree->getRoot()->insertChild(newnode);
}
void Node::deleteKey(int idx)
{
    key.erase(key.begin() + idx);
    key.push_back(0);
    n--;
}
void Node::deleteChilde(int idx)
{
    child.erase(child.begin() + idx);
    child.push_back(nullptr);
}

Node *Node::Bestsibling(int idx, bool &LR)
{
    int leftN = -1;
    int rightN = -1;
    if (idx > 0)
        leftN = child[idx - 1]->getN();
    if (idx < n)
        rightN = child[idx + 1]->getN();
    if (leftN == -1 && rightN == -1)
    {
        return nullptr;
    }
    else if (leftN == -1)
    {
        LR = false;
        return child[idx + 1];
    }
    else if (rightN == -1)
    {
        LR = true;
        return child[idx - 1];
    }
    else if (leftN >= rightN)
    {
        LR = true;
        return child[idx - 1];
    }
    else
    {
        LR = false;
        return child[idx + 1];
    }
}

void deleteBT(BTree *Tree, int m, int oldKey)
{
    Node *root = Tree->getRoot();
    stack<Node *> Stack;
    stack<int> iStack;
    int a;
    while (root != nullptr)
    {
        a = BinarySearch(root->getKey(), root->getN(), oldKey);
        if (a < root->getN() && oldKey == root->getKey(a))
            break;
        Stack.push(root);
        iStack.push(a);
        root = root->getChild(a);
    }

    if (root == nullptr)
        return;
    Node *internalNode;

    if (root->getChild(a + 1) != nullptr)
    {
        internalNode = root;
        Stack.push(root);
        iStack.push(a + 1);
        root = root->getChild(a + 1);

        while (root != nullptr)
        {
            Stack.push(root);
            iStack.push(0);
            root = root->getChild(0);
        }
    }
    if (root == nullptr)
    {
        root = Stack.top();
        Stack.pop();
        internalNode->setKey(a, root->getKey(0));
        root->setKey(0, oldKey);
        a = iStack.top();
        iStack.pop();
    }
    root->deleteKey(a);
    Node *y;
    Node *bestSibling;
    while (!Stack.empty())
    {
        if (root->getN() >= (m - 1) / 2)
            return;
        y = Stack.top();
        Stack.pop();
        a = iStack.top();
        iStack.pop();

        bool LR;
        Node *bestSibling = y->Bestsibling(a, LR);
        int b = a - LR;

        if (bestSibling->getN() > (m - 1) / 2)
        {
            root->insertKey(y->getKey(b));
            if (y->getKey(b) < bestSibling->getKey(0))
            {
                y->setKey(b, bestSibling->getKey(0));
                bestSibling->deleteKey(0);
                root->insertChild(bestSibling->getChild(0));
                bestSibling->deleteChilde(0);
            }
            else
            {
                y->setKey(b, bestSibling->getKey(bestSibling->getN() - 1));
                bestSibling->deleteKey(bestSibling->getN() - 1);
                root->insertChild(bestSibling->getChild(bestSibling->getN() + 1));
                bestSibling->deleteChilde(bestSibling->getN() + 1);
            }
            break;
        }
        if (bestSibling->getKey(0) < y->getKey(b))
        {
            bestSibling->insertKey(y->getKey(b));
            vector<int> newK = root->getKey();
            vector<Node *> newChild = root->getChild();
            for (int i = 0; i < root->getN(); i++)
            {
                bestSibling->insertKey(newK[i]);
            }
            for (int i = 0; i <= root->getN(); i++)
            {
                bestSibling->insertChild(newChild[i]);
            }
            y->deleteKey(b);
            y->deleteChilde(b + 1);
        }
        else
        {
            root->insertKey(y->getKey(b));
            vector<int> newK = bestSibling->getKey();
            vector<Node *> newChild = bestSibling->getChild();
            for (int i = 0; i < bestSibling->getN(); i++)
            {
                root->insertKey(newK[i]);
            }
            for (int i = 0; i <= bestSibling->getN(); i++)
            {
                root->insertChild(newChild[i]);
            }
            y->deleteKey(b);
            y->deleteChilde(b + 1);
        }

        root = y;
    }
    if (root->getN() == 0)
    {
        Tree->setRoot(root->getChild(0));
        delete root;
    }
}
void inorder(Node *N)
{
    if (N == nullptr)
        return;
    for (int i = 0; i < N->getN(); i++)
    {
        if (N->getChild(i) != nullptr)
        {
            inorder(N->getChild(i));
        }
        cout << N->getKey(i) << " ";
    }
    if (N->getChild(N->getN()) != nullptr)
    {
        inorder(N->getChild(N->getN()));
    }
}
void inorderBT(BTree *T)
{
    inorder(T->getRoot());
    cout << endl;
    cout << endl;
}

int main()
{
    BTree *T = new BTree();

    ifstream inputInsert;
    ifstream inputDelete;

    for (int m = 3; m <= 4; m++)
    {
        T = new BTree();
        inputInsert.open("insertSequence.txt");
        while (!inputInsert.eof())
        {
            int n;
            inputInsert >> n;
            insert(T, m, n);
            inorderBT(T);
        }
        inputInsert.close();

        inputDelete.open("deleteSequence.txt");
        while (!inputDelete.eof())
        {
            int n;
            inputDelete >> n;
            deleteBT(T, m, n);
            inorderBT(T);
        }
        inputDelete.close();
    }

    return 0;
}