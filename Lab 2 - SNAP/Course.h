#ifndef COURSE_H
#define COURSE_H

#include <string>
using namespace std;

class Course {
public:
	Course() {
		course = "Unspecified Course";
	}
	Course(string course) {
		this->course = course;
	}
	string getCourse() const {
		return course;
	}
private:
	string course;
};

#endif