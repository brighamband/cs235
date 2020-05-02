#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

string assignGrade(double score, double average)
{
    if (score <= (average - 15)) return "E";
    if (score >= (average + 15)) return "A";

    if (score < (average - 5)) return "D";
    if (score > (average + 5)) return "B";
    return "C";
}

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

    int numNames = 0;
    int numScores = 0;


                /*****  SETUP   *****/

    // read in how many students and exams from first line of file
    in >> numNames >> numScores;

    // create dynamic 1D names array
    string* namesArray = new string[numNames];

    // create dynamic 2D array for scores
    int** scoresArray = new int* [numNames];
    for (int i = 0; i < numNames; i++) {
        scoresArray[i] = new int[numScores];
    }

    // get input for names and scores, then add them to arrays
    string tempFirstName = "";
    string tempLastName = "";
    string tempFullName = "";

    for (int i = 0; i < numNames; i++) {
        // get input for names, add to names array
        in >> tempFirstName >> tempLastName;
        tempFullName = tempFirstName + " " + tempLastName;
        namesArray[i] = tempFullName;

        // get input for scores, add to scores array
        for (int j = 0; j < numScores; j++) {
            in >> scoresArray[i][j];
        }
    }


                /*****  PART 1   *****/

    // output student scores
    out << "Student Scores: " << endl;
    for (int i = 0; i < numNames; i++) {
        // output names
        out << setw(20) << namesArray[i];

        // output scores
        for (int j = 0; j < numScores; j++) {
            out << setw(6) << scoresArray[i][j];
        }
        out << endl;
    }


                /*****  PART 2   *****/

    // calculate and output exam averages
    double* examAvg = new double[numScores];

    out << "Exam Averages: " << endl;
    for (int i = 0; i < numScores; i++) {
        double examTotal = 0.0;

        for (int j = 0; j < numNames; j++) {
            examTotal += scoresArray[j][i];            // before getting avg, total up all scores for each exam
        }
        examAvg[i] = examTotal / numNames;           // take average of exam total
        out << setw(9) << "Exam " << i + 1 << " Average = " << fixed << setprecision(1) << setw(6) << examAvg[i] << endl;
    }


                /*****  PART 3   *****/

    // output student exam grades
    int diffLetterGrades = 5;

    out << "Student Exam Grades: " << endl;
    for (int i = 0; i < numNames; i++) {
        // output names
        out << setw(20) << namesArray[i];

        // output scores
        for (int j = 0; j < numScores; j++) {
            out << setw(6) << scoresArray[i][j];

            // calculate what grade to give
            //out << " debug: " << scoresArray[i][j] << "--" << examAvg[j] << endl;
            out << "(" << assignGrade(scoresArray[i][j], examAvg[j]) << ")";         // call assign grade function
        }
        out << endl;
    }


                /*****  PART 4   *****/

    // output exam grades (first declare)
    int** letterGrades = new int* [numScores];
    for (int i = 0; i < numScores; i++) {
        letterGrades[i] = new int[diffLetterGrades];
    }

    // initialize exam grades
    for (int i = 0; i < numScores; i++) {
        for (int j = 0; j < diffLetterGrades; j++) {
            letterGrades[i][j] = 0;
        }
    }

    // calculate exam grades
    for (int i = 0; i < numScores; i++) {
        for (int j = 0; j < numNames; j++) {
            if (assignGrade(scoresArray[j][i], examAvg[i]) == "A") {
                letterGrades[i][0] += 1;
            }
            if (assignGrade(scoresArray[j][i], examAvg[i]) == "B") {
                letterGrades[i][1] += 1;
            }
            if (assignGrade(scoresArray[j][i], examAvg[i]) == "C") {
                letterGrades[i][2] += 1;
            }
            if (assignGrade(scoresArray[j][i], examAvg[i]) == "D") {
                letterGrades[i][3] += 1;
            }
            if (assignGrade(scoresArray[j][i], examAvg[i]) == "E") {
                letterGrades[i][4] += 1;
            }
        }
    }

    // output exam grades
    char Letters[5] = { 'A', 'B', 'C', 'D', 'E' };

    out << "Exam Grades: " << endl;
    for (int i = 0; i < numScores; i++) {
        out << setw(9) << "Exam " << i + 1;

        for (int j = 0; j < diffLetterGrades; j++) {
            out << setw(6) << letterGrades[i][j];
            out << "(" << Letters[j] << ")";
        }
        out << endl;
    }


                /*****  PART 5   *****/

    // calculations for student final grades and class avg
    double* studAvg = new double[numNames];
    double classAvg = 0.0;

    for (int i = 0; i < numNames; i++) {
        double studTotal = 0.0;

        // calculate student final avg and class avg
        for (int j = 0; j < numScores; j++) {
            studTotal += scoresArray[i][j];         // before getting avg, total up all student scores
        }
        studAvg[i] = studTotal / numScores;         // take avg of student total
        classAvg += studAvg[i];         // total up student total
    }
    classAvg = classAvg / numNames;         // find class avg by dividing total by # of students


    // output student final grades
    out << "Student Final Grades: " << endl;
    for (int i = 0; i < numNames; i++) {
        // output names
        out << setw(20) << namesArray[i];

        out << setw(6) << studAvg[i] << "(" << assignGrade(studAvg[i], classAvg) << ")" << endl;
    }
    out << "Class Average Score = " << classAvg << endl;

    // deleting items in arrays (avoid memory leak)
    delete[] namesArray;
    delete[] examAvg;
    delete[] studAvg;

    for (int i = 0; i < numNames; i++) {
        delete[] scoresArray[i];
    }
    delete[] scoresArray;

    for (int i = 0; i < numScores; i++) {
        delete[] letterGrades[i];
    }
    delete[] letterGrades;

    return 0;
}