#include <iostream>
#include <string>

using namespace std;

class Person {
protected:
    string name;
    int age;

public:
    Person(string n, int a) {
        name = n;
        age = a;
    }

    void displayPerson() const {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
    }
};

class Student : public Person {
protected:
    int studentId;
    string major;

public:
    Student(string n, int a, int id, string m)
        : Person(n, a) {
        studentId = id;
        major = m;
    }

    void displayStudent() const {
        displayPerson();
        cout << "Student ID: " << studentId << endl;
        cout << "Major: " << major << endl;
    }
};

class GraduateStudent : public Student {
private:
    string thesisTopic;
    string supervisor;

public:
    GraduateStudent(string n, int a, int id, string m, string topic, string prof)
        : Student(n, a, id, m) {
        thesisTopic = topic;
        supervisor = prof;
    }

    void displayGraduateStudent() const {
        displayStudent();
        cout << "Thesis Topic: " << thesisTopic << endl;
        cout << "Supervisor: " << supervisor << endl;
    }
};

int main() {
    cout << "--- Single Inheritance (Student) ---" << endl;
    Student s("Bob", 20, 101, "Computer Science");
    s.displayStudent();

    cout << endl << "--- Multilevel Inheritance (GraduateStudent) ---" << endl;
    GraduateStudent gs("Alice", 25, 201, "Artificial Intelligence", "Neural Networks", "Dr. Smith");
    gs.displayGraduateStudent();

    return 0;
}
