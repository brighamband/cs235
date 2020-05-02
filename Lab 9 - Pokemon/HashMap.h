#ifndef HASH_MAP_H
#define HASH_MAP_H

#include "HashMapInterface.h"
#include <string>
#include <cmath>
using namespace std;

#define DEFAULT_MAP_HASH_TABLE_SIZE	31
#define HASH_CONSTANT				3
#define LOAD_THRESHOLD				75

template <typename K, typename V>
class HashMap : public HashMapInterface<K, V> {
private:
	size_t capacity;
	pair<K, V>* myPairs;
	size_t mapSize;
public:
	HashMap<K, V>() {
		capacity = DEFAULT_MAP_HASH_TABLE_SIZE;
		myPairs = new pair<K, V>[capacity];
		mapSize = 0;
	}
	~HashMap() { clear(); }

	/** Read/write index access operator.
	If the key is not found, an entry is made for it.
	@return: Read and write access to the value mapped to the provided key. */
	V& operator[](const K& key) { 
		// hashing
		//size_t hashIndex = 0;
		long long int hashIndex = 0;
		for (unsigned int i = 0; i < key.size(); ++i) {
			hashIndex += key[i] * pow(HASH_CONSTANT, key.size() - (i + 1));
		}
		hashIndex = hashIndex % capacity;
		// quadratic probing
		size_t tempIndex = hashIndex;
		size_t counter = 1;	 // # of probes in while loop
		while (1) {
			if (myPairs[tempIndex].first != K()) {
				if (myPairs[tempIndex].first == key) break;
				tempIndex = (hashIndex + pow(counter++, 2));
				tempIndex = tempIndex % capacity;
				continue;
			}
			myPairs[tempIndex].first = key;		// insert
			mapSize++;
			break;
		}
		return myPairs[tempIndex].second;
	}

	/** @return: the number of elements that match the key in the Map. */
	size_t count(const K& key) {
		for (unsigned int i = 0; i < capacity; ++i) {
			if (myPairs[i].first == key) return 1;
		}
		return 0;
	}

	/** Removes all items from the Map. */
	void clear(void) {
		delete[] myPairs;
		//myPairs = NULL;
		mapSize = 0;
	}

	/** @return: number of Key-Value pairs stored in the Map. */
	size_t size(void) const { return mapSize; }

	/** @return: maximum number of Key-Value pairs that the Map can hold. */
	size_t max_size(void) const { return capacity; }

	/** @return: string representation of Key-Value pairs in Map. */
	string toString(void) const {
		stringstream out;
		for (size_t i = 0; i < capacity; ++i) {
			if (myPairs[i].first != K()) {
				out << endl << " " << "[" << i << ":";
				out << myPairs[i].first << "->";
				out << myPairs[i].second << "]";
			}
		}
		return out.str();
	}

	friend ostream& operator<< (ostream& os, HashMap<K, V>& hashmap) {
		os << hashmap.toString();
		return os;
	}
};
#endif // HASH_MAP_H