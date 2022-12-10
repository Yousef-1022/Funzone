/*Implement the polynomial type. Represent a polynomial as a sequence of its realvalued coefficients. Implement as methods: 
adding two polynomials, multiplying two polynomials, evaluating the polynomial (substituting a value to the variable).
*/
#ifndef POLYNOMIAL_H_INCLUDED
#define POLYNOMIAL_H_INCLUDED

#include <vector>
#include <iostream>

class Polynomial {

    public:
    enum Exceptions {NegativeRankCoefficient,NoCoefficient,InvalidType};

    Polynomial();

    double evaluate ();
    
    void INPUT (); //friend std::istream& operator>>(std::istream& in, Polynomial& poly);
    friend std::ostream& operator<<(std::ostream& out, const Polynomial& poly);
    friend Polynomial operator+ (const Polynomial& poly1, const Polynomial& poly2);
    friend Polynomial operator* (const Polynomial& poly1, const Polynomial& poly2);

    int getVectorSize () { return (int)coefficients.size(); }       //ForMenu
    int getNumOfCoefficients () { return NumOfCoefficients; }       //ForMenu
    double getCoefficient (int x) { return coefficients[x]; }       //ForMenu
    void setNumOfCoefficients (int x) { NumOfCoefficients = x; }    //ForMenu
    void setCoefficient (double x) { coefficients.push_back(x); }   //ForMenu
    double evaluateTST (double x);                                  //ForTest

    private:
    std::vector<double>coefficients;
    int NumOfCoefficients;
};

#endif