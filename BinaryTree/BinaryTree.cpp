﻿#include <random>
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
	BinaryTree(const BinaryTree& BTree2); //+
	BinaryTree(int* a, int n);
	void copy(const Node* subTreeRoot, Node* copyRoot);
	Node& getRoot();
	void clear(Node* rt);
	bool isEmpty(Node* root) const;
	int height() const;
	int heightNode(Node* p) const;
	int NumberOfNodes(Node* root) const;
	bool addNode(Node* subTreeRoot, const int key);
	Node* findNode(int key);
	Node* findNode(Node* SearchNode, int SearchKey);
	int deleteNode(const int key);
	void printLevel(const int level);
	void printLevel(Node* subTreeRoot, const int level, const int currentLevel = 0);
	void print();
	BinaryTree& operator = (BinaryTree& CopyTree);
protected:
	Node* m_root = nullptr;
	Node& m_root1 = *m_root;
};




Node& BinaryTree::getRoot()
{
	return m_root1;
}

BinaryTree::BinaryTree (const BinaryTree& BTree) //конструктор копирования
{
	copy(BTree.m_root, this->m_root);
}

BinaryTree::BinaryTree(int* a, int n) //конструктор с двумя параметрами, где а-массив элементов, n-кол-во элементов
{
	m_root = nullptr;
	for (int i = 0; i < n; i++)
	{
		addNode(m_root, a[i]);
	}
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


void BinaryTree::copy (const Node* subTreeRoot, Node* copyRoot)// Копирование
{
	if (subTreeRoot == nullptr)
	{
		return;
	}
	if (subTreeRoot == copyRoot) 
	{
		return;
	}
	if(copyRoot) { 
		clear(copyRoot);
		copyRoot = new Node;
		copyRoot->key = subTreeRoot->key;
		copyRoot->leftChild = nullptr;
		copyRoot->rightChild = nullptr;
		copy(subTreeRoot->leftChild, copyRoot->leftChild);
		copy(subTreeRoot->rightChild, copyRoot->rightChild);
	}	
}




void BinaryTree::clear(Node* root) // Удаление
{
	if (root == nullptr) 
		return;
	if(root->leftChild)
		clear(root->leftChild);
	if(root->rightChild)
		clear(root->rightChild);
	if (root == m_root) {
		root = nullptr;
	}
	delete root;
}

BinaryTree::~BinaryTree() //деструктор
{
	if(m_root)
		clear(m_root);
}


Node* BinaryTree::findNode(int key)//ф-ция нахождения узла
{
	Node* SearchNode = findNode(m_root, key);//возвращаем нужный узел, либо NULL
	return SearchNode;//возвращаем узел
}

Node* BinaryTree::findNode(Node* SearchNode, int SearchKey)//ф-ция нахождения узла
{
	if (SearchNode == nullptr) 
		return SearchNode;//если узел пуст, возвращаемся 
	if (SearchKey == SearchNode->key)
		return SearchNode;//если искомое значение совпадает с ключём текущего узла, мы нашли его, возвращаем его
	SearchNode = findNode(SearchNode->leftChild, SearchKey);
	SearchNode = findNode(SearchNode->rightChild, SearchKey);
	return SearchNode;//возвращаем результат поисков
}

void BinaryTree:: print() {
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



bool BinaryTree::isEmpty(Node* root) const
{
	if (root == nullptr)
		return true;
	return false;
}

BinaryTree& BinaryTree:: operator = (BinaryTree& CopyTree) 
{
	if (&CopyTree == this) {
		std::cerr << "The same tree";
		return *this;
	}
	else {
		clear(this->m_root);
		copy(CopyTree.m_root, this->m_root);
	}
 }

int BinaryTree::NumberOfNodes(Node* root) const
{
	int left, right;
	if (root == nullptr)
		return 0;
	if (root->leftChild == nullptr && root->rightChild == nullptr)
		return 1;
	if (root->leftChild != nullptr)
		left = NumberOfNodes(root->leftChild);
	else
		left = 0;
	if (root->rightChild != nullptr)
		right = NumberOfNodes(root->rightChild);
	else
		right = 0;
	return right + left + 1;

}

//std:: vector <int> BinaryTree::MassiveOfNodes(Node* root) 
//{
//	int left, right;
//	std:: vector <int> count = {};
//	if (root == nullptr) {
//		return count;
//	}
//	if (root->leftChild == nullptr && root->rightChild == nullptr) {
//		count.push_back(root->key);
//		return count;
//	}
//	if (root->leftChild != nullptr) {};
//	
//
//}



int BinaryTree:: height() const //ф-ция вычисления высоты дерева
{
	return heightNode(m_root);
}
int BinaryTree::heightNode(Node* root) const //ф-ция вычисления высоты узла
{
	if (root == nullptr) 
		return 0; //у пустых деревьев и узлов соответствующая высота
	int h_l = heightNode(root->leftChild); //в высоту левого поддерева заносим рекурсией значение высоты левого потомка
	int h_r = heightNode(root->rightChild); //в высоту правого поддерева заносим рекурсией значение высоты правого потомка
	if (h_l > h_r) 
		return h_l + 1; //Если высота левого потомка больше правого, то высота корня данного поддерева соответственно на 1 больше
	return h_r + 1; //Иначе высота корня данного поддерева больше высоты правого поддерева на 1
}



int main()
{
	int* a = new int[10];
	for (int i = 0; i < 10; i++) {
		a[i] = i+1;
	}

	BinaryTree t1(a, 10);
	t1.print();

	int* a1 = new int[10];
	for (int i = 0; i < 10; i++) {
		a1[i] = i + 2;
	}

	BinaryTree t2(a1, 10);
	t2.print();

	t2 = t1;

	t2.print();

	return 0;
}