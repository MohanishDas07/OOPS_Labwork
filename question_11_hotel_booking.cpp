#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <exception>

using namespace std;

class HotelException : public exception {
protected:
    string message;

public:
    HotelException(string msg) : message(msg) {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};

class RoomUnavailableException : public HotelException {
public:
    RoomUnavailableException(string msg) : HotelException(msg) {}
};

class InvalidBookingException : public HotelException {
public:
    InvalidBookingException(string msg) : HotelException(msg) {}
};

template <typename T>
void printHeader(T title) {
    cout << "========================================" << endl;
    cout << "   " << title << endl;
    cout << "========================================" << endl;
}

class Room {
protected:
    int roomNumber;
    double pricePerNight;
    bool isBooked;

public:
    Room(int num, double price) {
        roomNumber = num;
        pricePerNight = price;
        isBooked = false;
    }

    virtual ~Room() {}

    int getRoomNumber() const {
        return roomNumber;
    }

    bool getIsBooked() const {
        return isBooked;
    }

    void setBooked(bool status) {
        isBooked = status;
    }

    virtual string getRoomType() const = 0;
    virtual double calculateCost(int days) const = 0;

    virtual void display() const {
        cout << "Room Number: " << roomNumber << endl;
        cout << "Type: " << getRoomType() << endl;
        cout << "Price/Night: Rs." << pricePerNight << endl;
        cout << "Status: " << (isBooked ? "Booked" : "Available") << endl;
    }
};

class StandardRoom : public Room {
public:
    StandardRoom(int num) : Room(num, 1000.0) {}

    string getRoomType() const override {
        return "Standard Room";
    }

    double calculateCost(int days) const override {
        return pricePerNight * days;
    }

    void display() const override {
        Room::display();
        cout << "Amenities: Free Wi-Fi, TV" << endl;
        cout << "----------------------------------------" << endl;
    }
};

class DeluxeRoom : public Room {
private:
    double luxuryTax;

public:
    DeluxeRoom(int num) : Room(num, 2500.0) {
        luxuryTax = 300.0;
    }

    string getRoomType() const override {
        return "Deluxe Room";
    }

    double calculateCost(int days) const override {
        return (pricePerNight * days) + luxuryTax;
    }

    void display() const override {
        Room::display();
        cout << "Amenities: AC, Breakfast, Ocean View, Wi-Fi" << endl;
        cout << "Service Charge: Rs." << luxuryTax << endl;
        cout << "----------------------------------------" << endl;
    }
};

class Booking {
private:
    string customerName;
    int roomNumber;
    int stayDays;
    double totalCost;

public:
    Booking() {
        customerName = "";
        roomNumber = 0;
        stayDays = 0;
        totalCost = 0.0;
    }

    Booking(string name, int rNum, int days, double cost) {
        customerName = name;
        roomNumber = rNum;
        stayDays = days;
        totalCost = cost;
    }

    string getCustomerName() const {
        return customerName;
    }

    int getRoomNumber() const {
        return roomNumber;
    }

    int getStayDays() const {
        return stayDays;
    }

    double getTotalCost() const {
        return totalCost;
    }

    void display() const {
        cout << "Customer Name: " << customerName << endl;
        cout << "Room Number: " << roomNumber << endl;
        cout << "Stay Days: " << stayDays << endl;
        cout << "Total Amount: Rs." << totalCost << endl;
        cout << "----------------------------------------" << endl;
    }
};

class HotelManager {
private:
    vector<Room*> rooms;
    vector<Booking> bookings;

public:
    HotelManager() {
        rooms.push_back(new StandardRoom(101));
        rooms.push_back(new StandardRoom(102));
        rooms.push_back(new DeluxeRoom(201));
        rooms.push_back(new DeluxeRoom(202));
    }

    ~HotelManager() {
        for (Room* r : rooms) {
            delete r;
        }
    }

    void displayRooms() const {
        printHeader("AVAILABLE & TOTAL ROOMS");
        for (const Room* r : rooms) {
            r->display();
        }
    }

