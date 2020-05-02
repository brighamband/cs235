#ifndef STUDENT_H
#define STUDENT_H

using namespace std;

class Student {
public:
	Student() {
		studID = "Unassigned Student ID";
	}
	Student(string studID) {
		this->studID = studID;
	}
	string getStudID() const {
		return studID;
	}
private:
	string studID;
};

#endif