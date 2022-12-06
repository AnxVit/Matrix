#pragma once

namespace linalg {
	class Matrix {
		Matrix() noexcept = default;
		Matrix(size_t rows);
		Matrix(size_t rows, size_t columns);

		size_t rows() const noexcept { return m_rows; }
		size_t culumns() const noexcept { return m_columns; }
		size_t capacity() const noexcept { return m_capacity; }
		bool empty() const noexcept { return m_rows == 0; }
		void reshape(size_t rows, size_t columns);
		void reserve(size_t n);
		void clear() noexcept { m_rows = 0; m_columns = 0; }
	private:
		double* m_ptr = nullptr;
		size_t m_rows{0};
		size_t m_columns{0};
		size_t m_capacity{0};
	};
}
#include "matrix.hpp"