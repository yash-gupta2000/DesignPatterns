#include<bits/stdc++.h>
using namespace std;

class DriveStrategy {
    public:
        virtual void drive () = 0;
        virtual ~DriveStrategy() {}
};

class SportsDriveStrategy: public DriveStrategy {
    void drive() {
        cout<<"Sports Drive"<<endl;
    }
};

class XYZDriveStrategy: public DriveStrategy {
    void drive() {
        cout<<"XYZ Drive Strategy"<<endl;
    }
};

class Vehicle {
    DriveStrategy* obj;
    public:

    Vehicle(DriveStrategy* ds) {
        this->obj = ds;
    }
    
    ~Vehicle() {
        if(obj) {
            delete obj;
            obj = nullptr;
        }
    }

    void drive() {
        obj->drive();
    }
};

class SportsCar: public Vehicle {
    public:
    SportsCar(): Vehicle(new SportsDriveStrategy()) {
        
    } 
};

class OffRoadCar: public Vehicle {
    public:
    OffRoadCar(): Vehicle(new SportsDriveStrategy()){}
};
class NormalCar: public Vehicle {
    public:
    NormalCar(): Vehicle(new XYZDriveStrategy()){}
};

int main() {
    Vehicle* v = new SportsCar();
    v->drive();
    delete v;
    Vehicle* offRoad = new NormalCar();
    offRoad->drive();
    delete offRoad;

}
