#ifndef CR_H
#define CR_H

#include <sstream>
#include <string>
#include "Course.h"
using namespace std;

class Cr : public Course {
public:
	Cr() {
		room = "Unspecified Room";
	}
	Cr(string course, string room) : Course(course) {
		this->room = room;
	}
	string getRoom() const {
		return room;
	}
	string toString() const {
		stringstream out;
		out << "cr(" << getCourse();
		out << "," << this->room << ")";
		return out.str();
	}
	friend ostream& operator<< (ostream& os, const Cr& cr) {
		os << cr.toString();
		return os;
	}
private:
	string room;
};

#endif