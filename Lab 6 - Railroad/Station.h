#ifndef STATION_H
#define STATION_H

#include "Vector.h"
#include "Queue.h"
#include "Stack.h"

#include <string>
using namespace std;

template<typename T>
class Station {
private:
	Vector<T> train_;
	Stack<T> stack_;
	Queue<T> queue_;
	T turnTableCar;
	bool empty = true;
public:
	Station() {}
	~Station() {}
	string addCar(const T& newCar) {
		if (empty == true) {
			turnTableCar = newCar;		// add new car to turntable
			empty = false;		// fill the turntable
			return "OK";
		}
		else {
			return "Turntable occupied!";
		}
	}
	string removeCar() {
		if (empty == false) {
			train_.push_back(turnTableCar);		// push car onto train vector
			empty = true;		// empty the turntable
			return "OK";
		}
		else {
			return "Turntable empty!";
		}
	}
	string topCar() {
		if (empty == false) {
			return to_string(turnTableCar);
		}
		else {
			return "Turntable empty!";
		}
	}
	string addStack() {
		if (empty == false) {
			empty = true;		// empty the turntable
			stack_.push(turnTableCar);		// push car onto stack roundhouse
			return "OK";
		}
		else {
			return "Turntable empty!";
		}
	}
	string removeStack() {
		if (empty == true) {
			if (stack_.size() != 0) {
				turnTableCar = stack_.top();		// add removed car from stack to turntable
				stack_.pop();
				empty = false;		// fill the turntable
				return "OK";
			}
			else {
				return "Stack empty!";
			}
		}
		else {
			return "Turntable occupied!";
		}
	}
	string topStack() {
		if (stack_.size() != 0) {
			stringstream ss;
			ss << stack_.top();
			return ss.str();
		}
		else {
			return "Stack empty!";
		}
	}
	string sizeStack() { 
		stringstream ss;
		ss << stack_.size();
		return ss.str();
	}
	string addQueue() {
		if (empty == false) {
			empty = true;		// empty the turntable
			queue_.push(turnTableCar);		// push car onto queue roundhouse
			return "OK";
		}
		else {
			return "Turntable empty!";
		}
	}
	string removeQueue() {
		if (empty == true) {
			if (queue_.size() != 0) {
				turnTableCar = queue_.top();		// add removed car from queue to turntable
				queue_.pop();
				empty = false;		// fill the turntable
				return "OK";
			}
			else {
				return "Queue empty!";
			}
		}
		else {
			return "Turntable occupied!";
		}
	}
	string topQueue() {
		if (queue_.size() != 0) {
			stringstream ss;
			ss << queue_.top();
			return ss.str();
		}
		else {
			return "Queue empty!";
		}
	}
	string sizeQueue() { 
		stringstream ss;
		ss << queue_.size();
		return ss.str();
	}
	string find(T searchCar) {
		// check turntable
		if (turnTableCar == searchCar) {
			return "Turntable";
		}
		// check queue
		for (unsigned int i = 0; i < queue_.size(); ++i) {
			if (queue_.at(i) == searchCar) {
				stringstream ss;
				ss << "Queue[" << i << "]";
				return ss.str();
			}
		}
		// check stack
		for (unsigned int i = 0; i < stack_.size(); ++i) {
			if (stack_.at(i) == searchCar) {
				stringstream ss;
				ss << "Stack[" << i << "]";
				return ss.str();
			}
		}
		// check vector
		for (unsigned int i = 0; i < train_.size(); ++i) {
			if (train_.at(i) == searchCar) {
				stringstream ss;
				ss << "Train[" << i << "]";
				return ss.str();
			}
		}
		return "Not Found!";		// if not found in turntable, vector, queue, or stack
	}
	string toString() const { return train_.toString(); }
};
#endif // STATION_H