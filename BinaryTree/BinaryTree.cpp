#include <random>
#include <iostream>

#pragma once

#include <vector>
#include <cstdlib>

class Node
{
private:
	int key;
	Node* leftChild, * rightChild;
public:
	friend class BinaryTree;
	Node()
	{
		key = 0;
		leftChild = nullptr;
		rightChild = nullptr;
	}

	Node(int k)
	{
		key = k;
		leftChild = nullptr;
		rightChild = nullptr;
	}

	int numberOfChildren() const
	{
		int count = 0;
		if (leftChild != nullptr)
		{
			count++;
		}
		if (rightChild != nullptr)
		{
			count++;
		}
		return count;
	}

	int KeyOfNode()const
	{
		return key;
	}
	
};

class BinaryTree
{
public:
	BinaryTree() = default; 
	~BinaryTree(); //+
	BinaryTree(BinaryTree& BTree2); //+
	BinaryTree(int* a, int n);
	void copy(const Node* subTreeRoot, Node*& copyRoot);
	Node* getRoot();
	void DeleteSubTree(Node* subTreeRoot);
	void clear();
	void clear(Node* subTreeRoot);
	bool isEmpty() const;
	bool isEmpty(Node* subTreeRoot) const;
	int height() const;
	int heightNode(Node* subTreeRoot) const;
	int GetLevel(int key);
	int GetLevel(int FindKey, Node* subTreeRoot, int level)const;
	int NumberOfNodes() const;
	int NumberOfNodes(Node* subTreeRoot) const;
	bool addNode(const int key);
	bool addNode(Node* subTreeRoot, const int key);
	Node* findNode(int key);
	Node* findNode(Node* SearchNode, int SearchKey);
	int deleteNode(const int key);
	void printLevel(const int level);
	void printLevel(Node* subTreeRoot, const int level, const int currentLevel = 0);
	std::vector <int> MassiveOfNodes(std::vector<int> keys);
	std::vector <int> MassiveOfNodes(Node* subTreeRoot, std:: vector<int> keys);
	int GetSumOfKeys();
	int GetMinKey()const;
	int GetMinKey(Node* subTreeRoot)const;
	int GetMaxKey()const;
	int GetMaxKey(Node* subTreeRoot)const;
	bool CheckingForBalance() const;
	bool CheckingForBalance( Node* subTreeRoot)const;
	void print();
	BinaryTree& operator = (BinaryTree& CopyTree);
protected:
	Node* m_root = nullptr;
};

Node* BinaryTree::getRoot()
{
	return m_root;
}

BinaryTree::BinaryTree (BinaryTree& outTree) //конструктор копирования
{
	copy(outTree.getRoot(), this->m_root);
}

BinaryTree::BinaryTree(int* a, int n) //конструктор с двумя параметрами, где а-массив элементов, n-кол-во элементов
{
	m_root = nullptr;
	for (int i = 0; i < n; i++)
	{
		addNode(m_root, a[i]);
	}
}

bool BinaryTree::addNode(const int key) 
{
	return addNode(m_root, key);
}


bool BinaryTree::addNode(Node* subTreeRoot, const int key) //Добавление узла
{
	if (subTreeRoot == nullptr) {
		if (m_root == nullptr) {
			m_root = new Node(key);
			return true;
		}
		else {
			return false;
		}
		
	}

	if (subTreeRoot->leftChild == nullptr) {
		subTreeRoot->leftChild = new Node(key);
		return true;
	}
	 if (subTreeRoot->rightChild == nullptr) {
		subTreeRoot->rightChild = new Node(key);
		return true;
	}
	if (rand() % 2) {
		addNode(subTreeRoot->leftChild, key);
		return true;
	}
	else {
		return addNode(subTreeRoot->rightChild, key);
		return true;
	}
	
}


void BinaryTree::copy (const Node* outTree, Node*& inTree)// Копирование
{
	if (outTree == nullptr)
	{
		return;
	}
	if (outTree == inTree) 
	{
		return;
	}
	if(outTree) {
		inTree = new Node;
		inTree->key = outTree->key;
		inTree->leftChild = nullptr;
		inTree->rightChild = nullptr;
		copy(outTree->leftChild, inTree->leftChild);
		copy(outTree->rightChild, inTree->rightChild);
	}	
}

void BinaryTree::DeleteSubTree(Node* subTreeRoot)
{
	if (subTreeRoot == nullptr)
		return;
	if (subTreeRoot->leftChild){
		clear(subTreeRoot->leftChild);
		subTreeRoot->leftChild = nullptr;
	}

	if (subTreeRoot->rightChild) {
		clear(subTreeRoot->rightChild);
		subTreeRoot->rightChild = nullptr;
	}

}

