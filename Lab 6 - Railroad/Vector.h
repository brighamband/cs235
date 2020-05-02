#ifndef VECTOR_H
#define VECTOR_H

#include "Deque.h"

#include <string>
using namespace std;

template<typename T>
class Vector {
private:
	Deque<T> container_;
public:
	Vector() {}
	~Vector() {}
	void push_back(const T& value) { container_.push_back(value); }
	void pop_back() { container_.pop_back(); }
	T& back() { return container_.back(); }
	size_t size() { return container_.size(); }
	T& at(size_t index) { return container_.at(index); }
	string toString() const { return container_.toString(); }
};
#endif // VECTOR_H