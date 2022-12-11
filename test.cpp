#include "test.h"
#include "matrix_utilities.h"
#include <iostream>

void test_const() {
	linalg::Matrix<double> m1 = { {100000000.1, 4.2},{4.1, 234.1}, {34.1, 3.1} };
	std::cout << m1;
}

void test_clear() {
	linalg::Matrix<char> m = { 'a', 'b', 'c', 'd' };
	std::cout << m;
	m.clear();
	std::cout << m;
}