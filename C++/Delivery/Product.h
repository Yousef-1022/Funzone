#include <string>

class Product   
{

public:


    Product(std::string theName, std::string theAddress) {name = theName; address = theAddress; }
    std::string address;    //GasStation
    std::string name;
};