/*Implement the polynomial type. Represent a polynomial as a sequence of its realvalued coefficients. Implement as methods: 
adding two polynomials, multiplying two polynomials, evaluating the polynomial (substituting a value to the variable).
*/
#include "polynomial.h"
using namespace std;

#define NORMAL_MODE
#ifdef NORMAL_MODE

//--------------------------------------------------------------------------------------------------------------------------
class Menu {
    public:
    Menu () {};
    void Run();

    private:
    int MenuPrint();
    void adding();
    void multiplying();
    void evaluating();
    void print();
};

//--------------------------------------------------------------------------------------------------------------------------
int main()
{
    Menu m;
    m.Run();
}
//--------------------------------------------------------------------------------------------------------------------------

int Menu::MenuPrint() {
    int choice;
    cout<<"\n****************************************\n";
    cout<<"0. Exit\n";
    cout<<"1. Add two polynomials\n";
    cout<<"2. Multiply two polynomials\n";
    cout<<"3. Evaluate a polynomial\n";
    cout<<"4. Print a poloynomial\n";
    cout<<"****************************************\n";

    cout << "Choose a number from the menu: ";
    string tmp;
    getline(cin>>std::ws, tmp);
    bool checkTmp = (tmp.find_first_not_of("01234") == string::npos);

    if (checkTmp) { choice = atoi(tmp.c_str()); }
    else { choice = 5; }

    return choice;
}
//----------------------------------------------------------Menu_Function
void Menu::Run() {
    int value;
    do {
        value = MenuPrint();
        switch(value){
            case 1:
                adding();                      break;
            case 2:
                multiplying();                 break;
            case 3:
                evaluating();                  break;
            case 4:
                print();                       break;
            case 5:
                cout<<"What part of `Choose a number from the menu:` did you not understand? Try again."; 
                break;
            default:
                cout<<"\nTerminated!\n";
                break;
        }
    } while(value != 0);
}
//----------------------------------------------------------Menu_Function
void Menu::adding () {
    
    try {
        cout<<"Polynomial 1:\n";
        Polynomial x;   x.INPUT();
     
        cout<<"Polynomial 2:\n";
        Polynomial y;   y.INPUT();
 
        Polynomial ans = x+y;
        cout<<"The answer is: "<<ans;
    }
    catch (Polynomial::Exceptions ERROR) {
        if(ERROR==Polynomial::NegativeRankCoefficient) { cerr<< "Negative coefficient!"; }
        if(ERROR==Polynomial::InvalidType) { cerr<< "Invalid type given!"; }
        if(ERROR==Polynomial::NoCoefficient) { cerr<< "A polynomial without coefficients isn't a polynomial!"; }
    }
}
//----------------------------------------------------------Menu_Function
void Menu::multiplying () {
   try {
        cout<<"Polynomial 1:\n";
        Polynomial x;   x.INPUT();

        cout<<"Polynomial 2:\n";
        Polynomial y;   y.INPUT();

        Polynomial ans = x*y;
        cout<<"The answer is: "<<ans;
    }
    catch (Polynomial::Exceptions ERROR) {
        if(ERROR==Polynomial::NegativeRankCoefficient) { cerr<< "Negative coefficient!"; }
        if(ERROR==Polynomial::InvalidType) { cerr<< "Invalid type given!"; }
        if(ERROR==Polynomial::NoCoefficient) { cerr<< "A polynomial without coefficients isn't a polynomial!"; }
    }
}
//----------------------------------------------------------Menu_Function
void Menu::evaluating () {
    try {
        cout<<"Polynomial:\n";
        Polynomial x;
        x.INPUT();
        double ans = x.evaluate();
        cout<<"The evaluation is: "<<ans;
    }
    catch (Polynomial::Exceptions ERROR) {
        if(ERROR==Polynomial::NegativeRankCoefficient) { cerr<< "Negative coefficient!"; }
        if(ERROR==Polynomial::InvalidType) { cerr<< "Invalid type given!"; }
        if(ERROR==Polynomial::NoCoefficient) { cerr<< "A polynomial without coefficients isn't a polynomial!"; }
    }
}
//----------------------------------------------------------Menu_Function
void Menu::print () {
    try {
        cout<<"Polynomial:\n";
        Polynomial x;
        x.INPUT();
        cout<<"The polynomial is: "<<x;
    }
    catch (Polynomial::Exceptions ERROR) {
        if(ERROR==Polynomial::NegativeRankCoefficient) { cerr<< "Negative coefficient!"; }
        if(ERROR==Polynomial::InvalidType) { cerr<< "Invalid type given!"; }
        if(ERROR==Polynomial::NoCoefficient) { cerr<< "A polynomial without coefficients isn't a polynomial!"; }
    }
}
//--------------------------------------------------------------------------------------------------------------------------

#else

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <sstream>


TEST_CASE("Polynomial declaration", "[polynomial]")
{
    Polynomial x;
    CHECK( x.getNumOfCoefficients() == x.getVectorSize() );
}


/*TEST_CASE("Polynomial making", "[polynomial]")
{
    Step1 : (Run Program) Insert negative int
    Step2 : (Run Program Again) Insert 0
    Step3 : (Run Program Again) Insert incorrect type input (not int)
    Step4 : (Run Program Again) Make the very first input correct, then: Insert incorrect type input (not int)
    Polynomial x;
    CHECK_THROWS(x.INPUT());
}*/


