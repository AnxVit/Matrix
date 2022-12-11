#pragma once

#include "matrix.h"
#include <iostream>

namespace linalg {
	template <typename T>
	std::ostream& operator<<(std::ostream& out, const Matrix<T>& mat);
}

#include "matrix_utilities.hpp"