#include <iostream>
#include <queue>
#include <string>
using namespace std;

// Ride class to store ride details
class Ride {
public:
    string name;
    int capacity;
    queue<string> ticketQueue; // Queue to store customer names who booked this ride

    Ride(string name, int capacity) {
        this->name = name;
        this->capacity = capacity;
    }

    // Book ticket if space is available
    bool bookTicket(string customerName) {
        if (ticketQueue.size() < capacity) {
            ticketQueue.push(customerName);
            return true;
        }
        return false;
    }

    // Cancel ticket (FIFO removal)
    bool cancelTicket() {
        if (!ticketQueue.empty()) {
            ticketQueue.pop();
            return true;
        }
        return false;
    }

    // Display booked customers
    void displayTickets() {
        if (ticketQueue.empty()) {
            cout << "No tickets booked for " << name << "!" << endl;
            return;
        }
        cout << "Customers with tickets for " << name << ": " << endl;
        queue<string> temp = ticketQueue;
        while (!temp.empty()) {
            cout << "- " << temp.front() << endl;
            temp.pop();
        }
    }
};

// Queue-based Amusement Park System
class AmusementParkSystem {
private:
    queue<Ride> rides;     // Queue of rides
    queue<string> customers; // Queue of customers

public:
    // Add a ride to the queue
    void addRide(string name, int capacity) {
        rides.push(Ride(name, capacity));
        cout << "Ride added: " << name << endl;
    }

    // Add a customer to the queue
    void addCustomer(string name) {
        customers.push(name);
        cout << "Customer added: " << name << endl;
    }

    // Book a ticket for the first customer in the queue
    void bookTicket() {
        if (customers.empty()) {
            cout << "No customers in the queue!" << endl;
            return;
        }

        string customerName = customers.front(); // Get first customer
        customers.pop(); // Remove from queue

        queue<Ride> tempRides;
        bool ticketBooked = false;

        while (!rides.empty()) {
            Ride currentRide = rides.front();
            rides.pop();

            if (!ticketBooked && currentRide.bookTicket(customerName)) {
                cout << "Ticket booked successfully for " << customerName << " on " << currentRide.name << "!" << endl;
                ticketBooked = true;
            }

            tempRides.push(currentRide);
        }

        rides = tempRides; // Restore rides
        if (!ticketBooked) cout << "No available tickets. Customer removed from queue!" << endl;
    }

    // Display all rides
    void displayRides() {
        if (rides.empty()) {
            cout << "No rides available!" << endl;
            return;
        }

        queue<Ride> temp = rides;
        cout << "Available Rides: " << endl;
        while (!temp.empty()) {
            Ride ride = temp.front();
            temp.pop();
            cout << "- " << ride.name << " (Capacity: " << ride.capacity - ride.ticketQueue.size() << " available)" << endl;
        }
    }

    // Cancel the first booked ticket of a ride
    void cancelTicket(string rideName) {
        queue<Ride> tempRides;
        bool found = false;

        while (!rides.empty()) {
            Ride currentRide = rides.front();
            rides.pop();

            if (currentRide.name == rideName && !found) {
                if (currentRide.cancelTicket()) {
                    cout << "Ticket canceled for ride: " << rideName << endl;
                    found = true;
                } else {
                    cout << "No tickets to cancel for this ride!" << endl;
                }
            }

            tempRides.push(currentRide);
        }

        rides = tempRides; // Restore rides
    }

    // Display ride tickets
    void displayRideTickets(string rideName) {
        queue<Ride> tempRides;
        bool found = false;

        while (!rides.empty()) {
            Ride currentRide = rides.front();
            rides.pop();

            if (currentRide.name == rideName) {
                currentRide.displayTickets();
                found = true;
            }

            tempRides.push(currentRide);
        }

        rides = tempRides; // Restore rides

        if (!found) cout << "Ride not found!" << endl;
    }
};

int main() {
    AmusementParkSystem system;

    while (true) {
        cout << "\nAmusement Park Management System using Queue" << endl;
        cout << "1. Add Ride" << endl;
        cout << "2. Add Customer" << endl;
        cout << "3. Book Ticket" << endl;
        cout << "4. Cancel Ticket" << endl;
        cout << "5. Display Ride Tickets" << endl;
        cout << "6. Display Rides" << endl;
        cout << "7. Exit" << endl;

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                string name;
                int capacity;
                cout << "Enter ride name: ";
                getline(cin, name);
                cout << "Enter ride capacity: ";
                cin >> capacity;
                cin.ignore();
                system.addRide(name, capacity);
                break;
            }
            case 2: {
                string name;
                cout << "Enter customer name: ";
                getline(cin, name);
                system.addCustomer(name);
                break;
            }
            case 3:
                system.bookTicket();
                break;
            case 4: {
                string rideName;
                cout << "Enter ride name: ";
                getline(cin, rideName);
                system.cancelTicket(rideName);
                break;
            }
            case 5: {
                string rideName;
                cout << "Enter ride name: ";
                getline(cin, rideName);
                system.displayRideTickets(rideName);
                break;
            }
            case 6:
                system.displayRides();
                break;
            case 7:
                cout << "Exiting program. Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }
}

