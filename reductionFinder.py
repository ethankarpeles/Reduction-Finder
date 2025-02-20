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


def getEquation(a1, a2, a3, a4, a6, p):
    equationString = "y^2"
    if a1 % p != 0:
        equationString = equationString + " + " + (str(a1) if a1 % p != 1 else "") + "xy"
    if a3 % p != 0:
        equationString = equationString + " + " + (str(a3) if a3 % p != 1 else "") + "y"
    equationString = equationString + " = x^3"
    if a2 % p != 0:
        equationString = equationString + " + " + (str(a2) if a2 % p != 1 else "") + "x^2"
    if a4 % p != 0:
        equationString = equationString + " + " + (str(a4) if a4 % p != 1 else "") + "x"
    if a6 % p != 0:
        equationString = equationString + " + " + str(a6)
    equationString = equationString + " (mod " + str(p) + ")\n"
    return equationString


p = 7
lower = 0 % p
upper = 6 % p
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