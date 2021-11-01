<<<<<<< HEAD
#include<iostream>
#include<algorithm>
#include <queue>
using namespace std;


struct node {
    node* left;
    node* right;
    int value;

};


node* getNode()
{
    node* newNode = (node*)malloc(sizeof(node));
    
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->value = NULL;
    return newNode;
}

node* insertBST(node* T, int newKey)
{
    node* q = NULL;
    node* p = T;

    while (p != NULL)
    {
        if (p->value == newKey)return T;
        q = p;
        if (newKey < p->value)
            p = p->left;
        else p = p->right;

    }
    node* newNode = getNode();
    newNode->value = newKey;
    newNode->right = NULL;
    newNode->left = NULL;

    if (T == NULL)
        T = newNode;
    else if (newKey < q->value)
        q->left = newNode;
    else
        q->right = newNode;
    return T;

}



int height(node* T) { 
    if (!T)
        return 0;
    else {
        int left_h = height(T->left);
        int right_h = height(T->right); 
        return 1 + (left_h > right_h ? left_h : right_h);
    }
}


node* maxNode(node* T)
{
    if (T->right == NULL)
        return T;
    else
    {
        return maxNode(T->right);
    }
}
node* minNode(node* T)
{
    if (T->left == NULL)
        return T;
    else
    {
        return minNode(T->left);
    }
}

int noNodes(node* T)
{
    int cnt = 0;
    if (T != NULL)
        cnt = 1 + noNodes(T->left) + noNodes(T->right);
    return cnt;
}

node* searchParentBST(node*T, int deleteKey,bool s)
{
    node* q = NULL;
    node* p = T;
    while (p != NULL)
    {
        if (deleteKey = p->value)
        {
            if (s)
                return q;
            else
                return p;
        }
        q = p;
        if (deleteKey < p->value)
            p = p->left;
        else
            p = p->right;
    }

}

void inorder(struct node* root)
{
    if (root != NULL) {
        inorder(root->left);
        cout << root->value<<" ";
        inorder(root->right);
    }
}

node* deleteBST(node* T, int newValue)
{
    if (T == NULL)
        return T;

    if (newValue < T->value)
        T->left = deleteBST(T->left, newValue);
    else if (newValue > T->value)
        T->right = deleteBST(T->right, newValue);
    else
    {
        if (T->left == NULL && T->right == NULL)
            return NULL;

        else if (T->left == NULL)
        {
            node* temp = T->right;
            return temp;
        }
        else if (T->right == NULL)
        {
            node* temp = T->left;
            return temp;
        }
        if (height(T->left) < height(T->right))
        {
            node* temp = minNode(T->right);
            T->value = temp->value;
            T->right = deleteBST(T->right, temp->value);
        }
        else if (height(T->left) > height(T->right))
        {
            node* temp = maxNode(T->left);
            T->value = temp->value;
            T->left = deleteBST(T->left, temp->value);
        }
        else if (height(T->left) == height(T->right))
        {
            if (noNodes(T->left) < noNodes(T->right))
            {
                node* temp = minNode(T->right);
                T->value = temp->value;
                T->right = deleteBST(T->right, temp->value);
            }
            else
            {
                node* temp = maxNode(T->left);
                T->value = temp->value;
                T->left = deleteBST(T->left, temp->value);
            }
        }
    }
    return T;
}

