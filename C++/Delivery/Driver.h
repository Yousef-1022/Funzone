#include "Vehicle.h"
#include <vector>   //For the list of products the driver has to take from the starting point
#include <string>   //For the location and fileName which contains the products
#include <fstream>  //Used to input the products the driver has to insert into the van
#include <iostream> //For testing


//Method to calculate the distance from the current location of the vehicle to another location
int distance (Vehicle van, std::string location) {
    
    std::ifstream file ("LocationToLocation.txt");  //File containing the possible location to go to
    std::string lineInFile;
    int ans;

    while ( file >> lineInFile ) {

        int semiColon = lineInFile.find(";");
        std::string firstPart = lineInFile.substr(0,semiColon);

        lineInFile = lineInFile.substr(semiColon+1);

        semiColon = lineInFile.find(";");
        std::string secondPart = lineInFile.substr(0,semiColon);

        lineInFile = lineInFile.substr(semiColon+1);
        int theDistance = atoi (lineInFile.c_str());

        if (firstPart == van.getCurrentLoc() && secondPart == location) { file.close(); ans=theDistance; break; }
    }
    return ans;
}


class Driver
{

private:

    std::vector<Product>list;   //Contains a list of products that the driver needs to take
    Vehicle van;

public:
    

    //Constructor
    Driver (std::string fileName, Vehicle vroom) {  //Takes a fileName containing the products

        std::ifstream file (fileName);
        std::string ProductString;

        while ( file>>ProductString ) {

            int semiColon = ProductString.find(";");
            Product p (ProductString.substr(0,semiColon) , ProductString.substr(semiColon+1) );
            list.push_back(p);

        }
        file.close();

        van = vroom;
    }
    

    //Public methods
    void DO() {
        
        int c = 0;
        while ( c < van.Capacity) {     //Capacity has to be less or equal to the size of the list
            van.insertCargo( take( list[c] ));
            c++;
        }

        //This for each loop does not work correctly due to the reason of skipping every SECOND element in the van.cargo vector!!!
        //for (Product p: van.cargo) {  deliver(p); }

        for ( ; 0<van.cargo.size(); ) { deliver(van.cargo[0]); }
            
    }


    Product take(Product p) { return p; }


    void deliver(Product p) {
        
        std::cout<<"\nVan location: '"<<van.getCurrentLoc()<<"', Current cargo size: ("<<van.cargo.size()<<"). Fuel level: "<<van.tank.getFuel()<<"\n";
        
        int dist = distance(van,p.address);     //std::cout<<"The distance is: "<<distance;     //Distance is a function
        if (!van.checkFuel(dist)) { van.refuel(); }     //CheckFuel is true if it doesn't need gas

        //std::cout<<" after checkFuel(): "<<van.tank.getFuel();
        van.drive(dist);
        //std::cout<<" after drive(): "<<van.tank.getFuel()<<'\n';
        std::cout<<"Cargo before removal of "<<p.name<<":\n"; for (Product x : van.cargo) { std::cout<<x.name<<" to "<<x.address<<", "; } std::cout<<"\n";
        van.removeCargo(p);
        std::cout<<"Cargo after removal of "<<p.name<<":\n"; if (van.cargo.size() == 0) { std::cout<<"Empty!"; } else { for (Product x : van.cargo) { std::cout<<x.name<<" to "<<x.address<<", "; } std::cout<<"\n"; }
        van.setCurrentLoc(p.address);
    }

};
