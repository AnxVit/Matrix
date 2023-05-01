# Matrix
I decided to create my own Matrix type

## matrix_utilities.h/.hpp
Implementation of operator overload <<.

Compute_with calculates the width between matrix elements

## marix.h/.hpp

The linalg namespace contains the Matrix, MatrixException and Proxy classes.

### Matrix

### MatrixException
Inherited from std::exception

Exceptions:
1. IncorrectDimensions - Incorrect dimenssions
2. OutOfRangeException - Out of range exception

###Proxy
Proxy class created to implement the operator[][]

## test
Some tests to check
