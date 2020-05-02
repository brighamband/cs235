#ifndef SET_H
#define SET_H

#include "SetInterface.h"
#include "BST.h"
#include <string>
#include <iostream>
using namespace std;

template<typename T>
class Set : public SetInterface<T> {
private:
	BST<T> bst_;
public:
	Set() {}
	~Set() {}

	/** Inserts item into the set, if the container doesn't
		already contain an element with an equivalent value.
		@return: pair.first = pointer to item
				 pair.second = true if successfully inserted, else false. */
				 //virtual Pair<T*, bool> insert(const T& item) = 0;
	bool insert(const T& item) { return bst_.addNode(item); }

	/** Removes all items from the set. */
	void clear() { bst_.clearTree(); }

	/** @return: the number of elements contained by the Set. */
	size_t size() const { return bst_.size(); }

	/** @return: return 1 if contains element equivalent to item, else 0. */
	size_t count(const T& item) { 
		if (bst_.find(item)) return 1;
		else return 0;
	}

	/** @return: string representation of items in Set. */
	string toString() const { return bst_.toString(); }

	friend ostream& operator<< (ostream& os, Set<T>& set) {
		os << set.toString();
		return os;
	}
};
#endif // SET_H