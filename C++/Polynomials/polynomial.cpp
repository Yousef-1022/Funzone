/*Implement the polynomial type. Represent a polynomial as a sequence of its realvalued coefficients. Implement as methods: 
adding two polynomials, multiplying two polynomials, evaluating the polynomial (substituting a value to the variable).
*/
#include "polynomial.h"
#include <string>
#include <cmath> // For evaluation


//------------------------------------------------------------------
template <typename theType> //Template to catch incorrect type input
theType getInput () {
    
    theType givenType;
    std::cin >> givenType;

    bool IncorrectInput = std::cin.fail();

    if( IncorrectInput ) std::cin.clear();

    std::string tmp = "";
    getline(std::cin, tmp);

    IncorrectInput = IncorrectInput || tmp.size()!=0;
    if(IncorrectInput) { throw Polynomial::InvalidType; }
    return givenType;
}
//------------------------------------------------------------------


//Task: 	constructor without anything
//Input:    -
//Output:   Polynomial
//Activity: creates an empty polnomial object without any data set
Polynomial::Polynomial () {
    NumOfCoefficients = 0;
}


//Task: 	reading
//Input:    double values
//Output:   -
//Activity: reads the coefficients of the polynomial and puts them into the vector
void Polynomial::INPUT () {
    std::cout<<"Enter the amount of coefficients: ";

    int x = getInput<int>();

    if (x<0) { throw Polynomial::NegativeRankCoefficient; }
    if (x==0) { throw Polynomial::NoCoefficient; }
    NumOfCoefficients=x;

    for(int i=0; i<x; i++) {
        double tmp;
        std::cout<<"Enter coefficient number "<<i+1<<": ";
        tmp = getInput<double>();
        coefficients.push_back(tmp);
    }
}


//Task: 	writing
//Input:    ostream out - target of writing
//          Polynomial poly 
//Output:   ostream out - target of writing
//Activity: writes the polynomial's coefficients with their respective ranking
std::ostream& operator<<(std::ostream& out, const Polynomial& poly) {

    int thePower = poly.NumOfCoefficients-1;

    for (int i=0; i<poly.NumOfCoefficients; i++) {

        if (poly.coefficients[i] != 0) {

            if (thePower == 0) {

                if (poly.coefficients[i-1] == 0) {
                    out << " + (" << poly.coefficients[i] << ")";
                    continue;
                }
                else {
                    out << "(" << poly.coefficients[i] << ")";
                }

            }
            else {

                if (poly.coefficients[i+1] == 0) {
                    out << "(" << poly.coefficients[i] << ")x^" << thePower;
                    --thePower;
                }
                else {
                    out << "(" << poly.coefficients[i] << ")x^" << thePower << " + ";
                    --thePower;
                }

            }
        }
        else { --thePower; }
    }

    return out;
}


//Task: 	evaluating
//Input:    integer x
//Output:   integer ans
//Activity: substituting a value to the variable
double Polynomial::evaluate () {

    std::cout<<"Enter the value you would like to substitute: ";

    int x = getInput<int>();

    double ans = 0;
    for (int i=0; i<NumOfCoefficients; i++) {
        ans += coefficients[i] * pow(x,NumOfCoefficients-(i+1)); 
    }

    return ans;
}


//Task: 	adding
//Input:    Polynomial poly1    
//          Polynomial poly2    
//Output:   Polynomial poly3   
//Activity: adds the coefficients of the given Polynomials according to the rules of mathematics.
Polynomial operator+ (const Polynomial& poly1, const Polynomial& poly2) {

    Polynomial poly3;

    if (poly1.NumOfCoefficients >= poly2.NumOfCoefficients) { //If the first polynomial is bigger than the second one.
        
        poly3.NumOfCoefficients=poly1.NumOfCoefficients;

        for (int i=0; i<poly1.NumOfCoefficients; i++) { poly3.coefficients.push_back(poly1.coefficients[i]); } //Copying
    
        int tmp = poly3.NumOfCoefficients-poly2.NumOfCoefficients;  //Algorithm
        for (int i=0; i<poly2.NumOfCoefficients; i++) {
               poly3.coefficients[tmp] += poly2.coefficients[i];
               tmp++;
        }
    }
    else { //If the second polynomial is bigger than the first one.

        poly3.NumOfCoefficients=poly2.NumOfCoefficients; 
    
        for (int i=0; i<poly2.NumOfCoefficients; i++) { poly3.coefficients.push_back(poly2.coefficients[i]); } //Copying
    
        int tmp = poly3.NumOfCoefficients-poly1.NumOfCoefficients;  //Algorithm
        for (int i=0; i<poly1.NumOfCoefficients; i++) { 
            poly3.coefficients[tmp] += poly1.coefficients[i];
            tmp++;
        }
    }
    
   return poly3;
}


//Task: 	multiplying
//Input:    Polynomial poly1    
//          Polynomial poly2    
//Output:   Polynomial poly3   
//Activity: multiplies the coefficients of the given Polynomials according to the rules of mathematics.
Polynomial operator* (const Polynomial& poly1, const Polynomial& poly2) {

    Polynomial poly3;
    poly3.NumOfCoefficients=poly1.NumOfCoefficients+poly2.NumOfCoefficients-1;
    poly3.coefficients.resize(poly1.NumOfCoefficients+poly2.NumOfCoefficients-1);

    for (int i=0; i<poly1.NumOfCoefficients; i++)   {
        for (int j=0; j<poly2.NumOfCoefficients; j++)   {
            poly3.coefficients[i+j] += poly1.coefficients[i]*poly2.coefficients[j];
        }
    }

    return poly3;
}


//{Extra} For test mode
double Polynomial::evaluateTST (double x) {
    double ans = 0;
    for (int i=0; i<NumOfCoefficients; i++) { ans += coefficients[i] * pow(x,NumOfCoefficients-(i+1)); }
    return ans;
}