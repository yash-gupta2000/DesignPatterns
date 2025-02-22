#include <bits/stdc++.h>
using namespace std;

enum VehicleType {
    TwoWheeler, FourWheeler
};

class Vehicle {
public: 
    int VehicleNo;
    VehicleType vehicleType;

    Vehicle(int VehicleNo, VehicleType vehicleType) {
        this->VehicleNo = VehicleNo;
        this->vehicleType = vehicleType;
    }
};

class ParkingSpot {
public:
    int id;
    bool isEmpty;
    Vehicle* vehicle;  // Pointer to Vehicle object
    int price;

    ParkingSpot(int id, int price) {
        this->id = id;
        this->price = price;
        this->isEmpty = true;
        this->vehicle = nullptr;
    }

    void parkVehicle(Vehicle* v) {
        this->isEmpty = false;
        this->vehicle = v;
    }

    void removeVehicle() {
        this->vehicle = nullptr;
        this->isEmpty = true;
    }
};

class ParkingSpotManager {
protected:
    vector<ParkingSpot> spots;

public:
    ParkingSpotManager(vector<ParkingSpot> spots) {
        this->spots = spots;
    }

    virtual ParkingSpot* findParkingSpace() = 0;

    void parkVehicle(Vehicle* v) {
        ParkingSpot* spot = findParkingSpace();
        if (spot != nullptr) {
            spot->parkVehicle(v);
        }
    }

    void removeVehicle(Vehicle* v) {
        for (ParkingSpot& spot : spots) {
            if (spot.vehicle != nullptr && spot.vehicle->VehicleNo == v->VehicleNo) {
                spot.removeVehicle();
                break;
            }
        }
    }
};

class FourWheelerManager : public ParkingSpotManager {
public:
    FourWheelerManager(vector<ParkingSpot> spots) : ParkingSpotManager(spots) {}

    ParkingSpot* findParkingSpace() override {
        for (ParkingSpot& spot : spots) {
            if (spot.isEmpty) {
                return &spot;
            }
        }
        return nullptr;
    }
};

class ParkingSpotManagerFactory {
public:
    ParkingSpotManager* getParkingSpotManager(VehicleType vehicleType, vector<ParkingSpot> spots) {
        if (vehicleType == TwoWheeler)
            return new FourWheelerManager(spots);
        else if (vehicleType == FourWheeler)
            return new FourWheelerManager(spots);
        return nullptr;
    }
};

// Ticket class (Fixed Syntax Issue)
class Ticket {
public:
    long long entryTime;
    ParkingSpot* parkingSpot;
    Vehicle* vehicle;

    Ticket(long long entryTime, ParkingSpot* parkingSpot, Vehicle* vehicle) {
        this->entryTime = entryTime;
        this->parkingSpot = parkingSpot;
        this->vehicle = vehicle;
    }
};

// EntranceGate class
class EntranceGate {
public:
    ParkingSpotManagerFactory factory;

    EntranceGate(ParkingSpotManagerFactory factory) {
        this->factory = factory;
    }

    ParkingSpot* findParkingSpace(VehicleType vehicleType, vector<ParkingSpot>& spots) {
        ParkingSpotManager* manager = factory.getParkingSpotManager(vehicleType, spots);
        return manager->findParkingSpace();
    }

    Ticket* generateTicket(Vehicle* vehicle, ParkingSpot* parkingSpot) {
        if (parkingSpot == nullptr) {
            cout << "No available parking spots!" << endl;
            return nullptr;
        }
        return new Ticket(time(0), parkingSpot, vehicle);
    }
};

// ExitGate class
class ExitGate {
public:
    ParkingSpotManagerFactory factory;

    ExitGate(ParkingSpotManagerFactory factory) {
        this->factory = factory;
    }

    void removeVehicle(Ticket* ticket, vector<ParkingSpot>& spots) {
        ParkingSpotManager* manager = factory.getParkingSpotManager(ticket->vehicle->vehicleType, spots);
        manager->removeVehicle(ticket->vehicle);
        delete ticket;  // Prevent memory leak
    }
};

// Main function
int main() {
    vector<ParkingSpot> spots;
    for (int i = 1; i <= 100; ++i) {
        if (i <= 50)
            spots.push_back(ParkingSpot(i, 10));
        else
            spots.push_back(ParkingSpot(i, 20));
    }

    ParkingSpotManagerFactory factory;

    EntranceGate entranceGate(factory);
    ExitGate exitGate(factory);

    Vehicle* vehicle = new Vehicle(123, TwoWheeler);
    ParkingSpot* spot = entranceGate.findParkingSpace(vehicle->vehicleType, spots);
    Ticket* ticket = entranceGate.generateTicket(vehicle, spot);

    Vehicle* car = new Vehicle(1234, FourWheeler);
    ParkingSpot* spot2 = entranceGate.findParkingSpace(car->vehicleType, spots);
    Ticket* ticket2 = entranceGate.generateTicket(car, spot);

    if (ticket) {
        cout << "Ticket generated for vehicle: " << vehicle->VehicleNo << endl;
    }

    if (ticket2) {
        cout << "Ticket generated for vehicle: " << car->VehicleNo << endl;
    }

    exitGate.removeVehicle(ticket, spots);
    exitGate.removeVehicle(ticket2, spots);

    delete vehicle;
    delete car;
    return 0;
}
