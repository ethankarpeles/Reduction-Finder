using namespace std;
#include <numeric>
#include <stdexcept>
#include <iostream>
#include <limits>
#include <string>
#include "rational.h"

Rational::Rational(int numerator, int denominator){
    if(denominator == 0){
        throw std::runtime_error("Error: cannot divide by zero.");
    }
    this->numerator = numerator;
    this->denominator = denominator;
    this->reduce();
}

Rational::Rational(int wholeNumber){
    this->numerator = wholeNumber;
    this->denominator = 1;
    this->reduce();
}

int Rational::getNumerator() const{
    return numerator;
}

int Rational::getDenominator() const{
    return denominator;
}

float Rational::asFloat() const{
    return static_cast<float>(numerator) / static_cast<float>(denominator);
}

string Rational::asString() const{
    if( this->getDenominator() == 1 ){
        return to_string(this->getNumerator());
    }
    else{
        return "(" + to_string(this->getNumerator()) + "/" + to_string(this->getDenominator());
    }
}

void Rational::reduce(){
    int NumDenGCD = gcd(numerator, denominator);
    numerator = numerator / NumDenGCD;
    denominator = denominator / NumDenGCD;
    //If the number is negative, make sure only the numerator is negative.
    //If numerator and denominator are both negative, then the result is positive.
    if( (denominator < 0 && numerator > 0) || (denominator < 0 && numerator < 0)){
        numerator = numerator * -1;
        denominator = denominator * -1;
    }
}

//Rational operator Rational
Rational Rational::operator+(const Rational& other) const{
    return Rational(this->getNumerator() * other.getDenominator() + other.getNumerator() * this->getDenominator(), this->getDenominator() * other.getDenominator());
}
Rational Rational::operator*(const Rational& other) const{
    return Rational(this->getNumerator() * other.getNumerator(), this->getDenominator() * other.getDenominator());
}
Rational Rational::operator/(const Rational& other) const{
    if(other.getNumerator() == 0){
        throw std::runtime_error("Error: cannot divide by zero.");
    }
    //To divide, just multiply by the reciprical.
    return *this * Rational(other.getDenominator(), other.getNumerator());
}
Rational Rational::operator-() const{
    //Just flip the sign of the numerator.
    return Rational(-(this->getNumerator()), this->getDenominator());
}

//Negative rationals
Rational Rational::operator-(const Rational& other) const{
    //To subtract, just add the negative.
    return *this + (-other);
}

//Rational operator int
Rational Rational::operator+(int num) const {
    return Rational(this->getNumerator() + (num * this->getDenominator()), this->getDenominator());
}
Rational Rational::operator*(int num) const {
    return Rational(this->getNumerator() * num, this->getDenominator());
}
Rational Rational::operator/(int num) const {
    if(num == 0){
        throw std::runtime_error("Error: cannot divide by zero.");
    }
    return Rational(this->getNumerator(), this->getDenominator() * num);
}
Rational Rational::operator-(int num) const {
    return *this + (-num);
}

//Rational inequality Rational
bool Rational::operator==(const Rational& other) const{
    return (this->getNumerator() == other.getNumerator()) && (this->getDenominator() == other.getDenominator());
}
bool Rational::operator!=(const Rational& other) const{
    return !(*this == other);
}
bool Rational::operator<(const Rational& other) const{
    return this->asFloat() < other.asFloat();
}
bool Rational::operator<=(const Rational& other) const{
    return (*this == other || *this < other);
}
bool Rational::operator>(const Rational& other) const{
    return this->asFloat() > other.asFloat();
}
bool Rational::operator>=(const Rational& other) const{
    return (*this == other || *this > other);
}

//Rational inequality int
bool Rational::operator==(int num) const{
    return *this == Rational(num);
}
bool Rational::operator!=(int num) const{
    return *this != Rational(num);
}
bool Rational::operator<(int num) const{
    return *this < Rational(num);
}
bool Rational::operator<=(int num) const{
    return *this <= Rational(num);
}
bool Rational::operator>(int num) const{
    return *this > Rational(num);
}
bool Rational::operator>=(int num) const{
    return *this >= Rational(num);
}

//Rational +-,*=,/=,-= Rational
Rational& Rational::operator+=(const Rational& other){
    *this = *this + other;
    return *this;
}
Rational& Rational::operator*=(const Rational& other){
    *this = *this * other;
    return *this;
}
Rational& Rational::operator/=(const Rational& other){
    if(other == 0){
        throw std::runtime_error("Error: cannot divide by zero.");
    }
    *this = *this / other;
    return *this;
}
Rational& Rational::operator-=(const Rational& other){
    *this = *this - other;
    return *this;
}

//Rational +-,*=,/=,-= int
Rational& Rational::operator+=(int num){
    *this = *this + num;
    return *this;
}
Rational& Rational::operator*=(int num){
    *this = *this * num;
    return *this;
}
Rational& Rational::operator/=(int num){
    if(num == 0){
        throw std::runtime_error("Error: cannot divide by zero.");
    }
    *this = *this / num;
    return *this;
}
Rational& Rational::operator-=(int num){
    *this = *this - num;
    return *this;
}

//Rational ++, --
Rational& Rational::operator++(){
    *this = *this + 1;
    return *this;
}
Rational Rational::operator++(int){
    Rational old = *this;
    operator++();
    return old;
}
Rational& Rational::operator--(){
    *this = *this - 1;
    return *this;
}
Rational Rational::operator--(int){
    Rational old = *this;
    operator--();
    return old;
}

//Non-member functions to handle int operator Rational
Rational operator+(int num, const Rational& obj) {
    //Commutitive
    return obj + num;
}
Rational operator*(int num, const Rational& obj) {
    //Commutitive
    return obj * num;
}
Rational operator/(int num, const Rational& obj) {
    if(obj == 0){
        throw runtime_error("Error: cannot divide by zero.");
    }
    //Just multiply by reciprical
    return Rational(obj.getDenominator() * num, obj.getNumerator());
}
Rational operator-(int num, const Rational& obj) {
    //Just add the negative
    return num + (-obj);
}

//Non-member functions to handle int inequality Rational
bool operator==(int num, const Rational& obj){
    return Rational(num) == obj;
}
bool operator!=(int num, const Rational& obj){
    return Rational(num) != obj;
}
bool operator<(int num, const Rational& obj){
    return Rational(num) < obj;
}
bool operator<=(int num, const Rational& obj){
    return Rational(num) <= obj;
}
bool operator>(int num, const Rational& obj){
    return Rational(num) > obj;
}
bool operator>=(int num, const Rational& obj){
    return Rational(num) >= obj;
}

//Non-member function to handle ostream
ostream& operator<<(ostream& os, const Rational& obj){
    os << obj.asString();
    return os;
}