void BinaryTree::clear()
{
	clear(m_root);
}


void BinaryTree::clear(Node* subTreeRoot)
{
	if (subTreeRoot == nullptr)
		return;
	if(subTreeRoot->leftChild)
		clear(subTreeRoot->leftChild);
	if(subTreeRoot->rightChild)
		clear(subTreeRoot->rightChild);
	if (subTreeRoot == m_root) {
		subTreeRoot = nullptr;
	}
	subTreeRoot = nullptr;
}

BinaryTree::~BinaryTree() //деструктор
{
	if(m_root)
		clear(m_root);
}


Node* BinaryTree::findNode(int key)
{
	Node* SearchNode = findNode(m_root, key);
	return SearchNode;
}

Node* BinaryTree::findNode(Node* subTreeRoot, int SearchKey)
{
	if (subTreeRoot == nullptr)
		return subTreeRoot;
	if (SearchKey == subTreeRoot->key)
		return subTreeRoot;
	subTreeRoot = findNode(subTreeRoot->leftChild, SearchKey);
	subTreeRoot = findNode(subTreeRoot->rightChild, SearchKey);
	return subTreeRoot;
}

void BinaryTree:: print() 
{
	using std::cout;
	using std::endl;

	int h = height();

	if (h) {
		for (int i = 0; i < h; i++) {
			printLevel(i);
		}
	}
}



void BinaryTree:: printLevel(const int level)
{
	printLevel(m_root, level, 0);
}

void BinaryTree :: printLevel(Node* subTreeRoot, const int level, const int currentLevel)
{
	using std::cout;
	using std::endl;


	if (subTreeRoot == nullptr) {
		if (subTreeRoot == m_root) {
			cout << "Tree is empty" << endl;
		}
		return;
	}

	if (currentLevel == level) {
		cout << subTreeRoot->key << "   ";
	}
	else if (currentLevel < level) {
		printLevel(subTreeRoot->leftChild, level, currentLevel + 1);
		printLevel(subTreeRoot->rightChild, level, currentLevel + 1);
	}

}


bool BinaryTree::isEmpty() const
{
	return isEmpty(m_root);
}

bool BinaryTree::isEmpty(Node* subTreeRoot) const
{
	if (subTreeRoot == nullptr)
		return true;
	return false;
}

BinaryTree& BinaryTree:: operator = (BinaryTree& outTree) 
{
	if (&outTree == this) {
		std::cerr << "The same tree";
		return *this;
	}
	else {
		clear(this->m_root);
		copy(outTree.getRoot(), this->m_root);
	}
 }

int BinaryTree::NumberOfNodes() const 
{
	return NumberOfNodes(m_root);
}


int BinaryTree::NumberOfNodes(Node* subTreeRoot) const
{
	int left, right;
	if (subTreeRoot == nullptr)
		return 0;
	if (subTreeRoot->leftChild == nullptr && subTreeRoot->rightChild == nullptr)
		return 1;
	if (subTreeRoot->leftChild != nullptr)
		left = NumberOfNodes(subTreeRoot->leftChild);
	else
		left = 0;
	if (subTreeRoot->rightChild != nullptr)
		right = NumberOfNodes(subTreeRoot->rightChild);
	else
		right = 0;
	return right + left + 1;

}

std::vector <int> BinaryTree::MassiveOfNodes(std::vector<int> keys)

{
	return MassiveOfNodes(m_root, keys);
}

std::vector <int> BinaryTree::MassiveOfNodes(Node* subTreeRoot, std::vector<int> keys) 
{
	int c = NumberOfNodes(subTreeRoot);
	int left, right;
	
	if (subTreeRoot == nullptr) {
		return keys;
	}
	
	if (subTreeRoot->leftChild == nullptr && subTreeRoot->rightChild == nullptr) {
		//std::cout<< subTreeRoot->key << "e " ;

		keys.push_back(subTreeRoot->key);
		return keys;
	}
	keys = MassiveOfNodes(subTreeRoot->leftChild, keys);
	keys.push_back(subTreeRoot->key);
	keys = MassiveOfNodes(subTreeRoot->rightChild, keys);

	return keys;

}



int BinaryTree:: height() const
{
	return heightNode(m_root);
}
int BinaryTree::heightNode(Node* subTreeRoot) const
{
	if (subTreeRoot == nullptr)
		return 0;
	int h_l = heightNode(subTreeRoot->leftChild);
	int h_r = heightNode(subTreeRoot->rightChild);
	if (h_l > h_r) 
		return h_l + 1; 
	return h_r + 1;
}

