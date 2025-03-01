#ifndef ELLIPTIC_H
#define ELLIPTIC_H

#include "rational.h"
#include <string>

enum ReductionType {
    SINGULAR,
    GOOD,
    MULTIPLICATIVE,
    ADDITIVE
};

class EllipticCurve {
    public:
        //Constructor
        EllipticCurve(Rational a1, Rational a2, Rational a3, Rational a4, Rational a6);
        //Functions
        Rational getDeterminant() const;
        Rational getC4() const;
        Rational getJ() const;
        ReductionType getReductionType(int modulus) const;
        string getEquation() const;
        string getCoefficientString() const;
    private:
        //Coefficients
        Rational a1 = 0;
        Rational a2 = 0;
        Rational a3 = 0;
        Rational a4 = 0;
        Rational a6 = 0;
};

bool pAdicValuationEqualsZero(Rational rational, int prime);
bool pAdicValuationGreaterThanZero(Rational rational, int prime);
string ReductionTypeToString(ReductionType redType);

#endif