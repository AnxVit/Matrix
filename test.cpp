#include "test.h"
#include "matrix_utilities.h"
#include <iostream>

void test_const() {
	linalg::Matrix m1{ 2,2 };
	//std::cout << m.rows() << m.columns();
	linalg::Matrix m2 = linalg::Matrix{1,2,3,4,5};
	std::cout << m2;

}