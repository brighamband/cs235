#ifndef SNAP_H
#define SNAP_H

#include <sstream>
#include <string>
#include "Student.h"
using namespace std;

class Snap : public Student {
public:
	Snap() {
		name = "Unspecified Name";
		address = "Unspecified Address";
		phone = "Unspecified Phone";
	}
	Snap(string studID, string name, string address, string phone) : Student(studID) {
		this->name = name;
		this->address = address;
		this->phone = phone;
	}
	string getName() const {
		return name;
	}
	string getAddress() const {
		return address;
	}
	string getPhone() const {
		return phone;
	}
	string toString() const {
		stringstream out;
		out << "snap(" << getStudID();
		out << "," << this->name;
		out << "," << this->address;
		out << "," << this->phone << ")";
		return out.str();
	}
	friend ostream& operator<< (ostream& os, const Snap& snap) {
		os << snap.toString();
		return os;
	}
private:
	string name;
	string address;
	string phone;
};

#endif