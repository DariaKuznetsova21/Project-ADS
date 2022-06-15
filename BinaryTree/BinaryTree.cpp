#pragma once
#include <random>
#include <iostream>
#include <vector>
#include <cstdlib>

bool check(std::vector<int> a, int b)
{
	for (int i = 0; i < a.size(); i++) {
		if (a.at(i) == b) return true;
	}
	return false;
}

std::vector<int> OptimalKeys(int** R, std::vector<int> d) {

	int n = d.size() + 1;

	std::vector<int> a;
	int i = 0, j = n - 1;
	a.push_back(d[R[i][j] - 1]);

	for (j = n - 1; j > 0; j--) {
		for (i = 0; i < j; i++) {
			if (!check(a, d[R[i][j] - 1])) a.push_back(d[R[i][j] - 1]);
		}
	}

	/*for (int t = 0; t < a.size(); t++) {
		cout << a.at(t) << " ";
	}*/

	return a;
}

class Node
{
private:
	int key;
	Node* leftChild, * rightChild;
public:
	friend class BinaryTree;
	friend class SearchBTree;
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
	virtual ~BinaryTree();
	void clear();
	bool isEmpty();
	int GetSumOfKeys();
	virtual int GetMinKey();
	Node* ParentOfNode(const int key);
	virtual int GetLevel(const int key);
	BinaryTree(BinaryTree& BTree2); 
	void copy(Node* subTreeRoot, Node*& copyRoot);
	void DeleteSubTree(Node& subTreeRoot);
	void clear(Node& subTreeRoot);
	bool isEmpty(Node& subTreeRoot);
	int height();
	int heightNode(Node& subTreeRoot);
	virtual int GetLevel(const int FindKey, Node& subTreeRoot, const int level);
	int NumberOfNodes();
	int NumberOfNodes(Node& subTreeRoot);
	virtual bool addNode(const int key);
	virtual bool addNode(Node& subTreeRoot, const int key);
	virtual bool deleteNode(const int key);
	virtual bool deleteNode(const int key, Node& subTreeRoot);
	void printLevel(Node& subTreeRoot, const int level, const int currentLevel = 0);
	std::vector <int> MassiveOfNodes(Node& subTreeRoot, std:: vector<int> keys);
	virtual int GetMinKey(Node& subTreeRoot);
	virtual int GetMaxKey(Node& subTreeRoot);
	bool CheckingForBalance(Node& subTreeRoot);
	Node* findNode(Node& SearchNode, const int SearchKey);
	Node* GetNode(Node& subTreeRoot);
	BinaryTree& operator = (BinaryTree& CopyTree);
	void printLevel();
	Node* getRoot();
	Node* findNode(const int key);
	bool CheckingForBalance();
	void print();
	std::vector <int> MassiveOfNodes(std::vector<int> keys);
	virtual int GetMaxKey();
	void printLevel(const int level);
protected:
	Node* m_root = nullptr;
	void DeleteSubTree(Node* subTreeRoot);
	void clear(Node* subTreeRoot);
	bool isEmpty(Node* subTreeRoot) const;
	int heightNode(Node* subTreeRoot) const;
	BinaryTree(int* a, int n);
	virtual int GetLevel(const int FindKey, Node* subTreeRoot, const int level) const;
	int NumberOfNodes(Node* subTreeRoot) const;
	virtual bool addNode(Node* subTreeRoot, const int key);
	virtual bool deleteNode(const int key, Node* subTreeRoot);
	Node* ParentOfNode(const int key, Node* subTreeRoot) const;
	void printLevel(Node* subTreeRoot, const int level, const int currentLevel = 0) const;
	std::vector <int> MassiveOfNodes(Node* subTreeRoot, std::vector<int> keys) const;
	virtual int GetMinKey(Node* subTreeRoot)const;
	virtual int GetMaxKey(Node* subTreeRoot)const;
	bool CheckingForBalance(Node* subTreeRoot) const;
	Node* findNode(Node* SearchNode, const int SearchKey) const;
};

Node* BinaryTree::GetNode(Node& subTreeRoot) 
{
	Node* temp = &subTreeRoot;
	return temp;
}


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

