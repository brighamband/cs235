#include "LinkedList.h"
#include "LinkedListInterface.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
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


    LinkedList<string> linked_list;

    // process input strings
    for (string line; getline(in, line);) {
        try {
            string command, commandData;
            if (line.size() == 0) continue;
            istringstream iss(line);
            iss >> command;
            out << command;
            if (command == "Insert") {
                while (iss >> commandData) {
                    linked_list.push_front(commandData);
                    out << " " << commandData;
                }
                out << endl;
            }
            if (command == "Clear") {
                linked_list.clear();

                if (linked_list.size() == 0) {
                    out << " OK" << endl;
                }
            }
            if (command == "Empty") {
                if (linked_list.empty()) {
                    out << " true" << endl;
                }
                else {
                    out << " false" << endl;
                }
            }
            if (command == "First") {
                if (linked_list.empty()) {
                    throw(line);
                }
                else {
                    out << " " << linked_list.front() << endl;
                }
            }
            if (command == "PrintList") {
                if (linked_list.empty()) {
                    throw (line);
                }
                else {
                    out << linked_list.toString() << endl;
                }
            }
            if (command == "Remove") {
                iss >> commandData;
                out << " " << commandData;
                linked_list.remove(commandData);
                out << endl;
            }
            if (command == "Reverse") {
                if (linked_list.empty()) {
                    throw(line);
                }
                else {
                    linked_list.reverse();
                    out << " OK" << endl;
                }
            }
            if (command == "Size") {
                out << " " << linked_list.size();
                out << endl;
            }
            if (command == "Delete") {
                if (linked_list.empty()) {
                    throw(line);
                }
                else {
                    linked_list.pop_front();
                    out << " OK" << endl;
                }
            }
        }
        catch (string line) {
            out << " Empty!" << endl;
        }
    }

    return 0;
}

