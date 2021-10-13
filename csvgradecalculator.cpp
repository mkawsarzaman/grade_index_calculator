#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include <sstream>
using namespace std;

const int MAX = 50;
const int MID = 30;
const int FINAL = 40;
const int LAB = 5;
const int ASSIGNMENT = 10;

// a function called GetData to read and store data into two arrays,
void GetData(ifstream& infile,string name[],double scores[][7],int& n){
    n = 0;
    int i = 0, j = 0;
    string line, fullname;
    string final_, mid_, lab_1, lab_2, lab_3, lab_4, assignment_;
    while(getline(infile, line, '\n')){
        stringstream ss(line);
        getline(ss, fullname, ',');
        getline(ss, final_, ',');
        getline(ss, mid_, ',');
        getline(ss, lab_1, ',');
        getline(ss, lab_2, ',');
        getline(ss, lab_3, ',');
        getline(ss, lab_4, ',');
        getline(ss, assignment_, ',');


        // initialize
        name[i] = fullname;
        scores[i][0] = (!final_.empty()) ? stoi(final_) : -1;
        scores[i][1] = (!mid_.empty()) ? stoi(mid_)     : -1;
        scores[i][2] = (!lab_1.empty()) ? stoi(lab_1)   : -1;
        scores[i][3] = (!lab_2.empty()) ? stoi(lab_2)   : -1;
        scores[i][4] = (!lab_3.empty()) ? stoi(lab_3)   : -1;
        scores[i][5] = (!lab_4.empty()) ? stoi(lab_4)   : -1;
        scores[i][6] = (!assignment_.empty()) ? stoi(assignment_) : -1;
        i++;
    }

    n = i;
}

char determineGrade(double avg){
    if(avg>=90 && avg<=100)
    return 'A';
    else if(avg>=80 && avg<90)
    return 'B';
    if(avg>=70 && avg<80)
    return 'C';
    if(avg>=60 && avg<70)
    return 'D';
    if(avg>=0 && avg<60)
    return 'F';
}



// a function called Average that is used to calculate the average test score and grade,
double calulateMarks(double score_individual, int terms){
    double marks = 0;
    if(score_individual == -1){
        return marks;
    }else{
        marks = (score_individual * terms) / 100;
    }
    return marks;
}

void Average(double score[][7],char grade[],double total[],int no_of_students){
    for(int i = 0; i < no_of_students; i++){
        double final_s = calulateMarks(score[i][0], FINAL);
        double mid_s = calulateMarks(score[i][1], MID);
        double labs_count = 0;
        double labs_s = 0;
        double assignment_s = score[i][6];
        double total_marks = 0;


        for(int j = 2; j <=5; j++){
                cout << score[i][j] << endl;
            if(score[i][j] == -1){
                labs_count++;
                score[i][j] = 0;
                if(labs_count == 2){
                    labs_s = 0;
                    break;
                }
            }else{
                labs_s += (score[i][j] * LAB) / 100;
            }
        }

        total_marks = labs_s + mid_s + final_s + assignment_s;
        total[i] = total_marks;
        cout << "Final: " << final_s << endl;
        cout << "Mid: " << mid_s << endl;
        cout << "Labs: " << labs_s << endl;
        cout << "Assignments: " << assignment_s << endl;

        if(labs_s == 0 || mid_s == 0 || final_s == 0){
            grade[i] = 'F';
            cout << total_marks << "-" << "F" << endl;
        }else{
            grade[i] = determineGrade(total_marks);
            cout << total_marks << "-" << determineGrade(total_marks) << endl;
        }
    }
}


// function called PrintResults to output the results.
void PrintResults(string name[],double total[],double scores[][7],char grade[],int n){
    cout << "Student Name & Marks" <<endl;
    cout << "===========================================================================" << endl;
    for(int i=0; i<n; i++){
        cout << left << setw(10) << name[i];
        for(int k=0; k<7; k++)
            cout << right << setw(8) << scores[i][k];
        cout << endl;
    }

    cout << endl;
    cout << "===========================================================================" << endl;
    cout << "Student Grades: " <<endl;
    cout << "===========================================================================" << endl;

    cout << "Full Name" << setw(13)<< " Total Marks" << setw(10) << "Grade" << endl;
    cout << "---------------------------------------------------------------------------" << endl;
    for(int i=0; i<n; i++){
        cout << left << setw(8)<< name[i];
        for(int k=0; k<1; k++)
            cout << right << setw(10) << total[i] << setw(12) << grade[i];
        cout << endl;
    }
}

int main(){
    // a one-dimensional array to store the students� names,
    string name[MAX];
    // a (parallel) two-dimensional array to store the test scores,
    double scores[MAX][7];
    // a parallel one-dimensional array to store grades.
    char grade[MAX];
    int no_of_students;
    double total[MAX];

    ifstream studentFile;
    studentFile.open("Student.csv");
    if(!studentFile.good()){
        cout <<"unable to open file." << endl;
        return 0;
    }

    GetData(studentFile, name, scores, no_of_students);
    studentFile.close();
    Average(scores, grade, total, no_of_students);
    PrintResults(name,total,scores,grade,no_of_students);

    return 0;
 }

