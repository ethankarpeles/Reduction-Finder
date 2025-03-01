using namespace std;
#include <iostream>
#include <list>
#include <numeric>
#include <fstream>
#include "elliptic.h"

list<int> getPrimesBeforeVal(int primeUpper){
    //Use the Sieve of Eratosthenes to find all primes less than primeUpper
    list<int> primes(primeUpper - 1);
    iota(primes.begin(), primes.end(), 2);
    for(list<int>::iterator prime = primes.begin(); *prime * *prime < primeUpper; ++prime){
        for(list<int>::iterator it = primes.begin(); it != primes.end();){
            //If "it" is divisible by "prime" and they aren't equal, then erase "it"
            if(*it != *prime && *it % *prime == 0){
                it = primes.erase(it);
            }
            else{
                ++it;
            }
        }
    }
    return primes;
}

int main() {
    string filename = "manyMultCurves.txt";

    int lower = 0;
    int upper = 40;
    int primeUpper = 40;
    if(primeUpper < 11){
        cout << "primeUpper should be strictly greater than 11." << endl;
        return 0;
    }
    list<int> primes = getPrimesBeforeVal(primeUpper);
    //Erase 2, 3, 5, and 7 from the list of primes
    primes.erase(primes.begin());
    primes.erase(primes.begin());
    primes.erase(primes.begin());
    primes.erase(primes.begin());
    list<EllipticCurve> eList;

    cout << "Creating inital list" << endl;
    //Create the initial list using the first element of primes
    for(Rational a1 = lower; a1 <= upper; a1++){
        for(Rational a2 = lower; a2 <= upper; a2++){
            for(Rational a3 = lower; a3 <= upper; a3++){
                for(Rational a4 = lower; a4 <= upper; a4++){
                    for(Rational a6 = lower; a6 <= upper; a6++){
                        EllipticCurve el = EllipticCurve(a1, a2, a3, a4, a6);
                        if(el.getReductionType( *(primes.begin()) ) == MULTIPLICATIVE){
                            eList.push_back(el);
                        }
                    }
                }
            }
        }
        cout << a1 << endl;
    }

    //Erase 11 from the list of primes
    primes.erase(primes.begin());

    //Start removing elements if they aren't multiplicative for a prime
    for(list<int>::iterator prime = primes.begin(); prime != primes.end(); ++prime){
        cout << "Checking p = " << *prime << endl;
        for(list<EllipticCurve>::iterator el = eList.begin(); el != eList.end();){
            if( (*el).getReductionType( *prime ) != MULTIPLICATIVE ){
                el = eList.erase(el);
            }
            else{
                ++el;
            }
        }
    }

    ofstream outputFile;
    outputFile.open(filename); // Open the file
    if (outputFile.is_open()) {
        //Print out all of the curves
        for(list<EllipticCurve>::iterator el = eList.begin(); el != eList.end(); ++el){
            outputFile << "Append(~ElList, EllipticCurve([" << (*el).getCoefficientString() << "]));" << endl;
        }
    }
    else{
        cerr << "Error opening file: " << filename << endl;
        return 1; 
    }
    outputFile.close(); // Close the file
    return 0;
}