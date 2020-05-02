#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include "Student.h"
#include "Course.h"
#include "Snap.h"
#include "Csg.h"
#include "Cdh.h"
#include "Cr.h"
using namespace std;

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

int main(int argc, char* argv[]) {
    VS_MEM_CHECK            // enable memory leak check

    // set up input and output files and read them
    if (argc < 3) {
        cerr << "Please provide name of input and output files";
        return 1;
    }
    cout << "Input file: " << argv[1] << endl;
    ifstream in(argv[1]);
    if (!in) {
        cerr << "Unable to open " << argv[1] << " for input";
        return 2;
    }
    cout << "Output file: " << argv[2] << endl;
    ofstream out(argv[2]);
    if (!out) {
        in.close();
        cerr << "Unable to open " << argv[2] << " for output";
        return 3;
    }
    
    vector<Snap> snaps;
    vector<Csg> csgs;
    vector<Cdh> cdhs;
    vector<Cr> crs;


    // input strings + fill each of the 4 vectors
    out << "Input Strings:" << endl;
    for (string line; getline(in, line);) {         // read until EOF
        try {
            if ("snap(" == line.substr(0, 5)) {           // find snaps
                out << line << endl;            // output original input string
                string studID = line.substr(5, line.find(',') - 5);
                line = line.substr(line.find(',') + 1);
                string name = line.substr(0, line.find(','));
                line = line.substr(line.find(',') + 1);
                string address = line.substr(0, line.find(','));
                line = line.substr(line.find(',') + 1);
                string phone = line.substr(0, line.find(')'));
                snaps.push_back(Snap(studID, name, address, phone));
            }
            else if ("csg(" == line.substr(0, 4)) {           // find csgs
                out << line << endl;            // output original input string
                string course = line.substr(4, line.find(',') - 4);
                line = line.substr(line.find(',') + 1);
                string studID = line.substr(0, line.find(','));
                line = line.substr(line.find(',') + 1);
                string grade = line.substr(0, line.find(')'));
                csgs.push_back(Csg(course, studID, grade));
            }
            else if ("cdh(" == line.substr(0, 4)) {           // find cdhs
                out << line << endl;            // output original input string
                string course = line.substr(4, line.find(',') - 4);
                line = line.substr(line.find(',') + 1);
                string day = line.substr(0, line.find(','));
                line = line.substr(line.find(',') + 1);
                string hour = line.substr(0, line.find(')'));
                cdhs.push_back(Cdh(course, day, hour));
            }
            else if ("cr(" == line.substr(0, 3)) {           // find crs
                out << line << endl;            // output original input string
                string course = line.substr(3, line.find(',') - 3);
                line = line.substr(line.find(',') + 1);
                string room = line.substr(0, line.find(')'));
                crs.push_back(Cr(course, room));
            }
            else {
                throw (line);
            }
        }
        catch (string line) {
            out << "**Error: " << line << endl;
        }
    }
    out << endl;

    // vectors
    out << "Vectors:" << fixed << setprecision(4) << endl;
    for (unsigned int i = 0; i < snaps.size(); i++) {
        out << snaps.at(i) << endl;
    }
    for (unsigned int i = 0; i < csgs.size(); i++) {
        out << csgs.at(i) << endl;
    }
    for (unsigned int i = 0; i < cdhs.size(); i++) {
        out << cdhs.at(i) << endl;
    }
    for (unsigned int i = 0; i < crs.size(); i++) {
        out << crs.at(i) << endl;
    }
    out << endl;

    // course grades
    out << "Course Grades:" << endl;
    for (unsigned int i = 0; i < csgs.size(); i++) {
        out << csgs.at(i).getCourse() << ",";
        for (unsigned int j = 0; j < snaps.size(); j++) {           // output name instead of studID
            if (csgs.at(i).getStudID() == snaps.at(j).getStudID()) {
                out << snaps.at(j).getName();
            }
        }
       out << "," << csgs.at(i).getGrade() << endl;
    }
    out << endl;

    // student schedules
    out << "Student Schedules:" << endl;
    for (unsigned int i = 0; i < snaps.size(); i++) {
        out << snaps.at(i).getName() << ", " << snaps.at(i).getStudID() << ", " << snaps.at(i).getAddress() << ", " <<  snaps.at(i).getPhone() << endl;         // output snap
        for (unsigned int j = 0; j < csgs.size(); j++) {
            if (snaps.at(i).getStudID() == csgs.at(j).getStudID()) {
                out << fixed << setw(7) << csgs.at(j).getCourse() << " ";

                for (unsigned int k = 0; k < cdhs.size(); k++) {
                    if (cdhs.at(k).getCourse() == csgs.at(j).getCourse()) {
                        out << cdhs.at(k).getDay();         // output days of week of each course
                    }
                }

                for (unsigned int k = 0; k < cdhs.size(); k++) {
                    if (cdhs.at(k).getCourse() == csgs.at(j).getCourse()) {
                        out << " " << cdhs.at(k).getHour();         // output hour for each course
                        break;
                    }
                }

                for (unsigned int k = 0; k < crs.size(); k++) {
                    if (csgs.at(j).getCourse() == crs.at(k).getCourse()) {
                        out << ", " << crs.at(k).getRoom();         // output room of each course
                    }
                }
                out << endl;
            }
        }
        out << endl;
    }

    return 0;
}