#ifndef DEQUE_H
#define DEQUE_H

#include "DequeInterface.h"
#include<sstream>
#include <string>
using namespace std;

template<typename T>
class Deque : public DequeInterface<T> {
private:
	size_t capacity;
	size_t num_items;
	size_t front_index;
	size_t rear_index;
	T* the_data;

	void reallocate() {
		size_t new_capacity = 2 * capacity;
		T* new_data = new T[new_capacity];
		size_t old = front_index;
		for (size_t i = 0; i < num_items; ++i) {
			new_data[i] = the_data[old];
			old = (old + 1) % capacity;
		}
		front_index = 0;
		rear_index = num_items - 1;
		capacity = new_capacity;

		delete[] the_data;
		the_data = new_data;
	}

public:
	Deque(void) :
		capacity(DEFAULT_CAPACITY),
		num_items(0),
		front_index(0),
		rear_index(DEFAULT_CAPACITY - 1),
		the_data(new T[DEFAULT_CAPACITY]) {}
	~Deque(void) { delete[] the_data; }

	/** Insert item at front of deque */
	void push_front(const T& value) {
		if (num_items == capacity) {
			reallocate();
		}
		num_items++;
		front_index = (front_index - 1) % capacity;
		the_data[front_index] = value;
	}

	/** Insert item at rear of deque */
	void push_back(const T& value) {
		if (num_items == capacity) {
			reallocate();
		}
		num_items++;
		rear_index = (rear_index + 1) % capacity;
		the_data[rear_index] = value;
	}

	/** Remove the front item of the deque */
	void pop_front(void) {
		num_items--;
		front_index = (front_index + 1) % capacity;
	}

	/** Remove the rear item of the deque */
	void pop_back(void) {
		num_items--;
		rear_index = (rear_index - 1) % capacity;
	}

	/** Return the front item of the deque (Do not remove) */
	T& front(void) { return the_data[front_index];  }

	/** Return the rear item of the deque (Do not remove) */
	T& back(void) { return the_data[rear_index]; }

	/** Return the number of items in the deque */
	size_t size(void) const { return num_items; }

	/** Return true if deque is empty */
	bool empty(void) const {
		return size() == 0;
	}

	/** Return item in deque at index (0 based) */
	T& at(size_t index) { return the_data[(front_index + index) % capacity]; }

	/** Return item in deque stack at index (reverse of queue and vector) */
	T& atStack(size_t index) { return the_data[(rear_index - index) % capacity]; }

	/** Return the deque items */
	string toString(void) const {
		stringstream ss; 
		for (unsigned int i = 0; i < num_items; ++i) {
			ss << the_data[(i + front_index) % capacity] << " ";
		}
		return ss.str();
	}
};
#endif // DEQUE_H