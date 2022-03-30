#include "AVLTree.h"
#include <iostream>

AVLTree::AVLTree() {
	size = 0;
	root = NULL;
}
AVLTree::~AVLTree() {

}

bool AVLTree::isEmpty() {
	return (root == NULL);
}
bool AVLTree::isFull() {
	Node* ptr = new Node;
	if (ptr == NULL) {
		return true;
	}
	delete ptr;
	return false;
}

int AVLTree::getSize() const {
	return getSize(root);
}

int AVLTree::getSize(Node* n) const{
	if (n == NULL) {
		return 0;
	}
	return (1 + getSize(n->left) + getSize(n->right));
}

ItemType AVLTree::getRoot() const {
	return root->data;
}

bool AVLTree::searchNode(ItemType a) const {
	return searchItem(a, root);
}

bool AVLTree::searchItem(ItemType a, Node* n) const {
	if (n == NULL) {
		return false;
	}
	else if (n->data == a) {
		return true;
	}
	else {
		if (n->data > a) {
			return searchItem(a, n->left);
		}
		else {
			return searchItem(a, n->right);
		}
	}
}

void AVLTree::insertNode(ItemType a) {
	insertItem(a, root);
}

void AVLTree::insertItem(ItemType a, Node*& n) {
	if (n == NULL) {
		n = new Node;
		n->data = a;
		n->left = NULL;
		n->right = NULL;
		n->height = 1; // New node always added as leaf
		size++;
		return;
	}
	else if (n->data > a) {
		insertItem(a, n->left);
	}
	else {
		insertItem(a, n->right);
	}
	
	n->height = 1 + max(height(n->left), height(n->right));

	int balance = getBalance(n);

	//LL
	if (balance > 1 && a < n->left->data) {
		n = rightRotate(n);
		return;
	}
	//RR
	if (balance < -1 && a > n->right->data) {
		n = leftRotate(n);
		return;
	}
	//LR
	if (balance > 1 && a > n->left->data) {
		n->left = leftRotate(n->left);
		n = rightRotate(n);
		return;
	}
	//RL
	if (balance < -1 && a < n->right->data) {
		n->right = rightRotate(n->right);
		n = leftRotate(n);
		return;
	}
}


void AVLTree::deleteNode(ItemType a) {
	deleteItem(a, root);
	size--;
}

void AVLTree::deleteItem(ItemType a, Node*& n) {
	if (n->data > a) {
		deleteItem(a, n->left);
	}
	else if (n->data < a) {
		deleteItem(a, n->right);
	}
	else {
		if (n->left == NULL && n->right == NULL) {	//No children
			delete n;
			n = NULL;
		}
		else if (n->left != NULL && n->right == NULL) {	//One child, left
			Node* temp = n->left;
			delete n;
			n = temp;
		}
		else if (n->right != NULL && n->left == NULL) {	//One child, right
			Node* temp = n->right;
			delete n;
			n = temp;
		}
		else {	//Two children
			Node* largest = n->left;

			while (largest->right != NULL) {	//Finds most right val in left subrtree
				largest = largest->right;
			}
			//largest->right = n->right;
			n->data = largest->data;
			deleteItem(largest->data, largest);
		}
		return;
	}

	n->height = 1 + max(height(root->left),height(root->right));
	int balance = getBalance(n);

	//LL
	if (balance > 1 && a < n->left->data) {
		n = rightRotate(n);
		return;
	}
	//RR
	if (balance < -1 && a > n->right->data) {
		n = leftRotate(n);
		return;
	}
	//LR
	if (balance > 1 && a > n->left->data) {
		n->left = leftRotate(n->left);
		n = rightRotate(n);
		return;
	}
	//RL
	if (balance < -1 && a < n->right->data) {
		n->right = rightRotate(n->right);
		n = leftRotate(n);
		return;
	}
}

void AVLTree::printAVLpreOrder() const {
	printPreOrder(root);
}

void AVLTree::printPreOrder(Node* node) const {
	if (node == NULL) {
		return;
	}
	std::cout << node->data << ' ';
	printPreOrder(node->left);
	printPreOrder(node->right);
}

void AVLTree::printAVLinOrder() const {
	printInOrder(root);
}

void AVLTree::printInOrder(Node* node) const {
	if (node == NULL) {
		return;
	}
	printInOrder(node->left);
	std::cout << node->data << ' ';
	printInOrder(node->right);
}


void AVLTree::printAVLpostOrder() const {
	printPostOrder(root);
}

void AVLTree::printPostOrder(Node* node) const {
	if (node == NULL) {
		return;
	}
	printPostOrder(node->left);
	printPostOrder(node->right);
	std::cout << node->data << ' ';
}

int AVLTree::max(int a, int b)
{
	if (a > b) {
		return a;
	}
	return b;
}

int AVLTree::height(Node* N)
{
	if (N == NULL)
		return 0;
	return N->height;
}

int AVLTree::getBalance(Node* N)
{
	if (N == NULL)
		return 0;
	return height(N->left) - height(N->right);
}

Node* AVLTree::rightRotate(Node* y) {
	Node* x = y->left;
	Node* T2 = x->right;

	// Perform rotation
	x->right = y;
	y->left = T2;

	// Update heights
	y->height = max(height(y->left), height(y->right)) + 1;
	x->height = max(height(x->left), height(x->right)) + 1;

	// Return new root
	return x;
}

Node* AVLTree::leftRotate(Node* x)
{
	Node* y = x->right;
	Node* T2 = y->left;

	// Perform rotation
	y->left = x;
	x->right = T2;

	// Update heights
	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;

	// Return new root
	return y;
}


