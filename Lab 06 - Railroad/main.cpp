#include "Station.h"

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

    Station<unsigned int> station;

    for (string line; getline(in, line);) {
        string command = "";
        unsigned int commandData;
        istringstream iss(line);
        iss >> command >> commandData;
        out << command << " ";

        // add
        if (command.substr(0, 4) == "Add:") {
            command = command.substr(4);
            if (command == "station") {
                out << commandData << " " << station.addCar(commandData) << endl;
            }
            else if (command == "queue") {
                out << station.addQueue() << endl;
            }
            else if (command == "stack") {
                out << station.addStack() << endl;
            }
        }
        // remove
        if (command.substr(0, 7) == "Remove:") {
            command = command.substr(7);
            if (command == "station") {
                out << station.removeCar() << endl;
            }
            else if (command == "queue") {
                out << station.removeQueue() << endl;
            }
            else if (command == "stack") {
                out << station.removeStack() << endl;
            }
        }
        // top
        if (command.substr(0, 4) == "Top:") {
            command = command.substr(4);
            if (command == "station") {
                out << station.topCar() << endl;
            }
            else if (command == "queue") {
                out << station.topQueue() << endl;
            }
            else if (command == "stack") {
                out << station.topStack() << endl;
            }
        }
        // size
        if (command.substr(0, 5) == "Size:") {
            command = command.substr(5);
            if (command == "queue") {
                out << station.sizeQueue() << endl;
            }
            else if (command == "stack") {
                out << station.sizeStack() << endl;
            }
        }
        // find (extra credit)
        if (command == "Find:") {
            out << commandData << " " << station.find(commandData) << endl;
        }
        // train
        if (command == "Train:") {
            out << station.toString() << endl;
        }
    }

    return 0;
}
