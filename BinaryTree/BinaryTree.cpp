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
	bool isEmpty(const Node* subTreeRoot) const;
	int height() const;
	int heightNode(const Node* subTreeRoot) const;
	int GetLevel(const int key) const;
	int GetLevel(const int FindKey, Node* subTreeRoot, const int level)const;
	int NumberOfNodes() const;
	int NumberOfNodes(const Node* subTreeRoot) const;
	bool addNode(const int key);
	bool addNode(Node* subTreeRoot, const int key);
	Node* findNode(const int key);
	Node* findNode(Node* SearchNode, const int SearchKey) const;
	bool deleteNode(const int key);
	bool deleteNode(const int key, Node* subTreeRoot);
	void printLevel(const int level) const;
	void printLevel(Node* subTreeRoot, const int level, const int currentLevel = 0) const;
	std::vector <int> MassiveOfNodes(std::vector<int> keys) const;
	std::vector <int> MassiveOfNodes(const Node* subTreeRoot, std:: vector<int> keys) const;
	int GetSumOfKeys() const;
	int GetMinKey()const;
	int GetMinKey(Node* subTreeRoot)const;
	int GetMaxKey()const;
	int GetMaxKey(Node* subTreeRoot)const;
	bool CheckingForBalance() const;
	bool CheckingForBalance(Node* subTreeRoot) const;
	void print() const;
	Node* ParentOfNode(const int key) const;
	Node* ParentOfNode(const int key, Node* subTreeRoot) const;
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


Node* BinaryTree::findNode(Node* subTreeRoot, int SearchKey) const
{
	if (subTreeRoot == nullptr)
		return nullptr;
	if (SearchKey == subTreeRoot->key)
		return subTreeRoot;
	if (subTreeRoot->leftChild == nullptr && subTreeRoot->rightChild == nullptr)
		return nullptr;
	if (subTreeRoot->leftChild) 
		if (subTreeRoot->leftChild->key == SearchKey)
			return subTreeRoot->leftChild;
	if (subTreeRoot->rightChild)
		if (subTreeRoot->rightChild->key == SearchKey)
			return subTreeRoot->rightChild;
	Node* additional = findNode(subTreeRoot->leftChild, SearchKey);
	if (additional == nullptr || additional->key != SearchKey)
		findNode(subTreeRoot->rightChild, SearchKey);
	else 
		return additional;
}



void BinaryTree:: print() const
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



void BinaryTree:: printLevel(const int level) const
{
	printLevel(m_root, level, 0);
}

void BinaryTree :: printLevel(Node* subTreeRoot, const int level, const int currentLevel) const
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

bool BinaryTree::isEmpty(const Node* subTreeRoot) const
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


int BinaryTree::NumberOfNodes(const Node* subTreeRoot) const
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

std::vector <int> BinaryTree::MassiveOfNodes(std::vector<int> keys) const

{
	return MassiveOfNodes(m_root, keys);
}

std::vector <int> BinaryTree::MassiveOfNodes(const Node* subTreeRoot, std::vector<int> keys) const
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
int BinaryTree::heightNode(const Node* subTreeRoot) const
{
	int HieghtL = 0, HieghtR = 0;
	if (subTreeRoot == nullptr)
		return 0;
	if (subTreeRoot->leftChild == nullptr && subTreeRoot->rightChild == nullptr)
		return 1;
	if (subTreeRoot->leftChild) {
		HieghtL = heightNode(subTreeRoot->leftChild);
	}

	if (subTreeRoot->rightChild) {
		HieghtR = heightNode(subTreeRoot->rightChild);
	}
	if (HieghtL > HieghtR)
		return HieghtL + 1;
	return HieghtR + 1;
}

int BinaryTree::GetLevel(const int FindKey) const
{
	return GetLevel(FindKey, m_root, 0);
}

int BinaryTree::GetLevel(const int FindKey, Node* subTreeRoot, const int level) const
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

int BinaryTree :: GetSumOfKeys()  const
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

Node* BinaryTree::ParentOfNode(const int key) const
{
	return ParentOfNode(key, m_root);
}

