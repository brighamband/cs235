#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <sstream>
#include <string>
#include "LinkedListInterface.h"
#include <iostream>
using namespace std;

/** Linked List */
template<typename T>
class LinkedList : public LinkedListInterface<T> {
private:
	struct Node {
		T data;
		Node* next;
		Node(const T& d) : data(d), next(NULL) {}
		Node(const T& d, Node* n) : data(d), next(n) {}
	};
	Node* head = NULL;

public:
	LinkedList() { this->head = NULL; }
	~LinkedList() { clear(); }

	/** Insert Node at beginning of list */
	void push_front(const T& value) { 
		if (head == NULL) {
			Node* newHead = new Node(value);
			head = newHead;
		}
		else {
			Node* newHead = new Node(value, head);
			head = newHead;
		}
	}

	/** Remove Node at beginning of linked list */
	void pop_front(void) {
		if (head == NULL) {		// check if linked list is empty
			return;
		}
		Node* tempPtr = head;
		head = head->next;			// point head to the next node so you can delete the previous head node
		delete tempPtr;
	}

	/** Return reference to value of Node at beginning of linked list */
	T& front(void) {
		return head->data;
	}

	/** Return true if linked list size == 0 */
	bool empty(void) const {
		return head == NULL;
	}

	/** Remove all Nodes with value from linked list */
	void remove(const T& value) {
		Node* tempNode = head;
		Node* tempNode2;
		while (tempNode->data == value) {
			tempNode = tempNode->next;
			pop_front();
			if (tempNode == NULL) break; }
		while (tempNode != NULL) {
			if (tempNode->next != NULL) {
				if (tempNode->next->data == value) {
					tempNode2 = tempNode->next->next;
					delete tempNode->next;
					tempNode->next = tempNode2;
				}
			}
			else break;
			tempNode = tempNode->next;
		}
	}

	/** Remove all Nodes from linked list */
	void clear(void) {
		while (head != NULL) {
			Node* current = head;
			head = head->next;
			delete current;
		}
	}
	
	/** Reverse Nodes in linked list */
	void reverse(void) {
		Node* prevPtr = NULL;
		Node* currPtr = head;
		Node* nextPtr = NULL;

		while (currPtr != NULL) {
			nextPtr = currPtr->next;
			currPtr->next = prevPtr;
			prevPtr = currPtr;
			currPtr = nextPtr;
		}
		head = prevPtr;
	}

	/** Return the number of nodes in the linked list */
	size_t size(void) const {
		size_t counter = 0;
		Node* tempPtr = head;

		while (tempPtr != NULL) {
			counter++;
			tempPtr = tempPtr->next;
		}
		
		return counter;
	}

	/** Return contents of Linked List as a string */
	string toString(void) const {
		stringstream out;
		Node* tempPtr = head;

		while (tempPtr != NULL) {
			out << " " << tempPtr->data;
			tempPtr = tempPtr->next;
		}
		return out.str();
	}

	friend ostream& operator<< (ostream& os, LinkedList<T>& linkedList) {
		for (Iterator iter = linkedList.begin(); iter != linkedList.end(); ++iter) {
			os << endl << " [" << *iter << "]";
		}
		return os;
	}

	class Iterator {
	private:
		Node* iNode;
	public:
		Iterator(Node* head) : iNode(head) { }
		~Iterator() {}

		// overload comparison operator
		bool operator!=(const Iterator& rhs) const { return iNode != rhs.iNode; }

		// overload pre-increment operator
		Iterator& operator++() { iNode = iNode ? iNode->next : NULL; return *this; }

		// overload dereference operator
		T& operator*() const { return iNode->data; }

		friend LinkedList;		// adds access to LinkedList data members
	};

	/** Return iterator pointing to the first value in linked list */
	Iterator begin(void) { return LinkedList<T>::Iterator(head); }

	/** Return iterator pointing to something not in linked list */
	Iterator end(void) { return LinkedList<T>::Iterator(NULL); }

	/** Return iterator pointing found value in linked list */
	Iterator find(Iterator first, Iterator last, const T& value) {
		for (Iterator iter = first; iter != last; ++iter) {
			if (*iter == value) {
				return iter;
			}
		}
		return last;
	}

	/** Return iterator pointing to inserted value in linked list */
	Iterator insert(Iterator position, const T& value) {
		// CASE 1 - if at beginning, call push front
		if (head == position.iNode) {
			push_front(value);
			return begin();
		}

		// CASE 2 - if not at beginning
		Node* tempPtr = head;
		while (tempPtr->next != position.iNode) {//getNode()) {
			tempPtr = tempPtr->next;
		}
		
		return insert_after(Iterator(tempPtr), value);
	}

	/** Return iterator pointing to inserted value in linked list */
	Iterator insert_after(Iterator position, const T& value) {
		Node* newNode = new Node(value, position.iNode->next);
		position.iNode->next = newNode;
		return ++position;
	}

	/** Return iterator pointing to next item after deleted node linked list */
	Iterator erase(Iterator position) {
		Node* tempPtr = head;
		Node* posSaver = position.iNode;

		// CASE 1 - if at beginning, call pop front
		if (head == position.iNode) {
			pop_front();
			return begin();
		}

		// CASE 2 - if not at beginning
		while (tempPtr->next != posSaver) {
			tempPtr = tempPtr->next;

		}
		tempPtr->next = tempPtr->next->next;
		
		++position;
		delete posSaver;
		return position;
	}

	/** Replace first found old_value(s) with new_value */
	void replace(Iterator first, Iterator last, const T& old_value, const T& new_value) {
		LinkedList<string>::Iterator iter = first;
		while (iter != last) {
			if (*iter == old_value) {
				*iter = new_value; 
				++iter;
			} else {
				++iter; 
			} 
		}
	}
};

#endif 