int BinaryTree::GetLevel(int FindKey)
{
	return GetLevel(FindKey, m_root, 0);
}

int BinaryTree::GetLevel(int FindKey, Node* subTreeRoot, int level) const
{
	if (subTreeRoot == nullptr)
		return -1;
	if (FindKey == subTreeRoot->key)
		return level;
	else if (subTreeRoot->rightChild == nullptr && subTreeRoot->leftChild == nullptr) 
		return -1;
	int level_L = GetLevel(FindKey, subTreeRoot->leftChild, level + 1);
	if (level_L != -1)
		return level_L;
	int level_R = GetLevel(FindKey, subTreeRoot->rightChild, level + 1);
	if (level_L != -1)
		return level_R;
}


int BinaryTree:: GetMinKey()const
{
	return GetMinKey(m_root);
}
int BinaryTree::GetMinKey(Node* subTreeRoot)const
{
	int minL =subTreeRoot->key, minR=subTreeRoot->key;
	if (subTreeRoot == nullptr)
		return -1;
	if (subTreeRoot->leftChild == nullptr && subTreeRoot->rightChild == nullptr)
		return subTreeRoot->key;
	if (subTreeRoot->leftChild != nullptr) {
		if (subTreeRoot->leftChild->key < minL) {
			minL = subTreeRoot->leftChild->key;
		}
		minL = GetMinKey(subTreeRoot->leftChild);
	}

	if (subTreeRoot->rightChild != nullptr) {
		if (subTreeRoot->rightChild->key < minR) {
			minR = subTreeRoot->rightChild->key;
		}
		minR = GetMinKey(subTreeRoot->rightChild);
	}

	int min;
	if (minL < minR)
		min = minL;
	else
		min = minR;
	if (min < subTreeRoot->key)
		return min;
	else
		return subTreeRoot->key;
}

int BinaryTree:: GetMaxKey()const
{
	return GetMaxKey(m_root);
}
int BinaryTree::GetMaxKey(Node* subTreeRoot)const
{
	int maxL = subTreeRoot->key, maxR = subTreeRoot->key;
	if (subTreeRoot == nullptr)
		return -1;
	if (subTreeRoot->leftChild == nullptr && subTreeRoot->rightChild == nullptr)
		return subTreeRoot->key;
	if (subTreeRoot->leftChild != nullptr) {
		if (subTreeRoot->leftChild->key > maxL) {
			maxL = subTreeRoot->leftChild->key;
		}
		maxL = GetMaxKey(subTreeRoot->leftChild);
	}

	if (subTreeRoot->rightChild != nullptr) {
		if (subTreeRoot->rightChild->key > maxR) {
			maxR = subTreeRoot->rightChild->key;
		}
		maxR = GetMaxKey(subTreeRoot->rightChild);
	}

	int max;
	if (maxL > maxR)
		max = maxL;
	else
		max = maxR;
	if (max > subTreeRoot->key)
		return max;
	else
		return subTreeRoot->key;
}

int BinaryTree :: GetSumOfKeys() 
{
	std::vector<int> keys = {};
	int sum = 0;
	keys = MassiveOfNodes(keys);
	for (int i = 0; i < keys.size(); i++) {
		sum += keys[i];
	}
	return sum;

}

bool BinaryTree::CheckingForBalance() const
{
	return CheckingForBalance(m_root);
}

bool BinaryTree::CheckingForBalance(Node* subTreeRoot) const
{
	if (subTreeRoot == nullptr)
		return false;
	int height_l = heightNode(subTreeRoot->leftChild);
	int height_r = heightNode(subTreeRoot->rightChild);
	if ((height_r - height_l) == 0)
		return true;
	else
		return false;

}



int main()
{
	int* a = new int[10];
	for (int i = 0; i < 10; i++) {
		a[i] = i+1;
	}

	BinaryTree t1(a, 7);
	t1.printLevel(0);
	std::cout << std::endl;
	t1.printLevel(1);
	std::cout << std::endl;
	t1.printLevel(2);
	std::cout << std::endl;
	BinaryTree t2, t3;

	t2 = t3 = t1;
	t2.print();
	t3.print();

	// 
	/*std::vector <int> keys = {};
	keys = t1.MassiveOfNodes(keys);
	for (int i=0; i < keys.size(); i++) {
		std::cout << keys[i]<< " ";
	}*/

	/*int m;
	m = t1.GetSumOfKeys();
	std::cout << m << std::endl;*/

	//int k = t1.CheckingForBalance();
	//std::cout << k << std::endl;
	return 0;
}