int main(void)
{
   node* v = NULL;
   v = insertBST(v, 25);
   inorder(v);
   cout << endl;
   v = insertBST(v, 500);
   inorder(v);
   cout << endl;
   v = insertBST(v, 33);
   inorder(v);
   cout << endl;
   v = insertBST(v, 49);
   inorder(v);
   cout << endl;
   v = insertBST(v, 17);
   inorder(v);
   cout << endl;
   v = insertBST(v, 403);
   inorder(v);
   cout << endl;
   v = insertBST(v, 29);
   inorder(v);
   cout << endl;
   v = insertBST(v, 105);
   inorder(v);
   cout << endl;
   v = insertBST(v, 39);
   inorder(v);
   cout << endl;
   v = insertBST(v, 66);
   inorder(v);
   cout << endl;
   v = insertBST(v, 305);
   inorder(v);
   cout << endl;
   v = insertBST(v, 44);
   inorder(v);
   cout << endl;
   v = insertBST(v, 19);
   inorder(v);
   cout << endl;
   v = insertBST(v, 441);
   inorder(v);
   cout << endl;
   v = insertBST(v, 390);
   inorder(v);
   cout << endl;
   v = insertBST(v, 12);
   inorder(v);
   cout << endl;
   v = insertBST(v, 81);
   inorder(v);
   cout << endl;
   v = insertBST(v, 50);
   inorder(v);
   cout << endl;
   v = insertBST(v, 100);
   inorder(v);
   cout << endl;
   v = insertBST(v, 999);
   inorder(v);
   cout << endl;
   


   v =deleteBST(v, 25);
   inorder(v);
   cout << endl;
   v =deleteBST(v, 500);
   inorder(v);
   cout << endl;
   v =deleteBST(v, 33);
   inorder(v);
   cout << endl;
   v =deleteBST(v, 49);
   inorder(v);
   cout << endl;
   v =deleteBST(v, 17);
   inorder(v);
   cout << endl;
   v =deleteBST(v, 403);
   inorder(v);
   cout << endl;
   v =deleteBST(v, 29);
   inorder(v);
   cout << endl;
   v =deleteBST(v, 105);
   inorder(v);
   cout << endl;
   v =deleteBST(v, 39);
   inorder(v);
   cout << endl;
   v =deleteBST(v, 66);
   inorder(v);
   cout << endl;
   v =deleteBST(v, 305);
   inorder(v);
   cout << endl;
   v =deleteBST(v, 44);
   inorder(v);
   cout << endl;
   v =deleteBST(v, 19);
   inorder(v);
   cout << endl;
   v =deleteBST(v, 441);
   inorder(v);
   cout << endl;
   v =deleteBST(v, 390);
   inorder(v);
   cout << endl;
   v =deleteBST(v, 12);
   inorder(v);
   cout << endl;
   v =deleteBST(v, 81);
   inorder(v);
   cout << endl;
   v =deleteBST(v, 50);
   inorder(v);
   cout << endl;
   v =deleteBST(v, 100);
   inorder(v);
   cout << endl;
   v =deleteBST(v, 999);
   inorder(v);
   cout << endl;


   //Àç»ðÀÔ
   v = NULL;
   v = insertBST(v, 25);
   inorder(v);
   cout << endl;
   v = insertBST(v, 500);
   inorder(v);
   cout << endl;
   v = insertBST(v, 33);
   inorder(v);
   cout << endl;
   v = insertBST(v, 49);
   inorder(v);
   cout << endl;
   v = insertBST(v, 17);
   inorder(v);
   cout << endl;
   v = insertBST(v, 403);
   inorder(v);
   cout << endl;
   v = insertBST(v, 29);
   inorder(v);
   cout << endl;
   v = insertBST(v, 105);
   inorder(v);
   cout << endl;
   v = insertBST(v, 39);
   inorder(v);
   cout << endl;
   v = insertBST(v, 66);
   inorder(v);
   cout << endl;
   v = insertBST(v, 305);
   inorder(v);
   cout << endl;
   v = insertBST(v, 44);
   inorder(v);
   cout << endl;
   v = insertBST(v, 19);
   inorder(v);
   cout << endl;
   v = insertBST(v, 441);
   inorder(v);
   cout << endl;
   v = insertBST(v, 390);
   inorder(v);
   cout << endl;
   v = insertBST(v, 12);
   inorder(v);
   cout << endl;
   v = insertBST(v, 81);
   inorder(v);
   cout << endl;
   v = insertBST(v, 50);
   inorder(v);
   cout << endl;
   v = insertBST(v, 100);
   inorder(v);
   cout << endl;
   v = insertBST(v, 999);
   inorder(v);
   cout << endl;



   v = deleteBST(v, 999);
   inorder(v);
   cout << endl;
   v = deleteBST(v, 100);
   inorder(v);
   cout << endl;
   v = deleteBST(v, 50);
   inorder(v);
   cout << endl;
   v = deleteBST(v, 81);
   inorder(v);
   cout << endl;
   v = deleteBST(v, 12);
   inorder(v);
   cout << endl;
   v = deleteBST(v, 390);
   inorder(v);
   cout << endl;
   v = deleteBST(v, 441);
   inorder(v);
   cout << endl;
   v = deleteBST(v,19);
   inorder(v);
   cout << endl;
   v = deleteBST(v,44);
   inorder(v);
   cout << endl;
   v = deleteBST(v,305);
   inorder(v);
   cout << endl;
   v = deleteBST(v,66);
   inorder(v);
   cout << endl;
   v = deleteBST(v,39);
   inorder(v);
   cout << endl;
   v = deleteBST(v,105);
   inorder(v);
   cout << endl;
   v = deleteBST(v, 29);
   inorder(v);
   cout << endl;
   v = deleteBST(v,403);
   inorder(v);
   cout << endl;
   v = deleteBST(v,17);
   inorder(v);
   cout << endl;
   v = deleteBST(v, 49);
   inorder(v);
   cout << endl;
   v = deleteBST(v,33);
   inorder(v);
   cout << endl;
   v = deleteBST(v, 500);
   inorder(v);
   cout << endl;
   v = deleteBST(v,25);
   inorder(v);
   cout << endl;

   
}


>>>>>>> 84487a664df0947bf5dd2dc1c311c148ab52acea
