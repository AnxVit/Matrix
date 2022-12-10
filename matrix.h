#pragma once

#include <initializer_list>

namespace linalg {
	class Matrix {
	public:
		Matrix() noexcept = default;
		Matrix(size_t rows, size_t columns = 1);
		Matrix(const Matrix& mat);
		Matrix(Matrix&& mat) noexcept;
		Matrix(std::initializer_list<std::initializer_list<double>> values);
		Matrix(std::initializer_list<double> list);

		size_t rows() const noexcept { return m_rows; }
		size_t columns() const noexcept { return m_columns; }
		size_t capacity() const noexcept { return m_capacity; }
		bool empty() const noexcept { return m_rows == 0; }
		void reshape(size_t rows, size_t columns);
		void reserve(size_t n);
		void shrink_to_fit();
		void clear() noexcept { m_rows = 0; m_columns = 0; }

		Matrix& operator=(const Matrix& mat);
		Matrix& operator=(Matrix&& mat) noexcept;
		double& operator()(int row, int col);
		double operator()(int row, int col) const;
	private:
		double* m_ptr = nullptr;
		size_t m_rows{0};
		size_t m_columns{0};
		size_t m_capacity{0};
	};
}
#include "matrix.hpp"