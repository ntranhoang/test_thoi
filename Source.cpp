#include<iostream>
#include<queue>
using namespace std;
struct node {
	int data;
	node* pLeft;
	node* pRight;
};
node* getNode(int data)
{
	node* pNew = new node;
	if (pNew)
	{
		pNew->data = data;
		pNew->pLeft = pNew->pRight=NULL;
	}
	return pNew;
}
void insert(node*& pRoot, int x)
{
	if (pRoot == NULL)
		pRoot = getNode(x);
	else if (x < pRoot->data)
		insert(pRoot->pLeft, x);
	else if (x > pRoot->data)
		insert(pRoot->pRight, x);
}

void LNR(node* pRoot)
{
	if (pRoot)
	{
		LNR(pRoot->pLeft);
		cout << pRoot->data << " ";
		LNR(pRoot->pRight);
	}
}
void LRN(node* pRoot)
{
	if (pRoot)
	{
		LRN(pRoot->pLeft);
		LRN(pRoot->pRight);
		cout << pRoot->data << " ";
	}
}
void NLR(node* pRoot)
{
	if (pRoot)
	{
		cout << pRoot->data << " ";
		NLR(pRoot->pLeft);
		NLR(pRoot->pRight);
	}
}
void LevelOrder(node* pRoot)
{
	queue<node*>list;
	list.push(pRoot);
	if (list.empty() == false)
	{
		node* temp = list.front();
		list.pop();
		cout << temp->data << " ";
		if (temp->pLeft)
			list.push(temp->pLeft);
		if (temp->pRight)
			list.push(temp->pRight);
	}
}
void makeDel(node*& pRoot)
{
	node* temp=pRoot;
	if (pRoot == NULL)
		return;
	else if (pRoot->pRight == NULL)
	{
		pRoot = pRoot->pLeft;
		delete temp;
	}
	else if (pRoot->pLeft == NULL)
	{
		pRoot = pRoot->pRight;
		delete temp;
	}
	else {
		temp = pRoot->pRight;
		while (temp->pLeft)
			temp = temp->pLeft;
		swap(temp->data, pRoot->data);
		makeDel(temp);
	}
}
void Remove(node*& pRoot, int x)
{
	if (pRoot == NULL)
		return;
	else if (x < pRoot->data)
		Remove(pRoot->pLeft, x);
	else if (x > pRoot->data)
		Remove(pRoot->pRight, x);
	else makeDel(pRoot);
}

node* createTree(int a[], int n)
{
	node* pRoot = NULL;
	for (int i = 0; i < n; i++)
		insert(pRoot, a[i]);
	return pRoot;
}

void createTreeOn(node* &pRoot, int a[], int start, int end)
{
	if (start > end)
		return;
	int mid = (start + end) / 2;
	pRoot = getNode(a[mid]);
	createTreeOn(pRoot->pLeft, a, start, mid-1);
	createTreeOn(pRoot->pRight, a, mid+1, end);
}
void removeTree(node* pRoot)
{
	if (pRoot)
	{
		removeTree(pRoot->pLeft);
		removeTree((pRoot->pRight));
		delete pRoot;
		pRoot = NULL;
	}
}
int main()
{
	int a[] = { 1, 2, 3, 4, 5, 6, 7 };
	node* pRoot = NULL;
	int n = sizeof(a) / sizeof(int);
	createTreeOn(pRoot, a, 0, n-1);
	NLR(pRoot);
	removeTree(pRoot);
	return 0;
}