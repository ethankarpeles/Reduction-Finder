from enum import Enum


class ReductionType(Enum):
    SINGULAR = 1
    GOOD = 2
    MULTIPLICATIVE = 3
    ADDITIVE = 4


def getReductionType(a1, a2, a3, a4, a6, p):
    b2 = a1*a1 + 4*a2
    b4 = 2*a4 + a1*a3
    b6 = a3*a3 + 4*a6
    b8 = a1*a1*a6 + 4*a2*a6 - a1*a3*a4 + a2*a3*a3 - a4*a4

    c4 = b2*b2 - 24*b4
    delta = - b2*b2*b8 - 8*b4*b4*b4 - 27*b6*b6 + 9*b2*b4*b6

    if delta == 0:
        return ReductionType.SINGULAR
    elif abs(delta) % p != 0:
        return ReductionType.GOOD
    elif abs(c4) % p != 0:
        return ReductionType.MULTIPLICATIVE
    else:
        return ReductionType.ADDITIVE


def getEquation(a1, a2, a3, a4, a6):
    equationString = "y^2"
    if a1 != 0:
        equationString = equationString + " + " + (str(a1) if a1 != 1 else "") + "xy"
    if a3 != 0:
        equationString = equationString + " + " + (str(a3) if a3 != 1 else "") + "y"
    equationString = equationString + " = x^3"
    if a2 != 0:
        equationString = equationString + " + " + (str(a2) if a2 != 1 else "") + "x^2"
    if a4 != 0:
        equationString = equationString + " + " + (str(a4) if a4 != 1 else "") + "x"
    if a6 != 0:
        equationString = equationString + " + " + str(a6) + "\n"
    return equationString



def getPrimesBeforeVal(upperBound):
    #Use the Sieve of Eratosthenes to find all primes less than primeUpper
    primes = list(range(2, upperBound + 1))
    for prime in primes:
        for num in primes:
            #If num is divisible by prime and they aren't equal, then erase num
            if num != prime and num % prime == 0:
                primes.remove(num)
    return primes;

def curveSortByReductionType(lower, upper, p):
    lower = lower % p
    upper = upper % p
    singularFile = open("singular.txt", "w")
    goodFile = open("goodReduction.txt", "w")
    multiplicativeFile = open("multiplicativeReduction.txt", "w")
    additiveFile = open("additiveReduction.txt", "w")
    
    for a1 in range(lower, upper + 1):
        for a2 in range(lower, upper + 1):
            for a3 in range(lower, upper + 1):
                for a4 in range(lower, upper + 1):
                    for a6 in range(lower, upper + 1):
                        redType = getReductionType(a1, a2, a3, a4, a6, p)
                        
                        if redType == ReductionType.SINGULAR:
                            singularFile.write(getEquation(a1, a2, a3, a4, a6, p))
                        elif redType == ReductionType.GOOD:
                            goodFile.write(getEquation(a1, a2, a3, a4, a6, p))
                        elif redType == ReductionType.MULTIPLICATIVE:
                            multiplicativeFile.write(getEquation(a1, a2, a3, a4, a6, p))
                        elif redType == ReductionType.ADDITIVE:
                            additiveFile.write(getEquation(a1, a2, a3, a4, a6, p))

    singularFile.close()
    goodFile.close()
    multiplicativeFile.close()
    additiveFile.close()


def findManyMultCurves(lower, upper, primeUpper):
    if primeUpper < 11:
        print("primeUpper should be strictly greater than 11.")
        return

    #Set primes list to all primes before a value
    primes = getPrimesBeforeVal(primeUpper)
    primes.remove(2)
    primes.remove(3)
    primes.remove(5)
    primes.remove(7)

    manyMultCurvesFile = open("manyMultCurves.txt", "w")
    manyMultCurvesCheckFile = open("manyMultCurvesCheck.txt", "w")
    for a1 in range(lower, upper + 1):
        for a2 in range(lower, upper + 1):
            for a3 in range(lower, upper + 1):
                for a4 in range(lower, upper + 1):
                    for a6 in range(lower, upper + 1):
                        isMultForAllPrimes = True
                        for prime in primes:
                            if getReductionType(a1, a2, a3, a4, a6, prime) != ReductionType.MULTIPLICATIVE:
                                isMultForAllPrimes = False
                        if(isMultForAllPrimes):
                            manyMultCurvesCheckFile.write("Append(~ElList, EllipticCurve([" + str(a1) + ", " + str(a2) + ", " + str(a3) + ", " + str(a4) + ", " + str(a6) + "]));\n")
                            manyMultCurvesFile.write(getEquation(a1, a2, a3, a4, a6))
        print(a1, "out of", upper)
    manyMultCurvesFile.close()
    manyMultCurvesCheckFile.close()

findManyMultCurves(0, 29, 23)