#! /usr/bin/env python

import openturns as ot

ot.TESTPREAMBLE()


# TEST NUMBER ZERO : DEFAULT CONSTRUCTOR AND STRING CONVERTER
print("test number zero : default constructor and string converter")

# Default constructor
symmetricTensor0 = ot.SymmetricTensor()

# String converter
print("symmetricTensor0 = ", repr(symmetricTensor0))

# TEST NUMBER ONE : CONSTRUCTOR WITH SIZE, OPERATOR() AND STRING CONVERTER
print("test number one : constructor with size, operator() and string converter")

# Constructor with size
symmetricTensor1 = ot.SymmetricTensor(2, 3)

# Check operator() methods
symmetricTensor1[0, 0, 0] = 1.0
symmetricTensor1[1, 0, 0] = 2.0
symmetricTensor1[1, 1, 0] = 3.0
symmetricTensor1[0, 0, 1] = 4.0
symmetricTensor1[1, 0, 1] = 5.0
symmetricTensor1[1, 1, 1] = 6.0
symmetricTensor1[0, 0, 2] = 7.0
symmetricTensor1[1, 0, 2] = 8.0
symmetricTensor1[1, 1, 2] = 9.0

# String converter
print("symmetricTensor1 = ", repr(symmetricTensor1))
print(
    "values = %.6f" % symmetricTensor1[0, 0, 0],
    "  %.6f" % symmetricTensor1[0, 1, 0],
    "  %.6f" % symmetricTensor1[1, 0, 0],
    "  %.6f" % symmetricTensor1[1, 1, 0],
    "  %.6f" % symmetricTensor1[0, 0, 1],
    "  %.6f" % symmetricTensor1[0, 1, 1],
    "  %.6f" % symmetricTensor1[1, 0, 1],
    "  %.6f" % symmetricTensor1[1, 1, 1],
    "  %.6f" % symmetricTensor1[0, 0, 2],
    "  %.6f" % symmetricTensor1[0, 1, 2],
    "  %.6f" % symmetricTensor1[1, 0, 2],
    "  %.6f" % symmetricTensor1[1, 1, 2],
)

# TEST NUMBER TWO : COPY CONSTRUCTOR AND STRING CONVERTER
print("test number two : copy constructor and string converter")

# Copy constructor
symmetricTensor2 = ot.SymmetricTensor(symmetricTensor1)

# String converter
print("symmetricTensor2 = ", repr(symmetricTensor2))

# TEST NUMBER THREE : GET DIMENSIONS METHODS
print("test number three : get dimensions methods")

# Get dimension methods
print("symmetricTensor1's nbRows = ", symmetricTensor1.getNbRows())
print("symmetricTensor1's nbColumns = ", symmetricTensor1.getNbColumns())
print("symmetricTensor1's nbSheets = ", symmetricTensor1.getNbSheets())

# TEST NUMBER FOUR : ASSIGNMENT METHOD
print("test number four : assignment method")
# no sense with python

# TEST NUMBER FIVE : ISEMPTY METHOD
print("test number five : isEmpty method")

# Check method isEmpty
symmetricTensor5 = ot.SymmetricTensor()
symmetricTensor6 = ot.SymmetricTensor()
print("symmetricTensor1 is empty = ", symmetricTensor1.isEmpty())
print("symmetricTensor0 is empty = ", symmetricTensor0.isEmpty())
print("symmetricTensor5 is empty = ", symmetricTensor5.isEmpty())
print("symmetricTensor6 is empty = ", symmetricTensor6.isEmpty())

# TEST NUMBER SIX : GETSHEET AND SETSHEET METHODS
print("symmetricTensor1 = ", repr(symmetricTensor1))

sheet1 = symmetricTensor1.getSheet(1)
print("symmetricTensor1.getSheet(1) = ", repr(sheet1))

sheet2 = ot.SymmetricMatrix(2)
sheet2[0, 0] = 0.4
sheet2[1, 0] = 0.5
sheet2[1, 1] = 0.6
print("sheet2 = ", repr(sheet2))
symmetricTensor1.setSheet(1, sheet2)
print("symmetricTensor1 = ", repr(symmetricTensor1))
