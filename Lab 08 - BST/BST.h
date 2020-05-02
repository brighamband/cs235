#ifndef BST_H
#define BST_H

#include <sstream>
#include <string>
#include "BSTInterface.h"
#include <iostream>
using namespace std;

template<typename T>
class BST : public BSTInterface<T> {
private:
	struct Node {
		T data;
		Node* left;
		Node* right;
		Node(const T& d) : data(d), left(NULL), right(NULL) {}
	};
	Node* root;
	int treeSize = 0;
public:
	BST(void) { this->root = NULL; }
	~BST(void) { clearTree(); }

	bool addNode(const T& data) { return addNodeRec(this->root, data); }

	bool addNodeRec(Node*& node, const T& data) {
		if (node == NULL) {
			node = new Node(data);
			return true;
		}
		if (data == node->data) return false;	// duplicate
		if (data < node->data) return addNodeRec(node->left, data);
		if (data > node->data) return addNodeRec(node->right, data);
		return false;
	}

	bool removeNode(const T& data) { return removeNodeRec(this->root, data); }

	bool removeNodeRec(Node*& node, const T& data) {
		if (node == NULL) return false;
		if (data < node->data) return removeNodeRec(node->left, data);
		if (data > node->data) return removeNodeRec(node->right, data);
		if (node->left == NULL && node->right == NULL) {	// if node has no children
			delete node;
			node = NULL;
			return true;
		}
		if (node->left == NULL || node->right == NULL) {	// one child
			Node* temp;
			temp = node->left;
			if (node->left == NULL) temp = node->right;
			delete node;
			node = temp;
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
		delete temp;
		return true;
	}

	bool clearTree() { return clearTreeRec(root); }

	bool clearTreeRec(Node*& node) {
		if (node == NULL) return true;
		if (node->left != NULL) clearTreeRec(node->left);
		if (node->right != NULL) clearTreeRec(node->right);
		delete node;
		node = NULL;
		return true;
	}

	int size() { return sizeRec(root); }

	int sizeRec(Node* root) {
		if (root == NULL) return 0;
		else return (sizeRec(root->left) + sizeRec(root->right) + 1);
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

	friend ostream& operator<< (ostream& os, BST<T>& bst) {
		for (BST iter = bst.begin(); iter != bst.end(); ++iter) {
			os << endl << " [" << *iter << "]";
		}
		return os;
	}
};
#endif	// BST_H