TEST_CASE("Adding two polynomials of the same size", "[polynomial]")
{
    Polynomial a1; a1.setNumOfCoefficients(3); 
    a1.setCoefficient(1); a1.setCoefficient(2); a1.setCoefficient(3);
    
    Polynomial a2; a2.setNumOfCoefficients(3); 
    a2.setCoefficient(10); a2.setCoefficient(20); a2.setCoefficient(30);

    Polynomial a3; a3=a1+a2;
    Polynomial check; check.setNumOfCoefficients(3);
    check.setCoefficient(11); check.setCoefficient(22); check.setCoefficient(33);
 
    stringstream buffer1,buffer2;
    buffer1 << a3; buffer2 << check;

    CHECK(buffer1.str() == buffer2.str());  
    
}


TEST_CASE("Adding two polynomials of the same size but they have their first coefficients 0", "[polynomial]")
{
    Polynomial a1; a1.setNumOfCoefficients(3);
    a1.setCoefficient(0); a1.setCoefficient(2); a1.setCoefficient(3);

    Polynomial a2; a2.setNumOfCoefficients(3);
    a2.setCoefficient(0); a2.setCoefficient(20); a2.setCoefficient(30);

    Polynomial a3; a3=a1+a2;
    Polynomial check; check.setNumOfCoefficients(3);
    check.setCoefficient(0); check.setCoefficient(22); check.setCoefficient(33);
 
    stringstream buffer1,buffer2;
    buffer1 << a3; buffer2 << check;

    CHECK(buffer1.str() == buffer2.str());      
}


TEST_CASE("Adding two polynomials, one is bigger than the other","[polynomial]")
{
    Polynomial a1; a1.setNumOfCoefficients(5); 
    a1.setCoefficient(100); a1.setCoefficient(200); a1.setCoefficient(300); a1.setCoefficient(400); a1.setCoefficient(500);

    Polynomial a2; a2.setNumOfCoefficients(3); 
    a2.setCoefficient(3.1); a2.setCoefficient(4.2); a2.setCoefficient(5.3);

    Polynomial a3; a3=a1+a2;
    Polynomial check; check.setNumOfCoefficients(5);
    check.setCoefficient(100); check.setCoefficient(200); check.setCoefficient(303.1); check.setCoefficient(404.2); check.setCoefficient(505.3);
 
    stringstream buffer1,buffer2;
    buffer1 << a3; buffer2 << check;

    CHECK(buffer1.str() == buffer2.str());   
}


TEST_CASE("Multiplying two polynomials of the same size", "[polynomial]")
{
    Polynomial a1; a1.setNumOfCoefficients(2);
    a1.setCoefficient(1); a1.setCoefficient(3);

    Polynomial a2; a2.setNumOfCoefficients(2);
    a2.setCoefficient(1); a2.setCoefficient(-3);

    Polynomial a3; a3=a1*a2;
    Polynomial check; check.setNumOfCoefficients(3);
    check.setCoefficient(1); check.setCoefficient(0); check.setCoefficient(-9);
 
    stringstream buffer1,buffer2;
    buffer1 << a3; buffer2 << check;

    CHECK(buffer1.str() == buffer2.str());  
}


TEST_CASE("Multiplying two polynomials of the same size but one of them has one of their coefficients 0", "[polynomial]")
{
    Polynomial a1; a1.setNumOfCoefficients(3);
    a1.setCoefficient(1); a1.setCoefficient(1); a1.setCoefficient(1);

    Polynomial a2; a2.setNumOfCoefficients(3);
    a2.setCoefficient(0); a2.setCoefficient(1); a2.setCoefficient(-3);

    Polynomial a3; a3=a1*a2;
    Polynomial check; check.setNumOfCoefficients(4);    
    check.setCoefficient(1); check.setCoefficient(-2); check.setCoefficient(-2); check.setCoefficient(-3);
 
    stringstream buffer1,buffer2;
    buffer1 << a3; buffer2 << check;

    CHECK(buffer1.str() == buffer2.str());  
}


TEST_CASE("Multiplying two polynomials, one is bigger than the other","[polynomial]")
{
    Polynomial a1; a1.setNumOfCoefficients(3);
    a1.setCoefficient(1); a1.setCoefficient(-2); a1.setCoefficient(3);

    Polynomial a2; a2.setNumOfCoefficients(2);
    a2.setCoefficient(1); a2.setCoefficient(-3);

    Polynomial a3; a3=a1*a2;
    Polynomial check; check.setNumOfCoefficients(4);
    check.setCoefficient(1); check.setCoefficient(-5); check.setCoefficient(9); check.setCoefficient(-9);
 
    stringstream buffer1,buffer2;
    buffer1 << a3; buffer2 << check;

    CHECK(buffer1.str() == buffer2.str());  
}


TEST_CASE("Evaluation with a postive variable", "[polynomial]")
{
    Polynomial a; a.setNumOfCoefficients(3);
    a.setCoefficient(2); a.setCoefficient(3); a.setCoefficient(4);
    CHECK(a.evaluateTST(3) == 31);
}


TEST_CASE("Evaluation with a negative variable", "[polynomial]")
{
    Polynomial a; a.setNumOfCoefficients(3);
    a.setCoefficient(2); a.setCoefficient(3); a.setCoefficient(4);
    CHECK(a.evaluateTST(-2) == 6);
}


TEST_CASE("Evaluation with a zero variable", "[polynomial]")
{
    Polynomial a; a.setNumOfCoefficients(3);
    a.setCoefficient(2); a.setCoefficient(3); a.setCoefficient(4);
    CHECK(a.evaluateTST(0) == 4);
}


#endif