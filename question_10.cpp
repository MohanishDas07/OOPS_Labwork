#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main() {
    string filename = "students.csv";

    fstream file;
    file.open(filename, ios::out | ios::trunc);

    if (!file.is_open()) {
        cout << "Error creating file" << endl;
        return 1;
    }

    file << "Roll,Name,Marks\n";
    cout << "Initial write position (tellp): " << file.tellp() << endl;

    file << "101,Alice,88.5\n";
    cout << "Position after record 1 (tellp): " << file.tellp() << endl;

    file << "102,Bob,79.0\n";
    file << "103,Charlie,92.5\n";

    file.seekp(0, ios::end);
    cout << "Write position after seekp to end: " << file.tellp() << endl;

    file.close();

    file.open(filename, ios::in);
    if (!file.is_open()) {
        cout << "Error opening file for reading" << endl;
        return 1;
    }

    cout << endl << "Initial read position (tellg): " << file.tellg() << endl;

    string line;
    getline(file, line);
    cout << "Header line: " << line << endl;
    cout << "Read position after header (tellg): " << file.tellg() << endl;

    streampos dataStart = file.tellg();

    cout << endl << "Student records in CSV:" << endl;
    while (getline(file, line)) {
        stringstream ss(line);
        string roll, name, marks;

        if (getline(ss, roll, ',') && getline(ss, name, ',') && getline(ss, marks, ',')) {
            cout << "Roll: " << roll << " | Name: " << name << " | Marks: " << marks << endl;
        }
    }

    cout << "Final read position (tellg): " << file.tellg() << endl;

    file.clear();
    file.seekg(dataStart, ios::beg);
    cout << endl << "Rewound read position with seekg to: " << file.tellg() << endl;

    if (getline(file, line)) {
        cout << "First record read again: " << line << endl;
    }

    file.close();

    return 0;
}
