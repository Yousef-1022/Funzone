class FuelTank
{

private:

    double fuel;
    double capacity;

public:


    //Methods
    void addFuel(double amount) { fuel = fuel+amount; }
    void consumeFuel(double amount) { fuel = fuel-amount; }

    //Getters and setters
    double getFuel() { return fuel; }
    double getCapacity() { return capacity; }
    void setFuel (double theFuel) { fuel = theFuel; }
    void setCapacity ( double theCapacity) { capacity = theCapacity; }
  
};

