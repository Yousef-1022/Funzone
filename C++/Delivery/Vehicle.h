#include "Engine.h"
#include "FuelTank.h"
#include "Product.h"
#include <vector>   //For the cargo
#include <string>   //For the location of the van and its distance to a certain location


enum Color {BLUE,YELLOW};   //For the color of the van


class Vehicle
{

private:
    
    double consumption;

    //For the current location of the Vehicle in order to calculate the distance to the next drop off zone
    std::string currentLoc;  

public:

    enum ERRORS{NegativeValue};

    //Constructors for task
    Vehicle (double theConsumption);    //The task mentions that we only know the consumption of the Vehicle.
    Vehicle (double theConsumption, Color theColor);    //The task mentions that we may have the color of the Vehicle.
    Vehicle ();

    //Proper constructors for later advanced modification if needed
    //Copy constructor
    Vehicle (const Vehicle &vroom);
    //Constructors for: Vehicle without/with color
    Vehicle (double theConsumption, std::string theCurrentLoc, int theCargoCapacity, double theCurrentFuelOfTheCar, double theFuelTankCapacity);
    Vehicle (double theConsumption, std::string theCurrentLoc, int theCargoCapacity, Color theColor, double theCurrentFuelOfTheCar, double theFuelTankCapacity);
   

    //Public attributes
    int Capacity = 0;
    Color color;


    //Functions
    bool checkFuel(int distance);
    void refuel();
    void drive (int distance);
    void startCar();
    void stopCar();

    
    //Getters and a Setter
    double getConsumption () { return consumption; }
    std::string getCurrentLoc () { return currentLoc; }
    void setCurrentLoc (std::string location) { currentLoc = location; }


    //Parts of the Vehicle
    Engine engine;
    FuelTank tank;
    std::vector<Product>cargo;


    //Methods for managing the cargo
    void insertCargo (Product p) { cargo.push_back(p); } 
    void removeCargo (Product p) {      //Search algorithm
        int l = false;
        int index = 0;
        //This loop can be modified later on, this one serves a perfect scenario. {Point 1 to 2, 2 to 3, 4 to 5 .. }
        for (int i = 0; !l && i < cargo.size(); i++)  { if (cargo[i].name == p.name && cargo[i].address == p.address) { l = true; index = i; } }
        if (l) cargo.erase(cargo.begin() + index );
    }

};