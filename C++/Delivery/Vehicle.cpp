#include "Vehicle.h"


//---------------------------------------------------------------------------------------------------------------------------------------------------------
//Constructors for task
Vehicle::Vehicle (double theConsumption) {
    if (theConsumption < 0) { throw NegativeValue; }
    else consumption = theConsumption;
}

Vehicle::Vehicle (double theConsumption, Color theColor) {
    if (theConsumption < 0) { throw NegativeValue; }
    else {
        consumption = theConsumption;
        color = theColor;
    }
}   

Vehicle::Vehicle () {

}


//Proper constructors for later advanced modification if needed
//Copy constructor
Vehicle::Vehicle (const Vehicle &vroom) {
    //Private
    this->consumption = vroom.consumption;
    this->currentLoc = vroom.currentLoc;
    //Public
    this->Capacity = vroom.Capacity;
    this->color = vroom.color;
    this->engine = vroom.engine;
    this->tank = vroom.tank;
    this->cargo = vroom.cargo;
}

//Constructor Vehicle without color
Vehicle::Vehicle (double theConsumption, std::string theCurrentLoc, int theCargoCapacity, double theCurrentFuelOfTheCar, double theFuelTankCapacity) {
    if (theConsumption < 0) { throw NegativeValue; }
    else {
        consumption = theConsumption;
        currentLoc = theCurrentLoc;

        Capacity = theCargoCapacity;
        tank.setFuel(theCurrentFuelOfTheCar);
        tank.setCapacity(theFuelTankCapacity);
    }
}

//Constructor Vehicle with color
Vehicle::Vehicle (double theConsumption, std::string theCurrentLoc, int theCargoCapacity, Color theColor, double theCurrentFuelOfTheCar, double theFuelTankCapacity) {
    if (theConsumption < 0) { throw NegativeValue; }
    else {
        consumption = theConsumption;
        currentLoc = theCurrentLoc;

        Capacity = theCargoCapacity;
        color = theColor;
        tank.setFuel(theCurrentFuelOfTheCar);
        tank.setCapacity(theFuelTankCapacity);
    }
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------


//Functions
bool Vehicle::checkFuel(int distance) {     //Returns true if the vehicle does not need fuel

    double need = distance*consumption;
    return need <= tank.getFuel();
}

void Vehicle::refuel() {

    double deficit = tank.getCapacity() - tank.getFuel();
    tank.addFuel(deficit);
}

void Vehicle::drive (int distance) {
    
    startCar();
    tank.consumeFuel(distance*consumption);
    stopCar();
}

void Vehicle::startCar() { if ( !engine.isEngineRunning() ) engine.start(); }

void Vehicle::stopCar() { if (engine.isEngineRunning() ) engine.stop(); }