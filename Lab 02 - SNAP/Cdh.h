#ifndef CDH_H
#define CDH_H

#include <sstream>
#include <string>
#include "Course.h"
using namespace std;

class Cdh : public Course {
public:
	Cdh() {
		day = "Unspecified Day";
		hour = "Unspecified Hour";
	}
	Cdh(string course, string day, string hour) : Course(course) {
		this->day = day;
		this->hour = hour;
	}
	string getDay() const {
		return day;
	}
	string getHour() const {
		return hour;
	}
	string toString() const {
		stringstream out;
		out << "cdh(" << getCourse();
		out << "," << this->day;
		out << "," << this->hour << ")";
		return out.str();
	}
	friend ostream& operator<< (ostream& os, const Cdh& cdh) {
		os << cdh.toString();
		return os;
	}
private:
	string day;
	string hour;
};

#endif