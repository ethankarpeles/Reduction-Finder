#ifndef RATIONAL_H
#define RATIONAL_H
using namespace std;
#include <iostream>
#include <string>

class Rational{
    public:
        //Constructor
        Rational(int numerator, int denominator);
        Rational(int wholeNumber);
        //Getters
        int getNumerator() const;
        int getDenominator() const;
        float asFloat() const;
        string asString() const;
        //Overloaded additon, subtraction, multiplication, and division
        Rational operator+(const Rational& other) const;
        Rational operator*(const Rational& other) const;
        Rational operator/(const Rational& other) const;
        Rational operator-(const Rational& other) const;
        //Rational operator int
        Rational operator+(int num) const;
        Rational operator*(int num) const;
        Rational operator/(int num) const;
        Rational operator-(int num) const;
        //Negate rationals
        Rational operator-() const;
        //Rational inequality Rational
        bool operator==(const Rational& other) const;
        bool operator!=(const Rational& other) const;
        bool operator<(const Rational& other) const;
        bool operator<=(const Rational& other) const;
        bool operator>(const Rational& other) const;
        bool operator>=(const Rational& other) const;
        //Rational inequality int
        bool operator==(int num) const;
        bool operator!=(int num) const;
        bool operator<(int num) const;
        bool operator<=(int num) const;
        bool operator>(int num) const;
        bool operator>=(int num) const;
        //Rational +-,*=,/=,-= Rational
        Rational& operator+=(const Rational& other);
        Rational& operator*=(const Rational& other);
        Rational& operator/=(const Rational& other);
        Rational& operator-=(const Rational& other);
        //Rational +-,*=,/=,-= int
        Rational& operator+=(int num);
        Rational& operator*=(int num);
        Rational& operator/=(int num);
        Rational& operator-=(int num);
        //Rational ++, --
        Rational& operator++();
        Rational operator++(int);
        Rational& operator--();
        Rational operator--(int);
    private:
        int numerator;
        int denominator;
        //Other functions
        void reduce();
};
//int operator Rational
Rational operator+(int num, const Rational& obj);
Rational operator*(int num, const Rational& obj);
Rational operator/(int num, const Rational& obj);
Rational operator-(int num, const Rational& obj);
//int inequality Rational
bool operator==(int num, const Rational& obj);
bool operator!=(int num, const Rational& obj);
bool operator<(int num, const Rational& obj);
bool operator<=(int num, const Rational& obj);
bool operator>(int num, const Rational& obj);
bool operator>=(int num, const Rational& obj);
//For ostream
ostream& operator<<(ostream& os, const Rational& obj);
#endif