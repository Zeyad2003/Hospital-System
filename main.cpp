//==========================================================
// Name        : Hospital System
// Author      : Zeyad Nasef
// Version     : Dr. Mostafa Saad Projects
// Created at  : March 2021
// Description : Simple System for Hospitals
//==========================================================
#pragma GCC optimization("0fast")
#include <bits/stdc++.h>
using namespace std;

bool firstTime = true; // used to check if the first time to print the header
const int MAX_SPECIALIZATION = 20; // max specialization number
const int MAX_QUEUE = 5; // max wait list number
// our data structure that will hold the patients with their data
deque<deque<tuple<string, int, bool> > > v(MAX_SPECIALIZATION + 1); // <name, specialization, status>


// function to check if you want to continue using the system or not
bool Continue(){
    cout << "Do you want to continue? (y/n) ";
    char c; cin >> c;
    return (c == 'n' or c == 'N');
}


// function to show the menu
int menu() {
    if(!firstTime)
        if(Continue()) return 0;
    firstTime = false;
    int choice = -1;
    while (choice == -1) {
        cout << "Please Enter choice between[1 : 4] : \n";
        cout << "1) To Add new patient\n";
        cout << "2) To Print all patients\n";
        cout << "3) To Get next patient\n";
        cout << "4) Exit\n";

        cin >> choice;

        if ((!(1 <= (int)choice && (int)choice <= 4)) or cin.fail())  {
            cout << "Invalid choice. Try again\n";
            choice = -1;	// loop keep working until valid choice is entered
        }
    }
    return choice;
}


// function to add a new patient to the queue
void add_patient() {
    int spec; // specialization
    string name; // patient name
    int st; // status

    cout << "Please Enter Patient specialization [1 : 20] :";
    cin >> spec;
    if (!(spec >= 1 && spec <= 20)) {
        cout << "Invalid specialization. Try again\n";
        goto here;
    }
    if(v[spec].size() == MAX_QUEUE) {
        cout <<"\n**************************************************************\n"
        <<"!!Sorry we can't add more patients for this specialization!!"
        <<"\n**************************************************************\n";
        return;
    }

    cout << "Please Enter Patient name :";
    cin.ignore();
    getline(cin, name);
    here:

    cout << "Please Enter Patient status, (0) for urgent else for regular :";
    cin >> st;

    if(st == 0)
        v[spec].emplace_front(name, spec, st);
    else
        v[spec].emplace_back(name, spec, st);
    cout << "\n!!Patient added successfully!!\n\n";
}


// function to print all patients in the queue
void print_patients() {

    for (int spec = 1; spec <= MAX_SPECIALIZATION; ++spec) {
        if(v[spec].empty()) continue;

        else {
            cout << "****************************\n";
            cout << "Specialization " << spec << " : \n";

            for (auto &i: v[spec]) {
                cout << get<0>(i) << " : ";
                if (get<2>(i))
                    cout << "regular\n";
                else
                    cout << "urgent\n";
            }


        }
        cout << "****************************\n";
    }
}



// function to get the next patient in the queue to be treated
void get_next_patients() {
    int spec;
    cout << "Enter specialization :";
    cin >> spec;

    if(v[spec].empty()) {
        cout << "\n*******************************************\n"
             << "\"No patients at the moment. Have rest, Dr\""
             << "\n*******************************************\n\n";
        return;
    }
    else {
        cout << "\n***********************************\n\""
        << get<0>(v[spec].front()) << " please go with the Dr\""
        << "\n***********************************\n";
        v[spec].pop_front();
    }
}

// function to run the system
void hospital_system() {
    while (true) {
        int choice = menu();
        if (choice == 1) {
            add_patient();
        }
        else if (choice == 2) {
            print_patients();
        }
        else if (choice == 3) {
            get_next_patients();
        }
        else {
            cout << "\n*******************************\n"
                 << "!!Thanks for using our system!!"
                 << "\n*******************************\n";
            break;
        }
    }
}


// main function
int main(){
    v[0].emplace_back("", 0, 0);
    hospital_system();
    return 0;
}