    void bookRoom(string customerName, int roomNumber, int days) {
        if (days <= 0) {
            throw InvalidBookingException("Booking days must be at least 1.");
        }

        auto it = find_if(rooms.begin(), rooms.end(), [roomNumber](Room* r) {
            return r->getRoomNumber() == roomNumber;
        });

        if (it == rooms.end()) {
            throw InvalidBookingException("Room number does not exist.");
        }

        if ((*it)->getIsBooked()) {
            throw RoomUnavailableException("Selected room is already booked.");
        }

        (*it)->setBooked(true);
        double cost = (*it)->calculateCost(days);

        Booking newBooking(customerName, roomNumber, days, cost);
        bookings.push_back(newBooking);

        cout << endl << "Booking Successful!" << endl;
        newBooking.display();
    }

    void displayBookings() const {
        printHeader("CURRENT BOOKINGS");
        if (bookings.empty()) {
            cout << "No bookings made yet." << endl;
            return;
        }
        for (const Booking& b : bookings) {
            b.display();
        }
    }

    void saveBookings(string filename) const {
        ofstream outFile(filename);
        if (!outFile.is_open()) {
            cout << "Failed to open file for saving." << endl;
            return;
        }

        for (const Booking& b : bookings) {
            outFile << b.getCustomerName() << ","
                    << b.getRoomNumber() << ","
                    << b.getStayDays() << ","
                    << b.getTotalCost() << "\n";
        }

        outFile.close();
        cout << "Bookings successfully saved to " << filename << endl;
    }

    void loadBookings(string filename) {
        ifstream inFile(filename);
        if (!inFile.is_open()) {
            cout << "Could not open file " << filename << " (file might not exist yet)." << endl;
            return;
        }

        bookings.clear();
        string line;

        while (getline(inFile, line)) {
            stringstream ss(line);
            string name, rNumStr, daysStr, costStr;

            if (getline(ss, name, ',') &&
                getline(ss, rNumStr, ',') &&
                getline(ss, daysStr, ',') &&
                getline(ss, costStr, ',')) {

                int rNum = stoi(rNumStr);
                int days = stoi(daysStr);
                double cost = stod(costStr);

                bookings.push_back(Booking(name, rNum, days, cost));

                auto it = find_if(rooms.begin(), rooms.end(), [rNum](Room* r) {
                    return r->getRoomNumber() == rNum;
                });
                if (it != rooms.end()) {
                    (*it)->setBooked(true);
                }
            }
        }

        inFile.close();
        cout << "Bookings successfully loaded from " << filename << endl;
    }
};

int main() {
    HotelManager hotel;
    int choice = 0;

    while (choice != 6) {
        printHeader("HOTEL BOOKING SYSTEM");
        cout << "1. View All Rooms" << endl;
        cout << "2. Book a Room" << endl;
        cout << "3. View All Bookings" << endl;
        cout << "4. Save Bookings to File" << endl;
        cout << "5. Load Bookings from File" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            string discard;
            cin >> discard;
            cout << "Invalid input. Please enter a valid number." << endl;
            continue;
        }

        if (choice == 1) {
            hotel.displayRooms();
        } else if (choice == 2) {
            string name;
            int roomNo, days;

            cout << "Enter Customer Name: ";
            cin >> name;
            cout << "Enter Room Number to book: ";
            cin >> roomNo;
            cout << "Enter Number of Days: ";
            cin >> days;

            try {
                hotel.bookRoom(name, roomNo, days);
            } catch (const HotelException& e) {
                cout << "Error: " << e.what() << endl;
            }
        } else if (choice == 3) {
            hotel.displayBookings();
        } else if (choice == 4) {
            hotel.saveBookings("hotel_bookings.txt");
        } else if (choice == 5) {
            hotel.loadBookings("hotel_bookings.txt");
        } else if (choice == 6) {
            cout << "Exiting Hotel Booking System. Thank you!" << endl;
        } else {
            cout << "Invalid choice! Please choose between 1 and 6." << endl;
        }

        cout << endl;
    }

    return 0;
}
