/**
 * Read Student Info
 * 
 * id,lname,fname,q1,q2,q3,q4,q5,q6,t1,t2,f
 * 
 * INFILE: "infile.txt"
 *      ID,LName,FName,Q1,Q2,Q3,Q4,Q5,Q6,T1,T2,Final.
 *      11111,lu,youmin,10,9,8,10,8,9,95,99,80
 *      12345,kapp,sam,8,8,7,9,10,1,95,90,75
 *      43234,tommy,kovaschetz,3,4,5,2,3,4,67,78,83
 * 
 * OUTFILE: "outfile.txt"
 * ID       LName      FName      Q1   Q2   Q3   Q4   Q5   Q6   T1   T2   Final      Total     Grade
 * 11111    lu         youmin     10    9    8   10    8    9   95   99      80         80     C
 * 12345    kapp       sam         8    8    7    9   10    1   95   90      75         73     C
 * 43234    tommy      kovaschetz  3    4    5    2    3    4   67   78      83         60     F
 * 
 * The maximum of all quizzes: 10
 * The average of all quizzes:  6
 * The maximum of all exams:   99
 * The average of all exams:   84
 * The maximum of all totals:  80
 * The average of all totals:  71
 * The total number of A's:     0
 * The total number of B's:     0
 * The total number of C's:     2
 * The total number of D's:     0
 * The total number of F's:     1

 * 
 * @author Sam Kapp
 * @date 1/29/2023
 * 
 */

#include <iostream> 
#include <cmath>
#include <fstream>
#include <cctype>
#include <iomanip>

using namespace std;

void printHeader(ostream &out, string header);
void printInfo(ostream &out, int id, string lname, string fname, int quizzes[], int exams[], int final, double total, char letter);
void printSummary(ostream &out, int maxQuiz, int maxExam, double maxTotal, int numQuiz, int numExam, int numTotal, int numRecords, int letterGrades[]);
char getLetter(int total);

double calculateTotal(int quizzes[], int exams[], int final);


int main() {
    ifstream in; 
    ofstream out;

    in.open("infile.txt");
    out.open("outfile.txt");

    char inchar; 

    // Get the default header 
    // Format it and print to outfile
    string header; 
    in >> header;
    printHeader(out, header);

    // Highest of each grade across all records
    // All quizzes/exams/totals added up across all records
    int maxQuiz = 0; 
    int numQuiz = 0;
    int maxExam = 0;
    int numExam = 0;
    double maxTotal = 0;
    double numTotal = 0;
    int numRecords = 0;

    // Tracks all letter grades across all records
    // 0 = A, 1 = B, 2 = C, 3 = D, 4 = F
    int letterGrades[5] = {0, 0, 0, 0, 0}; 

    // Loop through the file
    while (!in.eof()) {
        // Initialize all needed information from the record
        int id = 0; 
        string lname = ""; 
        string fname = ""; 
        int quizzes[6];
        int exams[2];
        int final;
        double total;
        char letter;

        // GET ID 
        in >> id;

        // Ignore the comma
        in.ignore(1);
        
        // GET LNAME 
        do {
            in >> inchar;
            lname += inchar;
        } while (inchar != ',');

        // Get rid of comma on the end of the string
        lname = lname.substr(0, lname.length()-1);

        // GET FNAME
        do {
            in >> inchar;
            fname += inchar;
        } while (inchar != ',');

        // Get rid of comma on the end of the string
        fname = fname.substr(0, fname.length()-1);

        

        // GET QUIZZES
        for (int i = 0; i < 6; i++) {
            in >> quizzes[i];
            if (maxQuiz < quizzes[i])
                maxQuiz = quizzes[i];
            numQuiz += quizzes[i];
            //ignore comma
            in.ignore(1);
        }

        // GET EXAMS 
        for (int i = 0; i < 2; i++) {
            in >> exams[i];
            if (maxExam < exams[i]) 
                maxExam = exams[i];
            numExam += exams[i];
            //ignore comma
            in.ignore(1);
        }

        // GET FINAL
        in >> final;
        if (maxExam < final)
            maxExam = final;
        numExam += final;

        // Calculate the total grade
        total = calculateTotal(quizzes, exams, final);

        numTotal += total; 

        if (maxTotal < total)
            maxTotal = total;
        
        letter = getLetter(total);
        
        // Add letter grade to the array of letter grades
        switch(letter) {
            case 'A': 
                letterGrades[0]++;
                break;
            case 'B': 
                letterGrades[1]++;
                break;
            case 'C': 
                letterGrades[2]++;
                break;
            case 'D': 
                letterGrades[3]++;
                break;
            default: 
                letterGrades[4]++;
                break;

        }

        printInfo(out, id, lname, fname, quizzes, exams, final, total, letter);

        numRecords++;
    }

    out << endl;
    printSummary(out, maxQuiz, maxExam, maxTotal, numQuiz, numExam, numTotal, numRecords, letterGrades);
}

