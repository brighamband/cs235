#ifndef QUEUE_H
#define QUEUE_H

#include "Deque.h"

#include <string>
using namespace std;

template<typename T>
class Queue {
private:
	Deque<T> container_;
public:
	Queue() {}
	~Queue() {}
	void push(const T& value) { container_.push_back(value); }
	void pop() { container_.pop_front();  }
	T& top() { return container_.front();  }
	size_t size() { return container_.size(); }
	T& at(size_t index) { return container_.at(index); }
	string toString() const { return container_.toString(); }
};
#endif // QUEUE_H