bool BinaryTree::addNode(Node& subTreeRoot, const int key)
{
	return addNode(GetNode(subTreeRoot), key);
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


void BinaryTree::copy (Node* outTree, Node*& inTree)// Копирование
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

void BinaryTree::DeleteSubTree(Node& subTreeRoot)
{
	return DeleteSubTree(GetNode(subTreeRoot));
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

void BinaryTree::clear(Node& subTreeRoot)
{
	return clear(GetNode(subTreeRoot));
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

Node* BinaryTree::findNode(Node& subTreeRoot, int SearchKey)
{
	Node* temp = GetNode(subTreeRoot);
	return findNode(temp, SearchKey);
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

void BinaryTree::printLevel()
{
	for (int i = 0; i < height(); i++) {
		printLevel(i);
		std::cout << std::endl;
	}
}


void BinaryTree:: printLevel(const int level)
{
	printLevel(m_root, level, 0);
}

void BinaryTree::printLevel(Node& subTreeRoot, const int level, const int currentLevel)
{
	return printLevel(GetNode(subTreeRoot), level, currentLevel);
}


void BinaryTree :: printLevel(Node* subTreeRoot, const int level, const int currentLevel) const
{
	using std::cout;
	using std::endl;

	if (currentLevel == level) {
		if (subTreeRoot == nullptr) {
			cout << "N" << " ";
		}
		else {
			cout << subTreeRoot->key << " ";
		}
	}
	else if (currentLevel < level) {
		if (subTreeRoot == nullptr) {
			printLevel(nullptr, level, currentLevel + 1);
			printLevel(nullptr, level, currentLevel + 1);
		}
		else {
			printLevel(subTreeRoot->leftChild, level, currentLevel + 1);
			printLevel(subTreeRoot->rightChild, level, currentLevel + 1);
		}
		
	}

}


bool BinaryTree::isEmpty()
{
	return isEmpty(m_root);
}

bool BinaryTree::isEmpty(Node& subTreeRoot)
{
	return isEmpty(GetNode(subTreeRoot));
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

int BinaryTree::NumberOfNodes() 
{
	return NumberOfNodes(m_root);
}

int BinaryTree::NumberOfNodes(Node& subTreeRoot)
{
	return NumberOfNodes(GetNode(subTreeRoot));
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

std::vector <int> BinaryTree::MassiveOfNodes(Node& subTreeRoot, std::vector<int> keys)
{
	return MassiveOfNodes(GetNode(subTreeRoot), keys);
}

std::vector <int> BinaryTree::MassiveOfNodes(Node* subTreeRoot, std::vector<int> keys) const
{
	
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



int BinaryTree:: height()
{
	return heightNode(m_root);
}

int BinaryTree::heightNode(Node& subTreeRoot)
{
	return heightNode(GetNode(subTreeRoot));
}

int BinaryTree::heightNode(Node* subTreeRoot) const
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
		HieghtR = heightNode(subTreeRoot-> rightChild);
	}
	if (HieghtL > HieghtR)
		return HieghtL + 1;
	return HieghtR + 1;
}

int BinaryTree::GetLevel(const int FindKey)
{
	return GetLevel(FindKey, m_root, 0);
}

int BinaryTree::GetLevel(const int FindKey, Node& subTreeRoot, const int level)
{
	return GetLevel(FindKey, GetNode(subTreeRoot), level);
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


int BinaryTree:: GetMinKey()
{
	return GetMinKey(m_root);
}

int BinaryTree::GetMinKey(Node& subTreeRoot)
{
	return GetMinKey(GetNode(subTreeRoot));
}


int BinaryTree::GetMinKey(Node* subTreeRoot)const
{
	if (subTreeRoot == nullptr)
		return -1;
	int minL = subTreeRoot->key, minR = subTreeRoot->key;
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

int BinaryTree:: GetMaxKey()
{
	return GetMaxKey(m_root);
}

int BinaryTree::GetMaxKey(Node& subTreeRoot)
{
	return GetMaxKey(GetNode(subTreeRoot));
}

int BinaryTree::GetMaxKey(Node* subTreeRoot)const
{
	if (subTreeRoot == nullptr)
		return -1;
	int maxL = subTreeRoot->key, maxR = subTreeRoot->key;
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

bool BinaryTree::CheckingForBalance()
{
	return CheckingForBalance(m_root);
}

bool BinaryTree::CheckingForBalance(Node& subTreeRoot)
{
	return CheckingForBalance(GetNode(subTreeRoot));
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

Node* BinaryTree::ParentOfNode(const int key)
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
		return additional;
	}
	additional = ParentOfNode(SearchKey, subTreeRoot->rightChild);
	if (additional) {
		return additional;
	}
	return nullptr;
}
			

bool BinaryTree::deleteNode(const int key)
{
	Node* deletedNode = findNode(key);
	if (deletedNode)
		return deleteNode(key, deletedNode);
	else
		return false;
}


bool BinaryTree::deleteNode(const int key, Node& subTreeRoot)
{
	return deleteNode(key, GetNode(subTreeRoot));
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
		delete m_root;
		m_root = nullptr;
		return true;
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



class SearchBTree : public BinaryTree
{
public:
	SearchBTree() = default;
	~SearchBTree() {};
	SearchBTree(SearchBTree& BTree2) : BinaryTree(BTree2) {};
	SearchBTree(int* a, int n);
	
	int GetLevel(const int FindKey, Node& subTreeRoot, const int level) override;
	bool addNode(const int key);
	int GetMinKey();
	int GetMaxKey();
	bool addNode(Node& subTreeRoot, const int key) override;
	Node* findNode(Node& SearchNode, const int SearchKey);
	bool deleteNode(const int key) override;
	bool deleteNode(const int key, Node& subTreeRoot) override;
	int GetMinKey(Node& subTreeRoot) override;
	int GetMaxKey(Node& subTreeRoot) override;
	SearchBTree OptimalSearchTree(std::vector <int> const& d, std::vector <int> const& p, std::vector <int > const& q);
	
	SearchBTree& operator= (SearchBTree& CopyTree);
protected:
	Node* ParentOfNode(const int key);
	Node* ParentOfNode(const int key, Node* subTreeRoot) const;
	Node* findNode(const int key);
	Node* findNode(Node* SearchNode, const int SearchKey) const;
	int GetLevel(const int key);
	int GetLevel(const int FindKey, Node* subTreeRoot, const int level)const;
	bool addNode(Node* subTreeRoot, const int key);
	int GetMinKey(Node* subTreeRoot)const;
	int GetMaxKey(Node* subTreeRoot)const;
	bool deleteNode(const int key, Node* subTreeRoot);

};


SearchBTree::SearchBTree(int* a, int n) //конструктор с двумя параметрами, где а-массив элементов, n-кол-во элементов
{
	m_root = nullptr;
	for (int i = 0; i < n; i++)
	{
		addNode(m_root, a[i]);
	}
}


bool SearchBTree::addNode(const int key)
{
	return addNode(m_root, key);
}

bool SearchBTree::addNode(Node& subTreeRoot, const int key)
{
	return addNode(GetNode(subTreeRoot), key);
}

bool SearchBTree::addNode(Node* subTreeRoot, const int key) 
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
	if(subTreeRoot->KeyOfNode() <= key)
	{
		if (subTreeRoot->rightChild == nullptr) {
			subTreeRoot->rightChild = new Node(key);
			return true;
		}
		else {
			addNode(subTreeRoot->rightChild, key);
			return true;
		}
	}
	else {
		if (subTreeRoot->leftChild == nullptr) {
			subTreeRoot->leftChild = new Node(key);
			return true;
		}
		else {
			addNode(subTreeRoot->leftChild, key);
			return true;
		}
	}
}
int SearchBTree::GetLevel(const int FindKey)
{
	return GetLevel(FindKey, m_root, 0);
}

int SearchBTree::GetLevel(const int FindKey, Node& subTreeRoot, const int level)
{
	return GetLevel(FindKey, GetNode(subTreeRoot), level);
}

int SearchBTree::GetLevel(const int FindKey, Node* subTreeRoot, const int level) const
{
	if (subTreeRoot == nullptr)
		return -1;
	if (FindKey == subTreeRoot->key)
		return level;
	else if (subTreeRoot->rightChild == nullptr && subTreeRoot->leftChild == nullptr)
		return -1;
	if (FindKey >= subTreeRoot->key) 
	{
		int level_R = GetLevel(FindKey, subTreeRoot->rightChild, level + 1);
		if (level_R != -1)
			return level_R;
	}
	else {
		int level_L = GetLevel(FindKey, subTreeRoot->leftChild, level + 1);
		if (level_L != -1)
			return level_L;
	}
}

Node* SearchBTree::findNode(int key)
{
	Node* SearchNode = findNode(m_root, key);
	return SearchNode;
}

Node* SearchBTree::findNode(Node& subTreeRoot, int SearchKey)
{
	return findNode(GetNode(subTreeRoot), SearchKey);
}

Node* SearchBTree::findNode(Node* subTreeRoot, int SearchKey) const
{
	if (subTreeRoot == nullptr)
		return nullptr;
	if (SearchKey == subTreeRoot->key)
		return subTreeRoot;
	if (subTreeRoot->leftChild == nullptr && subTreeRoot->rightChild == nullptr)
		return nullptr;
	if (subTreeRoot->rightChild && SearchKey >= subTreeRoot->key) {
		if (subTreeRoot->rightChild->key == SearchKey)
			return subTreeRoot->rightChild;
		else 
			return findNode(subTreeRoot->rightChild, SearchKey);
	}
	else if (subTreeRoot->leftChild && SearchKey < subTreeRoot->key) 
	{
		if (subTreeRoot->leftChild->key == SearchKey)
			return subTreeRoot->leftChild;
		else
			return findNode(subTreeRoot->leftChild, SearchKey);
	}
}

int SearchBTree::GetMinKey()
{
	return GetMinKey(m_root);
}

int SearchBTree::GetMinKey(Node& subTreeRoot)
{
	return GetMinKey(GetNode(subTreeRoot));
}

int SearchBTree::GetMinKey(Node* subTreeRoot)const
{
	if (subTreeRoot == nullptr)
		return -1;
	int min = subTreeRoot->key;
	if (subTreeRoot->leftChild == nullptr && subTreeRoot->rightChild == nullptr)
		return subTreeRoot->key;
	if (subTreeRoot->leftChild) {
		if (subTreeRoot->leftChild->key < min) {
			min = subTreeRoot->leftChild->key;
		}
	}
	return min;
}

int SearchBTree::GetMaxKey()
{
	return GetMaxKey(m_root);
}

int SearchBTree::GetMaxKey(Node& subTreeRoot)
{
	return GetMaxKey(GetNode(subTreeRoot));
}

int SearchBTree::GetMaxKey(Node* subTreeRoot)const
{
	if (subTreeRoot == nullptr)
		return -1;
	int max = subTreeRoot->key;
	if (subTreeRoot->rightChild) {

		max = GetMaxKey(subTreeRoot->rightChild);
	}
	return max;
}

Node* SearchBTree::ParentOfNode(const int key)
{
	return ParentOfNode(key, m_root);
}

Node* SearchBTree::ParentOfNode(const int SearchKey, Node* subTreeRoot) const
{
	if (subTreeRoot == nullptr)
		return nullptr;
	if (SearchKey == subTreeRoot->key)
		return nullptr;
	if (subTreeRoot->leftChild == nullptr && subTreeRoot->rightChild == nullptr)
		return nullptr;
	if (subTreeRoot->leftChild && subTreeRoot->leftChild->key >=SearchKey)
		if (subTreeRoot->leftChild->key == SearchKey)
			return subTreeRoot;
	if (subTreeRoot->rightChild && subTreeRoot->rightChild->key <= SearchKey)
		if (subTreeRoot->rightChild->key == SearchKey)
			return subTreeRoot;
	Node* additional = ParentOfNode(SearchKey, subTreeRoot->leftChild);
	if (additional) {
		return additional;
	}
	additional = ParentOfNode(SearchKey, subTreeRoot->rightChild);
	if (additional) {
		return additional;
	}
	return nullptr;
}


bool SearchBTree::deleteNode(const int key)
{
	Node* deletedNode = findNode(key);
	if (deletedNode)
		return deleteNode(key, deletedNode);
	else
		return false;
}

bool SearchBTree::deleteNode(const int key, Node& subTreeRoot)
{
	return deleteNode(key, GetNode(subTreeRoot));
}


bool SearchBTree::deleteNode(const int key, Node* subTreeRoot)
{  
	if (subTreeRoot == nullptr)
		return false;
	if (subTreeRoot == m_root) {
		if (subTreeRoot->rightChild) {
			m_root = subTreeRoot->rightChild;
			if (subTreeRoot->leftChild) {
				Node* node = subTreeRoot->rightChild;
				while (node->leftChild) {
						node = node->leftChild;
				}
				node->leftChild = subTreeRoot->leftChild;
			}
			delete subTreeRoot;
			return true;
		}
		if (subTreeRoot->leftChild) {
			m_root = subTreeRoot->leftChild;
			delete subTreeRoot;
			return true;
		}
		delete m_root;
		m_root = nullptr;
		return true;
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
		Node* parent = ParentOfNode(key);
		if (parent->leftChild == subTreeRoot)
		{
			parent->leftChild = subTreeRoot->rightChild;
			Node* additional = subTreeRoot->rightChild;
			while (additional->leftChild)
			{
				additional = additional->leftChild;
			}
			additional->leftChild = subTreeRoot->leftChild;
			delete subTreeRoot;
			return true;
		}
		else
		{
			parent->rightChild = subTreeRoot->rightChild;
			Node* additional = subTreeRoot->rightChild;
			while (additional->leftChild)
			{
				additional = additional->leftChild;
			}
			additional->leftChild = subTreeRoot->leftChild;
			delete subTreeRoot;
			return true;
		}
	}
	if (subTreeRoot->leftChild)
	{
		Node* parent = ParentOfNode(key);
		if (parent->leftChild == subTreeRoot)
		{
			parent->leftChild = subTreeRoot->leftChild;
			delete subTreeRoot;
			return true;
		}
		else
		{
			parent->rightChild = subTreeRoot->leftChild;
			delete subTreeRoot;
			return true;
		}
	}

	if (subTreeRoot->rightChild)
	{
		Node* parent = ParentOfNode(key);
		if (parent->rightChild && parent->rightChild == subTreeRoot)
		{
			parent->rightChild = subTreeRoot->rightChild;
			delete subTreeRoot;
			return true;
		}
		else
		{
			parent->leftChild = subTreeRoot->rightChild;
			delete subTreeRoot;
			return true;
		}
	}

	return false;


}
SearchBTree& SearchBTree:: operator= (SearchBTree& outTree)
{
	if (&outTree == this) {
		std::cerr << "The same tree";
		return *this;
	}
	else {
		BinaryTree::operator=(outTree);
		return *this;
	}
}

SearchBTree SearchBTree::OptimalSearchTree(std::vector <int> const& d, std::vector <int> const& p, std::vector <int > const& q) {
	const int n = d.size() + 1;

	if (not ((d.size() == p.size()) and (n == q.size())) or n == 1)
		std::cerr << "incorrect data" << std::endl;
	
	int** W = new int* [n];
	for (int i = 0; i < n; i++) {
		W[i] = new int[n];
		for (int j = 0; j < n; j++) {
			W[i][j] = 0;
		}
	}

	int** C = new int* [n];
	for (int i = 0; i < n; i++) {
		C[i] = new int[n];
		for (int j = 0; j < n; j++) {
			C[i][j] = 0;
		}
	}

	int** R = new int* [n];
	for (int i = 0; i < n; i++) {
		R[i] = new int[n];
		for (int j = 0; j < n; j++) {
			R[i][j] = 0;
		}
	}

	// заполнение таблицы W ловушками
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j)
				W[i][j] = q[j];
			if (i + 1 <= j)
				W[i][j] = W[i][j - 1] + p[j - 1] + q[j];
		}
	}

	// заполнение таблицы C 
	for (int i = 0; i < n; i++) {
		C[i][i] = q[i];
	}
	for (int i = 0; i < n - 1; i++) {
		C[i][i + 1] = W[i][i + 1] + C[i][i] + C[i + 1][i + 1];
		R[i][i + 1] = i + 1;
	}

	for (int x = 2; x < n; x++) {
		for (int i = 0; i < n - x; i++) {
			int m = 0, k = m + i + 1;
			int _min = C[i][m + i] + C[m + i + 1][x + i];
			for (m = 1; m < x; m++) {
				if (C[i][m + i] + C[m + i + 1][x + i] < _min) {
					_min = C[i][m + i] + C[m + i + 1][x + i];
					k = m + i + 1;
				}
			}
			C[i][x + i] = W[i][x + i] + _min;
			R[i][x + i] = k;
		}
	}

	/*for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			std::cout.width(3);
			std::cout << W[i][j] << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			std::cout.width(3);
			std::cout << C[i][j] << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			std::cout.width(3);
			std::cout << R[i][j] << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";*/

	SearchBTree tree;
	std::vector <int> keys = OptimalKeys(R, d);
	for (int i = 0; i < keys.size(); i++)
		tree.addNode(keys[i]);

	tree.printLevel();
	return tree;
}


bool testSearchTree(int size)
{
	int failedCase = 0;
	SearchBTree searchTree;
	std::vector<int> nodesKeys;

	for (int i = 0; i < size; ++i) {
		searchTree.addNode(i);
		nodesKeys.push_back(i);
	}

	int index, key;

	searchTree.deleteNode(13);

	while (nodesKeys.size()) {
		// index = rand() % nodesKeys.size();
		// nodesKeys.erase(nodesKeys.begin() + index);
		// if (!searchTree.deleteKnot(searchTree.getRoot(), index)) {
		// failedCase = 1;
		// break;
		// }

		/*if (testSearchTree(searchTree, nodesKeys.size())) {
		failedCase = 2;
		break;
		}*/

		if (nodesKeys.size()) {
			index = rand() % nodesKeys.size();
			key = nodesKeys[index];
			nodesKeys.erase(nodesKeys.begin() + index);
			if (!searchTree.deleteNode(key)) {
				failedCase = 3;
				break;
			}

			/*if (testSearchTree(searchTree, nodesKeys.size())) {
			failedCase = 4;
			break;
			}*/
		}
	}

	if (failedCase || !searchTree.isEmpty()) {
		if (!failedCase) {
			failedCase = -1;
		}

		std :: cout << size << " " << searchTree.NumberOfNodes() << std::endl;
		searchTree.printLevel();
		std::cout << std::endl;
		std::cout << std::endl;

	}
	return (failedCase == 0);
}



bool testSearchTreeAsBinaryTree(int size)
{
	int failedCase = 0;
	SearchBTree searchTree;
	BinaryTree& searchTreeRef = searchTree;
	std::vector<int> nodesKeys;

	for (int i = 0; i < size; ++i) {
		searchTreeRef.addNode(i);
		nodesKeys.push_back(i);
	}
	int index, key;

	searchTree.deleteNode(13);

	while (nodesKeys.size()) {
		/*index = rand() % nodesKeys.size();
		nodesKeys.erase(nodesKeys.begin() + index);
		if (!searchTreeRef.deleteKnot(searchTreeRef.getRoot(), index)) {
		failedCase = 1;
		break;
		}*/

		/*if (testSearchTreeAsBinaryTree(searchTreeRef, nodesKeys.size())) {
		failedCase = 2;
		break;
		}*/

		if (nodesKeys.size()) {
			index = rand() % nodesKeys.size();
			key = nodesKeys[index];
			nodesKeys.erase(nodesKeys.begin() + index);
			if (!searchTreeRef.deleteNode(key)) {
				failedCase = 3;
				break;
			}

			/*if (testSearchTreeAsBinaryTree(searchTreeRef, nodesKeys.size())) {
			failedCase = 4;
			break;
			}*/
		}
	}

	if (failedCase || !searchTreeRef.isEmpty()) {
		if (!failedCase) {
			failedCase = -1;
		}

		std::cout << size << " " << searchTreeRef.NumberOfNodes() << std::endl;
		searchTreeRef.printLevel();
		std::cout << std::endl;
		std::cout << std::endl;

	}
	return (failedCase == 0);
}





int main()
{
	//return testSearchTreeAsBinaryTree(15);
	int* a = new int[10];
	for (int i = 0; i < 10; i++) {
		a[i] = i;	
	}

	SearchBTree opTree;
	
	std::vector<int> d{10, 20, 30, 40};
	std::vector<int> p{2, 1, 1, 5};
	std::vector<int> q{1, 10, 1, 1, 10};
	
	opTree.OptimalSearchTree(d, p, q).printLevel();
	//std::cout << opTree.getRoot()->KeyOfNode();
	
	return 0;
}