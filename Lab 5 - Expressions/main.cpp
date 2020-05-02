#include "ExpressionManager.h"
#include "ExpressionManagerInterface.h"

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


    ExpressionManager manager;

    for (string line; getline(in, line);) {
        try {
            string expCommand, expString;
            if (line.size() == 0) continue;
            istringstream iss(line);
            iss >> expCommand;
            
            if (expCommand == "Expression:") {
                getline(iss, expString);
                manager.setExpression(expString);
                out << endl << expCommand << " " << expString << endl;
            }
            if (expCommand == "Infix:") {
                out << expCommand << " ";
                out << manager.infix() << endl;
            }
            if (expCommand == "Postfix:") {
                out << expCommand << " " << manager.postfix() << endl;
            }
            if (expCommand == "Prefix:") {
                out << expCommand << " " << endl;
            }
            if (expCommand == "Value:") {
                out << expCommand << " " << manager.value() << endl;
            }
        }
        catch (int) {
            out << "Unbalanced" << endl;
        }
        catch (string) {
            out << "Missing Operand" << endl;
        }
        catch (char) {
            out << "Illegal Operator" << endl;
        }
        catch (double) {
            out << "Missing Operator" << endl;
        }
    }

    return 0;
}

