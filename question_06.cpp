#include <iostream>
#include <string>

using namespace std;

class Complex {
private:
    double real;
    double imag;

public:
    Complex() {
        real = 0;
        imag = 0;
    }

    Complex(double r, double i) {
        real = r;
        imag = i;
    }

    void display() const {
        cout << real << " + " << imag << "i" << endl;
    }

    void display(string label) const {
        cout << label << ": " << real << " + " << imag << "i" << endl;
    }

    Complex add(double r) const {
        return Complex(real + r, imag);
    }

    Complex add(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }

    Complex operator*(const Complex& other) const {
        double r = (real * other.real) - (imag * other.imag);
        double i = (real * other.imag) + (imag * other.real);
        return Complex(r, i);
    }

    bool operator==(const Complex& other) const {
        return (real == other.real && imag == other.imag);
    }
};

int main() {
    Complex c1(4, 5);
    Complex c2(2, 3);

    cout << "--- Function Overloading ---" << endl;
    c1.display();
    c1.display("Number 1");

    Complex cMethodAdd1 = c1.add(5.0);
    cMethodAdd1.display("After adding scalar 5.0");

    Complex cMethodAdd2 = c1.add(c2);
    cMethodAdd2.display("After adding c2");

    cout << endl << "--- Operator Overloading ---" << endl;
    Complex cSum = c1 + c2;
    cSum.display("c1 + c2");

    Complex cDiff = c1 - c2;
    cDiff.display("c1 - c2");

    Complex cProd = c1 * c2;
    cProd.display("c1 * c2");

    if (c1 == c2) {
        cout << "c1 is equal to c2" << endl;
    } else {
        cout << "c1 is not equal to c2" << endl;
    }

    return 0;
}
