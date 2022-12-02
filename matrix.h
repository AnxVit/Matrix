#pragma once

namespace linalg {
	class Matrix {
		size_t rows() const noexcept { return m_rows; }
		size_t culumns() const noexcept { return m_columns; }
		bool empty() const noexcept { return m_rows == 0; }
		void reshape(size_t rows, size_t columns);
	private:
		double* m_ptr = nullptr;
		size_t m_rows;
		size_t m_columns;
	};
}