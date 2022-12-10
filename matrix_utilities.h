#pragma once

#include "matrix.h"
#include <iostream>

namespace linalg {
	std::ostream& operator<<(std::ostream& out, const Matrix& mat);
}

#include "matrix_utilities.hpp"