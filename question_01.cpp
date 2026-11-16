#include <iostream>
#include <string>

using namespace std;

int main() {
    int age = 20;
    float height = 5.9f;
    double balance = 1250.75;
    char grade = 'A';
    bool isStudent = true;
    string name = "Alex";

    const double PI = 3.14159;
    const int MAX_SCORE = 100;

    cout << "Name: " << name << endl;
    cout << "Age: " << age << endl;
    cout << "Height: " << height << endl;
    cout << "Balance: " << balance << endl;
    cout << "Grade: " << grade << endl;
    cout << "Is Student: " << isStudent << endl;
    cout << "Constant PI: " << PI << endl;
    cout << "Constant MAX_SCORE: " << MAX_SCORE << endl;

    int a = 15;
    int b = 4;

    cout << "Addition: " << (a + b) << endl;
    cout << "Subtraction: " << (a - b) << endl;
    cout << "Multiplication: " << (a * b) << endl;
    cout << "Division: " << (a / b) << endl;
    cout << "Modulo: " << (a % b) << endl;

    cout << "Is a > b: " << (a > b) << endl;
    cout << "Is a == b: " << (a == b) << endl;
    cout << "Logical AND: " << (a > 10 && b < 5) << endl;
    cout << "Logical OR: " << (a < 10 || b < 5) << endl;
    cout << "Logical NOT: " << !(a == b) << endl;

    int inputNumber;
    cout << "Enter an integer: ";
    if (cin >> inputNumber) {
        cout << "You entered: " << inputNumber << endl;
    }

    return 0;
}
