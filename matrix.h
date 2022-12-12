#pragma once

#include <initializer_list>

namespace linalg {
	template <typename T = double>
	class Matrix {
	public:
		Matrix() noexcept = default;
		Matrix(size_t rows, size_t columns = 1);
		Matrix(const Matrix& mat);
		template <typename T2> Matrix(const Matrix<T2>& mat);
		Matrix(Matrix&& mat) noexcept;
		Matrix(std::initializer_list<std::initializer_list<T>> values);
		Matrix(std::initializer_list<T> list);
		//~Matrix() noexcept;

		size_t rows() const noexcept { return m_rows; }
		size_t columns() const noexcept { return m_columns; }
		size_t capacity() const noexcept { return m_capacity; }
		bool empty() const noexcept { return m_rows == 0; }
		void reshape(size_t rows, size_t columns);
		void reserve(size_t n);
		void shrink_to_fit();
		void clear() noexcept;

		Matrix& operator=(const Matrix& mat);
		template <typename T2> 
		Matrix& operator=(const Matrix<T2>& mat);
		template <typename T2> friend class Matrix;
		Matrix& operator=(Matrix&& mat) noexcept;
		T& operator()(size_t row, size_t col);
		const T& operator()(size_t row, size_t col) const;

		template <typename T>
		Matrix& operator+= (const Matrix<T>& mat);
	private:
		T* m_ptr = nullptr;
		size_t m_rows{0};
		size_t m_columns{0};
		size_t m_capacity{0};
	private:
		template <typename T2> void copy_constructor(const Matrix<T2>& mat);
	};
}
#include "matrix.hpp"