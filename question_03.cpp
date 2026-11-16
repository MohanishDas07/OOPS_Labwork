#include <iostream>

using namespace std;

class DynamicNumber {
private:
    int* value;

public:
    DynamicNumber() {
        value = new int(0);
        cout << "Default constructor called" << endl;
    }

    DynamicNumber(int val) {
        value = new int(val);
        cout << "Parameterized constructor called with value " << val << endl;
    }

    ~DynamicNumber() {
        delete value;
        cout << "Destructor called" << endl;
    }

    DynamicNumber(const DynamicNumber& other) {
        value = new int(*other.value);
        cout << "Copy constructor called" << endl;
    }

    DynamicNumber& operator=(const DynamicNumber& other) {
        cout << "Copy assignment operator called" << endl;
        if (this != &other) {
            delete value;
            value = new int(*other.value);
        }
        return *this;
    }

    DynamicNumber(DynamicNumber&& other) noexcept {
        value = other.value;
        other.value = nullptr;
        cout << "Move constructor called" << endl;
    }

    DynamicNumber& operator=(DynamicNumber&& other) noexcept {
        cout << "Move assignment operator called" << endl;
        if (this != &other) {
            delete value;
            value = other.value;
            other.value = nullptr;
        }
        return *this;
    }

    void display() const {
        if (value != nullptr) {
            cout << "Value: " << *value << endl;
        } else {
            cout << "Value: (null/moved)" << endl;
        }
    }
};

int main() {
    DynamicNumber num1;
    num1.display();

    DynamicNumber num2(42);
    num2.display();

    DynamicNumber num3 = num2;
    num3.display();

    DynamicNumber num4;
    num4 = num2;
    num4.display();

    DynamicNumber num5 = static_cast<DynamicNumber&&>(num2);
    num5.display();
    num2.display();

    DynamicNumber num6;
    num6 = static_cast<DynamicNumber&&>(num3);
    num6.display();
    num3.display();

    return 0;
}
