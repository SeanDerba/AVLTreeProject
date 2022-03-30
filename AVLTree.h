#pragma once

typedef int ItemType;

struct Node {
	ItemType data;
	Node* left;
	Node* right;
	int height; 
};


class AVLTree
{
private:
	int size;
	Node* root;

	int getSize(Node* node) const;
	bool searchItem(ItemType a, Node* n) const;
	void insertItem(ItemType a, Node*& n);
	void deleteItem(ItemType a, Node* &n);

	void printPreOrder(Node* node) const;
	void printInOrder(Node* node) const;
	void printPostOrder(Node* node) const;

	int max(int a, int b);
	int height(Node* N);
	int getBalance(Node* N);

	Node* rightRotate(Node* y);
	Node* leftRotate(Node* y);

public: 
	AVLTree();
	~AVLTree();
	
	bool isEmpty();
	bool isFull();

	int getSize() const;
	int getHeight(Node* n);
	ItemType getRoot() const;

	bool searchNode(ItemType a) const;
	void insertNode(ItemType a);
	void deleteNode(ItemType a);

	void printAVLpreOrder() const;
	void printAVLinOrder() const;
	void printAVLpostOrder() const;

};

