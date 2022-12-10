#pragma once

#include "matrix.h"
#include <iostream>

namespace linalg {
	std::ostream& operator<<(std::ostream& out, const Matrix& mat);
}

std::ostream& linalg::operator<<(std::ostream& out, const Matrix& mat) {
	for (size_t i = 0; i < mat.rows(); ++i) {
		for (size_t j = 0; j < mat.columns(); ++j) {
			out << mat(i,j) << ' ';
		}
		out << '\n';
	}
	return out;
}

#include "matrix_utilities.hpp"