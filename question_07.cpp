#include <iostream>
#include <string>

using namespace std;

template <typename T>
class Stack {
private:
    T elements[50];
    int topIndex;

public:
    Stack() {
        topIndex = -1;
    }

    bool isEmpty() const {
        return topIndex == -1;
    }

    bool isFull() const {
        return topIndex == 49;
    }

    void push(T val) {
        if (isFull()) {
            cout << "Stack overflow" << endl;
            return;
        }
        topIndex++;
        elements[topIndex] = val;
    }

    void pop() {
        if (isEmpty()) {
            cout << "Stack underflow" << endl;
            return;
        }
        topIndex--;
    }

    T top() const {
        if (isEmpty()) {
            cout << "Stack is empty" << endl;
            return T();
        }
        return elements[topIndex];
    }

    void display() const {
        if (isEmpty()) {
            cout << "Stack is empty" << endl;
            return;
        }
        for (int i = topIndex; i >= 0; i--) {
            cout << elements[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    cout << "--- Integer Stack ---" << endl;
    Stack<int> intStack;
    intStack.push(10);
    intStack.push(20);
    intStack.push(30);
    intStack.display();
    cout << "Top element: " << intStack.top() << endl;
    intStack.pop();
    intStack.display();

    cout << endl << "--- Float Stack ---" << endl;
    Stack<float> floatStack;
    floatStack.push(1.5f);
    floatStack.push(2.75f);
    floatStack.push(3.14f);
    floatStack.display();
    cout << "Top element: " << floatStack.top() << endl;
    floatStack.pop();
    floatStack.display();

    cout << endl << "--- String Stack ---" << endl;
    Stack<string> stringStack;
    stringStack.push("Apple");
    stringStack.push("Banana");
    stringStack.push("Cherry");
    stringStack.display();
    cout << "Top element: " << stringStack.top() << endl;
    stringStack.pop();
    stringStack.display();

    return 0;
}
