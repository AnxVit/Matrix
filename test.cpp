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

void test_equal(){
	linalg::Matrix<int> m = { 1, 2, 3, 4};
	linalg::Matrix<double> m1 = { 10.1, 9.1, 8.1, 7.1};
	std::cout << m + m1;
}