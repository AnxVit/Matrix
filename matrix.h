#pragma once

#include <stdexcept>
#include <initializer_list>

namespace linalg {
	template <typename T>
	class Proxy;

	template <typename T = double>
	class Matrix {
	public:
		Matrix() noexcept = default;
		Matrix(size_t rows, size_t columns = 1);
		Matrix(const Matrix& mat);
		template <typename T2>
		Matrix(const Matrix<T2>& mat);
		Matrix(Matrix&& mat) noexcept;
		template <typename T2>
		Matrix(std::initializer_list<std::initializer_list<T2>> list);
		template <typename T2>
		Matrix(std::initializer_list<T2> list);
		~Matrix() noexcept;

		size_t rows() const noexcept { return m_rows; }
		size_t columns() const noexcept { return m_columns; }
		size_t capacity() const noexcept { return m_capacity; }
		bool empty() const noexcept { return m_rows == 0 ; }
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

		Matrix& operator+= (const Matrix& mat);
		template <typename T>
		Matrix& operator+= (const Matrix<T>& mat);
		Matrix& operator-= (const Matrix& mat);
		template <typename T>
		Matrix& operator-= (const Matrix<T>& mat);
		Matrix& operator*= (const Matrix& mat);
		template <typename T>
		Matrix& operator*= (const Matrix<T>& mat);
		Matrix& operator*= (const T& val);
		template <typename T>
		Matrix& operator*= (const T& val);
		
		const Proxy<T> operator[](size_t r) const;
		Proxy<T> operator[](size_t r);
	private:
		T* m_ptr = nullptr;
		size_t m_rows{0};
		size_t m_columns{0};
		size_t m_capacity{0};
	private:
		template <typename T2> void copy_constructor(const Matrix<T2>& mat);
	};

	template <typename T1, typename T2>
	auto operator+(const Matrix<T1>& mat1, const Matrix<T2>& mat2) {
		Matrix<decltype(T1() + T2())> result = mat1;
		return result += mat2;
	}
	template <typename T1, typename T2>
	auto operator-(const Matrix<T1>& mat1, const Matrix<T2>& mat2) {
		Matrix<decltype(T1() + T2())> result = mat1;
		return result -= mat2;
	}
	template <typename T1, typename T2>
	auto operator*(const Matrix<T1>& mat1, const Matrix<T2>& mat2) {
		Matrix<decltype(T1() * T2())> result = mat1;
		return result *= mat2;
	}
	template <typename T1, typename T2>
	auto operator*(const Matrix<T1>& mat, const T2& val) {
		Matrix<decltype(T1()* T2())> result = mat;
		return result *= val;
	}
	template <typename T1, typename T2>
	auto operator*(const T1& val, const Matrix<T2>& mat) {
		return mat * val;
	}

	struct MatrixException: public std::exception {
		MatrixException(const char* str) : std::exception(str){}
	};
	struct IncorrectDimensions: public MatrixException {
		IncorrectDimensions() : MatrixException("Incorrect dimenssions") {}
	};
	struct OutOfRangeException: public MatrixException {
		OutOfRangeException() : MatrixException("Out of range exception") {}
	};
	
	template <typename T>
	class Proxy{
	public:
		Proxy(T* mat, size_t columns): m_row(mat), m_size(columns) {}
		T& operator[](size_t c) {
			if (c < 0 || c > m_size - 1) {
				throw OutOfRangeException();
			}
			return *(m_row + c);
		}
		T operator[](size_t c) const{
			if (c < 0 || c > m_size - 1) {
				throw OutOfRangeException();
			}
			return *(m_row + c);
		}
	private:
		T* m_row;
		size_t m_size;
	};
}
#include "matrix.hpp"