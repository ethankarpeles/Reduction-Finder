#include "elliptic.h"
using namespace std;
#include <cmath>

EllipticCurve::EllipticCurve(Rational a1, Rational a2, Rational a3, Rational a4, Rational a6){
    this->a1 = a1;
    this->a2 = a2;
    this->a3 = a3;
    this->a4 = a4;
    this->a6 = a6;
}

Rational EllipticCurve::getDeterminant() const{
    Rational b2 = a1*a1 + 4*a2;
    Rational b4 = 2*a4 + a1*a3;
    Rational b6 = a3*a3 + 4*a6;
    Rational b8 = a1*a1*a6 + 4*a2*a6 - a1*a3*a4 + a2*a3*a3 - a4*a4;
    return - b2*b2*b8 - 8*b4*b4*b4 - 27*b6*b6 + 9*b2*b4*b6;
}

Rational EllipticCurve::getC4() const{
    Rational b2 = a1*a1 + 4*a2;
    Rational b4 = 2*a4 + a1*a3;
    Rational b6 = a3*a3 + 4*a6;
    Rational b8 = a1*a1*a6 + 4*a2*a6 - a1*a3*a4 + a2*a3*a3 - a4*a4;
    return b2*b2 - 24*b4;
}

Rational EllipticCurve::getJ() const{
    return (getC4() * getC4() * getC4()) / getDeterminant();
}

ReductionType EllipticCurve::getReductionType(int modulus) const{
    Rational delta = this->getDeterminant();
    Rational c4 = this->getC4();
    if(delta == 0){
        return SINGULAR;
    }
    else if(pAdicValuationEqualsZero(delta, modulus)){
        return GOOD;
    }
    else if(pAdicValuationGreaterThanZero(delta, modulus) && pAdicValuationEqualsZero(c4, modulus)){
        return MULTIPLICATIVE;
    }
    else{
        return ADDITIVE;
    }
}

string EllipticCurve::getEquation() const{
    string equationString = "y^2";
    if (a1 != 0){
        equationString = equationString + " + " + (a1 != 1 ? a1.asString() : "") + "xy";
    }
    if (a3 != 0){
        equationString = equationString + " + " + (a3 != 1 ? a3.asString() : "") + "y";
    }
    equationString = equationString + " = x^3";
    if (a2 != 0){
        equationString = equationString + " + " + (a2 != 1 ? a2.asString() : "") + "x^2";
    }
    if (a4 != 0){
        equationString = equationString + " + " + (a4 != 1 ? a4.asString() : "") + "x";
    }
    if (a6 != 0){
        equationString = equationString + " + " + a6.asString();
    }
    return equationString;
}

string EllipticCurve::getCoefficientString() const{
    return a1.asString() + ", " + a2.asString() + ", " + a3.asString() + ", " + a4.asString() + ", " + a6.asString();
}

bool pAdicValuationEqualsZero(Rational rational, int prime){
    //The pAdic valuation will be 0 whenever the numerator and denominator both are not divisible by p in lowest terms.
    return (rational.getNumerator() % prime != 0) && (rational.getDenominator() % prime != 0);
}

bool pAdicValuationGreaterThanZero(Rational rational, int prime){
    //The pAdic valuation will be greater than 0 whenever the numerator is divisible by p in lowest terms.
    return rational.getNumerator() % prime == 0;
}

string ReductionTypeToString(ReductionType redType){
    switch(redType){
        case SINGULAR:
            return "Singular";
            break;
        case GOOD:
            return "Good";
            break;
        case MULTIPLICATIVE:
            return "Multiplicative";
            break;
        case ADDITIVE:
            return "Additive";
            break;
        default:
            return "Not Defined";
    }
}