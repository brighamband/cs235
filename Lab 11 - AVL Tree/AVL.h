#ifndef AVL_H
#define AVL_H

#include "AVLInterface.h"
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

template<typename T>
class AVL : public AVLInterface<T> {
private:
	struct Node {
		T data;
		Node* left;
		Node* right;
		int height;
		Node(const T& d) {
			data = d;
			left = NULL;
			right = NULL;
			height = 1;		
		}
	};
	Node* root;
	size_t treeSize = 0;
public:
	AVL(void) { this->root = NULL; }
	~AVL(void) { clearTree(); }

	/** Return true if node added to AVL, else false */
	bool addNode(const T& data) { return addNodeRec(this->root, data); }

	bool addNodeRec(Node*& node, const T& data) {
		if (node == NULL) {
			node = new Node(data);
			updateHeight(node);
			return true;
		}
		if (data == node->data) return false;	// duplicate
		if (data < node->data) {
			bool success = addNodeRec(node->left, data);
			rebalance(node);
			return success;
		}
		if (data > node->data) {
			bool success = addNodeRec(node->right, data);
			rebalance(node);
			return success;
		}
		return false;
	}

	int updateHeight(Node*& node) {
		if (node == NULL) return 0;
		node->height = max(updateHeight(node->left), updateHeight(node->right)) + 1;
		return node->height;
	}

	void rebalance(Node*& node) {
		if (node == NULL) return;
		// check for balance
		int leftChild = node->left ? node->left->height : 0;
		int rightChild = node->right ? node->right->height : 0;

		switch (rightChild - leftChild) {		// balance factor
		case -2: {
			int leftLeftChild = node->left->left ? node->left->left->height : 0;		// ': 0' means that if there's no child, make variable equal to 0
			int leftRightChild = node->left->right ? node->left->right->height : 0;
			if ((leftRightChild - leftLeftChild) > 0) rotateLeft(node->left);		// rotate left around child (if left-right heavy)
			rotateRight(node);		// rotate right around parent (left-left or left-right heavy)
			break;
		}
		case +2: {
			int rightLeftChild = node->right->left ? node->right->left->height : 0;
			int rightRightChild = node->right->right ? node->right->right->height : 0;
			if ((rightRightChild - rightLeftChild) < 0) rotateRight(node->right);		// rotate right around child (if right-left heavy)
			rotateLeft(node);		// rotate left around parent (right-right or right-left heavy)
			break;
		}
		default: break;
		}
		node->height = updateHeight(node);	
	}

	void rotateLeft(Node*& node) {
		Node* temp = node->right;
		node->right = temp->left;
		temp->left = node;
		node = temp;
	}

	void rotateRight(Node*& node) {
		Node* temp = node->left;
		node->left = temp->right;
		temp->right = node;
		node = temp;
	}

	/** Return true if node removed from AVL, else false */
	bool removeNode(const T& data) { return removeNodeRec(this->root, data); }

	bool removeNodeRec(Node*& node, const T& data) {
		if (node == NULL) return false;
		if (data < node->data) {
			bool success = removeNodeRec(node->left, data);
			updateHeight(node);
			rebalance(node);
			return success;
		}
		if (data > node->data) {
			bool success = removeNodeRec(node->right, data);
			updateHeight(node);
			rebalance(node);
			return success;
		}
		if (node->left == NULL && node->right == NULL) {	// no children
			delete node;
			node = NULL;
			updateHeight(node);
			rebalance(node);
			return true;
		}
		if (node->left == NULL || node->right == NULL) {	// one child
			Node* temp;
			temp = node->left;
			if (node->left == NULL) temp = node->right;
			delete node;
			node = temp;
			updateHeight(node);
			rebalance(node);
			return true;
		}
		Node* temp = node->left;
		Node* parent = node;
		while (temp->right != NULL) {	// two children
			parent = temp;
			temp = temp->right;
		}
		if (node->data != parent->data) parent->right = temp->left;
		else parent->left = temp->left;
		node->data = temp->data;
		removeNodeRec(node->left, data);
		delete temp;
		temp = NULL;
		updateHeight(node);
		rebalance(node);
		return true;
	}

	/** Return true if AVL cleared of all nodes, else false */
	bool clearTree() { return clearTreeRec(root); }

	bool clearTreeRec(Node*& node) {
		if (node == NULL) return true;
		if (node->left != NULL) clearTreeRec(node->left);
		if (node->right != NULL) clearTreeRec(node->right);
		delete node;
		node = NULL;
		return true;
	}

	int sizeTree() { return sizeTreeRec(root); }

	int sizeTreeRec(Node* root) {
		if (root == NULL) return 0;
		else return (sizeTreeRec(root->left) + sizeTreeRec(root->right) + 1);
	}

	bool find(T data) { return findRec(root, data); }

	bool findRec(Node* node, T data) {
		if (node == NULL) return false;
		if (node->data == data) return true;
		if (data < node->data) return findRec(node->left, data);
		if (data > node->data) return findRec(node->right, data);
		return false;
	}

	bool outLevel(Node* root, int level, stringstream& out) const {
		if (root == NULL) return false;
		if (level == 1) {
			out << " " << root->data;
			if ((root->left != NULL) || (root->right != NULL)) return true;
			return false;
		}
		if ((level == 2) && !root->left && root->right) out << " _";
		bool left = outLevel(root->left, level - 1, out);
		bool right = outLevel(root->right, level - 1, out);
		if ((level == 2) && root->left && !root->right) out << " _";
		return left || right;
	}

	/** Return a level order traversal of a AVL as a string */
	string toString() const {
		stringstream out;
		if (root == NULL) out << " empty";
		else {
			int level = 0;
			do {
				out << endl << "  " << ++level << ":";
			} while (outLevel(root, level, out));
		}
		return out.str();
	}
};
#endif	// AVL_H