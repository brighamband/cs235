#ifndef CSG_H
#define CSG_H

#include <sstream>
#include <string>
#include "Student.h"
#include "Course.h"
using namespace std;

class Csg : public Student, public Course {
public:
	Csg() {
		grade = "Unspecified Grade";
	}
	Csg(string course, string studID, string grade) : Student(studID), Course(course) {
		this->grade = grade;
	}
	string getGrade() const {
		return grade;
	}
	string toString() const {
		stringstream out;
		out << "csg(" << getCourse();
		out << "," << getStudID();
		out << "," << getGrade() << ")";
		return out.str();
	}
	friend ostream& operator<< (ostream& os, const Csg& csg) {
		os << csg.toString();
		return os;
	}
private:
	string grade;
};

#endif