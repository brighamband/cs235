#include "AVLInterface.h"
#include "AVL.h"

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

    AVL<int> intTree;
    AVL<string> stringTree;
    bool isIntTree = true;

    // process input strings
    for (string line; getline(in, line);) {
        string command = "";
        string commandData = "";
        istringstream iss(line);
        iss >> command;
        iss >> commandData;
        out << line;

        // INT
        if (command == "INT") {
            isIntTree = true;
            out << " true";
        }
        // STRING
        if (command == "STRING") {
            isIntTree = false;
            out << " true";
        }
        // add
        if (command == "add") {
            if (isIntTree) {
                if (intTree.addNode(stoi(commandData))) out << " true";
                else out << " false";
            }
            else {
                if (stringTree.addNode(commandData)) out << " true";
                else out << " false";
            }
        }
        // remove
        if (command == "remove") {
            if (isIntTree) {
                if (intTree.removeNode(stoi(commandData))) out << " true";
                else out << " false";
            }
            else {
                if (stringTree.removeNode(commandData)) out << " true";
                else out << " false";
            }
        }
        // clear
        if (command == "clear") {
            if (isIntTree) {
                if (intTree.clearTree()) out << " true";
                else out << " false";
            }
            else {
                if (stringTree.clearTree()) out << " true";
                else out << " false";
            }
        }
        // size
        if (command == "size") {
            if (isIntTree) out << " " << intTree.sizeTree();
            else out << " " << stringTree.sizeTree();
        }
        // print
        if (command == "print") {
            if (isIntTree) out << ":" << intTree.toString();
            else out << ":" << stringTree.toString();
        }
        // find
        if (command == "find") {
            if (isIntTree) {
                if (intTree.find(stoi(commandData))) out << " found";
                else out << " not found";
            }
            else {
                if (stringTree.find(commandData)) out << " found";
                else out << " not found";
            }
        }
        out << endl;
    }

    return 0;
}

