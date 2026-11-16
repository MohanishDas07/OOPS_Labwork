#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <string>

using namespace std;

int addGraceMarks(int mark) {
    return mark + 5;
}

int main() {
    vector<int> marks = {75, 92, 64, 88, 55, 98, 81};

    cout << "Original Marks:" << endl;
    for (int m : marks) {
        cout << m << " ";
    }
    cout << endl;

    sort(marks.begin(), marks.end());

    cout << endl << "Sorted Marks (Ascending):" << endl;
    for (int m : marks) {
        cout << m << " ";
    }
    cout << endl;

    auto it = find_if(marks.begin(), marks.end(), [](int m) {
        return m >= 90;
    });

    if (it != marks.end()) {
        cout << endl << "First mark >= 90 found: " << *it << endl;
    }

    vector<int> updatedMarks(marks.size());
    transform(marks.begin(), marks.end(), updatedMarks.begin(), addGraceMarks);

    cout << endl << "Marks after adding 5 grace marks:" << endl;
    for (int m : updatedMarks) {
        cout << m << " ";
    }
    cout << endl;

    map<string, int> studentMarks;
    studentMarks["Charlie"] = 78;
    studentMarks["Alice"] = 95;
    studentMarks["Bob"] = 85;

    cout << endl << "Student Marks (std::map - Sorted by Name):" << endl;
    for (const auto& pair : studentMarks) {
        cout << pair.first << ": " << pair.second << endl;
    }

    unordered_map<int, string> studentRollMap;
    studentRollMap[101] = "Alice";
    studentRollMap[102] = "Bob";
    studentRollMap[103] = "Charlie";

    cout << endl << "Student Directory (std::unordered_map - Roll to Name):" << endl;
    for (const auto& pair : studentRollMap) {
        cout << "Roll No " << pair.first << " -> " << pair.second << endl;
    }

    return 0;
}