/**
 * Prints out the default header in the file
 * 
 * PostConditions: 
 *  - The header has been properly outputted to the given stream
 */
void printHeader(ostream &out, string header) {
    string newHeader;
    int wordLength = 5;
    for (int i = 0; i < header.length()-1; i++){
        if (header[i] != ',') {
            newHeader += header[i];
        } else {
            out << newHeader << setw(wordLength) << " "; 
            wordLength = 0;
            newHeader = "";
        }
        wordLength++;
    }
    out << newHeader << setw(wordLength) << " ";
    out << "Total" << setw(5) << " "; 
    out << "Grade" << endl;
    
}

/**
 * Preconditions: 
 *  -all info has been found and stored from the file and given
 * 
 * Postconditions: 
 *  -The info has been properly outputted to the given stream
 *  - All text is left-justified 
 *  - ALl numbers are right justified
 * 
 */
void printInfo(ostream &out, int id, string lname, string fname, int quizzes[], int exams[], int final, double total, char letter) {
    int fnameLength = fname.length(); 
    int lnameLength = lname.length();

    out << id << setw(4) << " ";
    out << lname << setw(11 - lnameLength) << " ";
    out << fname << setw((12 - fnameLength) - (quizzes[0] / 10)) << " ";
    for (int i = 0; i < 5; i++) {
        if ((quizzes[i+1] / 10) == 1) 
            out << quizzes[i] << setw(3) << " ";
        else 
            out << quizzes[i] << setw(4) << " ";
    }
    out << quizzes[5] << setw(3) << " ";
    out << exams[0] << setw(3) << " "; 
    out << exams[1] << setw(6) << " "; 
    out << setprecision(4) << final << setw(9) << " "; 
    out << total << setw(5) << " "; 
    out << letter << endl;
}

/**
 * Preconditions: 
 *  - all needed info has been stored already and given
 * 
 * Postconditions: 
 *  - The total score has been returned with quizzes total being 25% 
 *      and exams each being worth 25%
 * 
*/
double calculateTotal(int quizzes[], int exams[], int final) {
    int quizTotal = 0; 
    int examsTotal = 0;

    int minQuiz = 0;

    for (int i = 0; i < 6; i++) {
        if (minQuiz > quizzes[i])
            minQuiz = quizzes[i];

        quizTotal += quizzes[i];
    }
    quizTotal -= minQuiz;
    quizTotal *= .25;

    for (int i = 0; i < 2; i++) {
        examsTotal += (exams[i] * .25);
    }
    examsTotal += (final * .25);
    return quizTotal + examsTotal;
}

/**
 * Preconditions: 
 *  -All Records have been run through and their needed information stored and given
 * 
 * Postconditions: 
 *  - A summary of all information gathered has been outputted to the given stream
 * 
 * 
*/
void printSummary(ostream &out, int maxQuiz, int maxExam, double maxTotal, int numQuiz, int numExam, int numTotal, int numRecords, int letterGrades[]) {
    double avgQuiz = numQuiz / (numRecords*6);
    double avgExam = numExam / (numRecords*3);
    double avgTotal = numTotal / numRecords;

    out << "The maximum of all quizzes: " << maxQuiz << endl; 
    out << "The average of all quizzes:  " << avgQuiz << endl;
    out << "The maximum of all exams:   " << maxExam << endl; 
    out << "The average of all exams:   " << avgExam << endl;
    out << "The maximum of all totals:  " << setprecision(2) << maxTotal << endl; 
    out << "The average of all totals:  " << setprecision() <<avgTotal << endl;
    out << "The total number of A's:     " << letterGrades[0] <<  endl;
    out << "The total number of B's:     " << letterGrades[1] << endl;
    out << "The total number of C's:     " << letterGrades[2] << endl;
    out << "The total number of D's:     " << letterGrades[3] << endl;
    out << "The total number of F's:     " << letterGrades[4] << endl;
}

/**
 * Precondition: 
 *  -the total grade has been given 
 * 
 * Postcondition: 
 *  - The accurate letter grade has been returned
*/
char getLetter(int total) {
    if (total > 90) return 'A'; 
    else if (total > 80) return 'B'; 
    else if (total > 70) return 'C'; 
    else if (total > 60) return 'D'; 
    return 'F';
}
    