Node* BinaryTree:: ParentOfNode(const int SearchKey, Node* subTreeRoot) const
{
	if (subTreeRoot == nullptr)
		return nullptr;
	if (SearchKey == subTreeRoot->key)
		return nullptr;
	if (subTreeRoot->leftChild == nullptr && subTreeRoot->rightChild == nullptr)
		return nullptr;
	if (subTreeRoot->leftChild)
		if (subTreeRoot->leftChild->key == SearchKey)
			return subTreeRoot;
	if (subTreeRoot->rightChild)
		if (subTreeRoot->rightChild->key == SearchKey)
			return subTreeRoot;
	Node* additional = ParentOfNode(SearchKey, subTreeRoot->leftChild);
	if (additional) {
		if (additional->leftChild->key == SearchKey || additional->rightChild->key == SearchKey) {
			return additional;
		}
		else
			ParentOfNode(SearchKey, subTreeRoot->rightChild);
	}
	else
		ParentOfNode(SearchKey, subTreeRoot->rightChild);
}
			

bool BinaryTree::deleteNode(const int key)
{
	Node* deletedNode = findNode(key);
	if (deletedNode)
		return deleteNode(key, deletedNode);
	else
		return false;
}
bool BinaryTree::deleteNode(const int key, Node* subTreeRoot)
{
	if (subTreeRoot == nullptr)
		return false;
	if (subTreeRoot == m_root) {
		if (subTreeRoot->leftChild) {
			m_root = subTreeRoot->leftChild;
			if (subTreeRoot->rightChild) {
				Node* additional = subTreeRoot->leftChild;
				while(additional->leftChild){
					additional = additional->leftChild;
				}
				additional->leftChild = subTreeRoot->rightChild;
			}
			delete subTreeRoot;
			return true;
		}
		if (subTreeRoot->rightChild) {
			m_root = subTreeRoot->rightChild;
			delete subTreeRoot;
			return true;
		}
	}
	if (subTreeRoot->leftChild == nullptr && subTreeRoot->rightChild == nullptr) {
		Node* additional = ParentOfNode(key);
		if (additional) {
			if (additional->leftChild == subTreeRoot)
				additional->leftChild = nullptr;
			else
				additional->rightChild = nullptr;
		}
		delete subTreeRoot;
		return true;
	}
	if (subTreeRoot->rightChild && subTreeRoot->leftChild)
	{
		Node* additional = ParentOfNode(key);
		if (additional->leftChild == subTreeRoot)
		{
			additional->leftChild = subTreeRoot->leftChild;
			Node* temp = m_root;
			while (temp->leftChild)
			{
				temp = temp->leftChild;
			}
			temp->leftChild = subTreeRoot->rightChild;
			delete subTreeRoot;
			return true;
		}
		else
		{
			additional->rightChild = subTreeRoot->leftChild;
			Node* temp = m_root;
			while (temp->leftChild)
			{
				temp = temp->leftChild;
			}
			temp->leftChild = subTreeRoot->rightChild;
			delete subTreeRoot;
			return true;
		}
	}
	if (subTreeRoot->leftChild)
	{
		Node* additional = ParentOfNode(key);
		if (additional->leftChild == subTreeRoot)
		{
			additional->leftChild = subTreeRoot->leftChild;
			delete subTreeRoot;
			return true;
		}
		else
		{
			additional->rightChild = subTreeRoot->leftChild;
			delete subTreeRoot;
			return true;
		}
	}

	if (subTreeRoot->rightChild)
	{
		Node* additional = ParentOfNode(key);
		if (additional->leftChild == subTreeRoot)
		{
			additional->leftChild = subTreeRoot->rightChild;
			delete subTreeRoot;
			return true;
		}
		else
		{
			additional->rightChild = subTreeRoot->rightChild;
			delete subTreeRoot;
			return true;
		}
	}

	return false;


}

int main()
{
	int* a = new int[10];
	for (int i = 0; i < 10; i++) {
		a[i] = i+1;
	}

	BinaryTree t1(a, 10);
	t1.printLevel(0);
	std::cout << std::endl;
	t1.printLevel(1);
	std::cout << std::endl;
	t1.printLevel(2);
	std::cout << std::endl;
	t1.printLevel(3);
	std::cout << std::endl;
	BinaryTree t2;
	/*t2 = t1;
	t2.print();
	std::cout << std::endl;*/

	t1.ParentOfNode(10);
	std::cout << t1.deleteNode(2) << std::endl;
	t1.printLevel(0);
	std::cout << std::endl;
	t1.printLevel(1);
	std::cout << std::endl;
	t1.printLevel(2);
	std::cout << std::endl;
	t1.printLevel(3);
	std::cout << std::endl;
	
	/*Node* Nfinded = t2.findNode(6);
	Nfinded == nullptr ? std::cout << "Null" << std::endl : std::cout << Nfinded->KeyOfNode() << std::endl;*/
	

	
	
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