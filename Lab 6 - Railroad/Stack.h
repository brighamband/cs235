#ifndef STACK_H
#define STACK_H

#include "Deque.h"

#include <string>
using namespace std;

template<typename T>
class Stack {
private:
	Deque<T> container_;
public:
	Stack() {}
	~Stack() {}
	void push(const T& value) { container_.push_front(value); } 
	void pop() { container_.pop_front(); }
	T& top() { return container_.front(); }
	size_t size() { return container_.size(); }
	T& at(size_t index) {	return container_.atStack(index); }
	string toString() const { return container_.toString();  }
};
#endif // STACK_H