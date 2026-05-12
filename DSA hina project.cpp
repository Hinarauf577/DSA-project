#include <iostream>
#include <stack>
#include <queue>
#include <string>

using namespace std;

class Vehicle
{
public:
    string number;
    int entryTime;

    Vehicle(string num)
    {
        number = num;
        entryTime = 0;
    }
};

class ParkingSystem
{
private:
    stack<Vehicle> parking;
    queue<Vehicle> waiting;

    int maxParkingSlots;
    int hourlyRate;

public:
    ParkingSystem(int slots, int rate)
    {
        maxParkingSlots = slots;
        hourlyRate = rate;
    }

    // Enter Vehicle
    void enterVehicle(string number)
    {
        Vehicle v(number);

        if (parking.size() < maxParkingSlots)
        {
            parking.push(v);
            cout << "\nVehicle " << number << " parked successfully.\n";
        }
        else
        {
            waiting.push(v);
            cout << "\nParking Full! Vehicle added to waiting queue.\n";
        }
    }

    // Exit Vehicle
    void exitVehicle()
    {
        if (parking.empty())
        {
            cout << "\nNo vehicle in parking.\n";
            return;
        }

        Vehicle v = parking.top();
        parking.pop();

        int hours;
        cout << "Enter Parking Hours: ";
        cin >> hours;

        int fee = hours * hourlyRate;

        cout << "\nVehicle Exited Successfully.\n";
        cout << "Vehicle Number : " << v.number << endl;
        cout << "Parking Time   : " << hours << " hour(s)\n";
        cout << "Parking Fee    : Rs. " << fee << endl;

        // Move waiting vehicle to parking
        if (!waiting.empty())
        {
            Vehicle nextVehicle = waiting.front();
            waiting.pop();

            parking.push(nextVehicle);

            cout << "\nVehicle from waiting queue moved to parking: "
                 << nextVehicle.number << endl;
        }
    }

    // Display Parking
    void displayParking()
    {
        if (parking.empty())
        {
            cout << "\nParking is empty.\n";
            return;
        }

        stack<Vehicle> temp = parking;

        cout << "\n===== Parked Vehicles =====\n";

        while (!temp.empty())
        {
            cout << temp.top().number << endl;
            temp.pop();
        }
    }

    // Display Waiting Queue
    void displayWaitingQueue()
    {
        if (waiting.empty())
        {
            cout << "\nWaiting queue is empty.\n";
            return;
        }

        queue<Vehicle> temp = waiting;

        cout << "\n===== Waiting Vehicles =====\n";

        while (!temp.empty())
        {
            cout << temp.front().number << endl;
            temp.pop();
        }
    }

    // Search Vehicle
    void searchVehicle(string number)
    {
        bool found = false;

        stack<Vehicle> tempStack = parking;

        while (!tempStack.empty())
        {
            if (tempStack.top().number == number)
            {
                cout << "\nVehicle found in Parking Area.\n";
                found = true;
                break;
            }

            tempStack.pop();
        }

        if (!found)
        {
            queue<Vehicle> tempQueue = waiting;

            while (!tempQueue.empty())
            {
                if (tempQueue.front().number == number)
                {
                    cout << "\nVehicle found in Waiting Queue.\n";
                    found = true;
                    break;
                }

                tempQueue.pop();
            }
        }

        if (!found)
        {
            cout << "\nVehicle not found.\n";
        }
    }
};

int main()
{
    int choice;
    string vehicleNumber;

    ParkingSystem system(3, 100);

    do
    {
        cout << "\n========== Parking Management System ==========\n";
        cout << "1. Enter Vehicle\n";
        cout << "2. Exit Vehicle\n";
        cout << "3. Display Parking\n";
        cout << "4. Display Waiting Queue\n";
        cout << "5. Search Vehicle\n";
        cout << "6. Exit\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter Vehicle Number: ";
            cin >> vehicleNumber;

            system.enterVehicle(vehicleNumber);
            break;

        case 2:
            system.exitVehicle();
            break;

        case 3:
            system.displayParking();
            break;

        case 4:
            system.displayWaitingQueue();
            break;

        case 5:
            cout << "Enter Vehicle Number to Search: ";
            cin >> vehicleNumber;

            system.searchVehicle(vehicleNumber);
            break;

        case 6:
            cout << "\nExiting Program...\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 6);

    return 0;
}