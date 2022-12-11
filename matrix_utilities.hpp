#pragma once

#include <iomanip>
#include <sstream>

template <typename T>
static size_t compute_width(const linalg::Matrix<T>& mat, bool flag){
	std::stringstream s_str;
	size_t width = 0;
	std::pair<int, int> length;
	length.first = flag ? 0 : 1;
	length.second = flag ? 1: mat.columns();

	for (size_t i = 0; i < mat.rows(); ++i) {
		for (size_t j = length.first; j < length.second; ++j) {
			s_str << mat(i, j);
			if (s_str.str().size() > width) {
				width = s_str.str().size();
			}
			s_str.str("");
		}
	}
	return width;
}

template <typename T>
std::ostream& linalg::operator<<(std::ostream& out, const Matrix<T>& mat) {
	size_t width_f = compute_width(mat, true);
	size_t width_m = compute_width(mat, false);
	if (mat.empty()) {
		out << "Empty";
	}
	else {
		for (size_t i = 0; i < mat.rows(); ++i) {
			out << '|';
			out << ' ' << std::setw(width_f) << mat(i, 0);
			for (size_t j = 1; j < mat.columns(); ++j) {
				out << ' ' << std::setw(width_f) << mat(i, j);
			}
			out << "|\n";
		}
	}
	return out;
}

