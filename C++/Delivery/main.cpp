#include "Driver.h"

#include <iostream>
int main () {

    double theConsumption = 0.12;
    std::string theCurrentLoc = "GasStation0";  //Has to be 0
    int theCargoCapacity = 7;
    double theCurrentFuelOfTheCar = 60.0;
    double theFuelTankCapacity = 60.0;

    Vehicle car (theConsumption,theCurrentLoc,theCargoCapacity,theCurrentFuelOfTheCar,theFuelTankCapacity);
    Driver D ("ProductList.txt",car);
    D.DO();
}