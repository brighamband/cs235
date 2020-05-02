#include "QSInterface.h"
#include "QS.h"

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

    QS<int> qs;

    // process input strings
    for (string line; getline(in, line);) {
        string command = "";
        string arrayAsString = "";
        int intData = 0;
        istringstream iss(line);
        iss >> command;
        out << command << " ";

        // QuickSort
        if (command == "QuickSort") {
            iss >> intData;
            out << intData << " ";
            if (qs.createArray(intData)) out << "OK";
            else out << "Error";
        }
        // AddToArray
        if (command == "AddToArray") {
            // add first element and print
            iss >> intData;
            qs.addElement(intData);
            out << intData;
            // add remaining elements and print
            while (iss >> intData) {
                qs.addElement(intData);
                out << "," << intData;
            }
            out << " OK";
        }
        // Capacity
        if (command == "Capacity") {
            out << qs.capacity();
        }
        // Clear
        if (command == "Clear") {
            qs.clear();
            out << " OK";
        }
        // Size
        if (command == "Size") {
            out << qs.size();
        }
        // Sort
        if (command == "Sort") {
            int leftIndex, rightIndex = 0;
            iss >> leftIndex >> rightIndex;
            out << leftIndex << "," << rightIndex;
            if (qs.sort(leftIndex, rightIndex)) out << " OK";
            else out << " Error";
        }
        // SortAll
        if (command == "SortAll") {
            if (qs.sortAll()) out << " OK";
            else out << " Error";
        }
        // MedianOfThree
        if (command == "MedianOfThree") {
            int leftIndex, rightIndex = 0;
            iss >> leftIndex >> rightIndex;
            out << leftIndex << "," << rightIndex << " = " << qs.medianOfThree(leftIndex, rightIndex);
        }
        // Partition
        if (command == "Partition") {
            int leftIndex, rightIndex, pivotIndex = 0;
            iss >> leftIndex >> rightIndex >> pivotIndex;
            out << leftIndex << "," << rightIndex << "," << pivotIndex << " = " << qs.partition(leftIndex, rightIndex, pivotIndex);
        }
        // PrintArray
        if (command == "PrintArray") {
            if (qs.size() != 0) out << qs;
            else out << " Empty";
        }
        // Stats (BONUS)
        if (command == "Stats") {
            out << "Unknown"; // qs.getNumComparisons() << ", " << qs.getNumExchanges();
        }
        out << endl;
    }

    return 0;
}

