#pragma once

#include <utility>
#include "matrix.h"

template<typename T>
linalg::Matrix<T>::Matrix(size_t rows, size_t columns) {
	if (!rows || !columns) return;
	T* tmp_ptr = reinterpret_cast<T*>(operator new(sizeof(T) * rows * columns));
	T* cur_ptr = tmp_ptr;
	try {
		while (cur_ptr != tmp_ptr + rows * columns) {
			new(cur_ptr) T();
			++cur_ptr;
		}
	}
	catch (...) {
		for (T* ptr = tmp_ptr; ptr != cur_ptr; ++ptr)
			ptr->~T();
		delete reinterpret_cast<void*>(tmp_ptr);
		throw;
	}
	m_ptr = tmp_ptr;
	m_rows = rows;
	m_columns = columns;
	m_capacity = rows * columns;
}

template <typename T>
linalg::Matrix<T>::Matrix(const Matrix& mat) {
	copy_constructor(mat);
}

template <typename T>
template <typename T2>
linalg::Matrix<T>::Matrix(const Matrix<T2>& mat) {
	copy_constructor(mat);
}

template <typename T>
linalg::Matrix<T>::Matrix(Matrix&& mat) noexcept
	: m_ptr(mat.m_ptr), m_rows(mat.m_rows), 
	m_columns(mat.m_columns), m_capacity(mat.m_capacity)
{
	mat.m_ptr = nullptr;
	mat.m_rows = mat.m_columns = 0;
}

template<typename T>
linalg::Matrix<T>::~Matrix() noexcept {
	for (T* ptr = m_ptr; ptr != m_ptr + m_rows * m_columns; ++ptr)
		ptr->~T();
	delete reinterpret_cast<void*>(m_ptr);
}


template <typename T>
template <typename T2>
linalg::Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T2>> list) {
	if (!list.size()) return;
	T* tmp_ptr = reinterpret_cast<T*>(operator new(sizeof(T) * list.size() * (*list.begin()).size()));
	T* cur_ptr = tmp_ptr;
	try {
		for (std::initializer_list<T> row : list) {
			using list_it = typename std::initializer_list<T2>::iterator;
			for (list_it it = row.begin(); it != row.end(); ++it, ++cur_ptr) {
				new(cur_ptr) T(*it);
			}
		}
	}
	catch (...) {
		for (T* ptr = tmp_ptr; ptr != cur_ptr; ++ptr)
			ptr->~T();
		delete reinterpret_cast<void*>(tmp_ptr);
		throw;
	}
	m_ptr = tmp_ptr;
	m_rows = list.size();
	m_columns = (*list.begin()).size();
	m_capacity = list.size() * (*list.begin()).size();
}

template <typename T>
template <typename T2>
linalg::Matrix<T>::Matrix(std::initializer_list<T2> list) {
	if (!list.size()) return;
	T* tmp_ptr = reinterpret_cast<T*>(operator new(sizeof(T) * list.size()));
	T* cur_ptr = tmp_ptr;
	try {
		using list_it = typename std::initializer_list<T2>::iterator;
		for (list_it it = list.begin(); it != list.end(); ++it, ++cur_ptr) {
			new(cur_ptr) T(*it);
		}
	}
	catch (...) {
		for (T* ptr = tmp_ptr; ptr != cur_ptr; ++ptr)
			ptr->~T();
		delete reinterpret_cast<void*>(tmp_ptr);
		throw;
	}
	m_ptr = tmp_ptr;
	m_rows = list.size();
	m_columns = 1;
	m_capacity = list.size();
}

template <typename T>
void linalg::Matrix<T>::reshape(size_t rows, size_t columns) {
	if (rows * columns == m_rows * m_columns) {
		m_rows = rows;
		m_columns = columns;
	}
	else {
		throw IncorrectDimensions();
	}
}

template <typename T>
void linalg::Matrix<T>::reserve(size_t capacity) {
	if (m_capacity >= capacity) return;

	T* tmp_ptr = reinterpret_cast<T*>(operator new(sizeof(T) * capacity));
	T* cur_ptr = tmp_ptr;
	try {
		for (T* ptr = m_ptr; ptr != m_ptr + m_rows * m_columns; ++ptr, ++cur_ptr) {
			new(cur_ptr) T(*ptr);
		}
	}
	catch (...) {
		for (T* ptr = tmp_ptr; ptr != cur_ptr; ++ptr)
			ptr->~T();
		delete reinterpret_cast<void*>(tmp_ptr);
		throw;
	}
	for (T* ptr = m_ptr; ptr != m_ptr + m_rows * m_columns; ++ptr) {
		ptr->~T();
	}
	delete reinterpret_cast<void*> (m_ptr);
	m_ptr = tmp_ptr;
	m_capacity = capacity;
}

template <typename T>
void linalg::Matrix<T>::shrink_to_fit() {
	if (m_capacity == m_rows * m_columns) return;
	*this = Matrix(*this);
}

template <typename T>
template <typename T2>
linalg::Matrix<T>& linalg::Matrix<T>::operator=(const Matrix<T2>& mat) {
	if (mat.m_columns * mat.m_rows > m_capacity) {
		return *this = Matrix(mat);
	}
	T* self = m_ptr;
	T2* other = mat.m_ptr;
	for (; self != m_ptr + std::min(m_rows * m_columns, mat.m_rows * mat.m_columns); ++self, ++other) {
		*self = *other;
	}
	if (m_rows * m_columns < mat.m_rows * mat.m_columns) {
		try {
			for (; self != m_ptr + mat.m_rows * mat.m_columns; ++self, ++other) {
				new(self) T(*other);
			}
		}
		catch (...) {
			for (T* ptr = m_ptr + m_rows * m_columns; ptr != self; ++ptr) {
				ptr->~T();
			}
			throw;
		}
	}
	else {
		for (; self != m_ptr + m_rows * m_columns; ++self) {
			self->~T();
		}
	}
	m_rows = mat.m_rows;
	m_columns = mat.m_columns;
	return *this;
}

template<typename T>
linalg::Matrix<T>& linalg::Matrix<T>::operator=(const Matrix& mat) {
	if (&mat == this) {
		return *this;
	}
	return operator=<T>(mat);
}


template <typename T>
linalg::Matrix<T>& linalg::Matrix<T>::operator=(Matrix&& mat) noexcept{
	if (&mat == this)
		return *this;
	delete m_ptr;

	m_ptr = mat.m_ptr;
	mat.m_ptr = nullptr;
	mat.m_rows = mat.m_columns = 0;

	return *this;
}

template <typename T>
T& linalg::Matrix<T>::operator()(size_t row, size_t col) {
	if (col < 0 || col > m_columns - 1 || row < 0 || row > m_rows - 1) {
		throw OutOfRangeException();
	}
	return m_ptr[row * m_columns + col];
}

template <typename T>
const T& linalg::Matrix<T>::operator()(size_t row, size_t col) const{
	if (col < 0 || col > m_columns - 1 || row < 0 || row > m_rows - 1) {
		throw OutOfRangeException();
	}
	return m_ptr[row * m_columns + col];
}


template<typename T>
void linalg::Matrix<T>::clear() noexcept {
	for (T* ptr = m_ptr; ptr != m_ptr + m_rows * m_columns; ++ptr)
		ptr->~T();
	m_rows = m_columns = 0;
}


template<typename T>
template<typename T2>
void linalg::Matrix<T>::copy_constructor(const Matrix<T2>& mat) {
	if (!mat.m_rows) return;
	T* tmp_ptr = reinterpret_cast<T*>(operator new(sizeof(T) * mat.m_rows * mat.m_columns));
	T* cur_ptr = tmp_ptr;
	try {
		for (T2* ptr = mat.m_ptr; ptr != mat.m_ptr + mat.m_rows * mat.m_columns; ++ptr, ++cur_ptr) {
			new(cur_ptr) T(*ptr);
		}
	}
	catch (...) {
		for (T* ptr = tmp_ptr; ptr != cur_ptr; ++ptr)
			ptr->~T();
		delete reinterpret_cast<void*>(tmp_ptr);
		throw;
	}
	m_ptr = tmp_ptr;
	m_rows = mat.m_rows;
	m_columns = mat.m_columns;
	m_capacity = mat.m_rows * mat.m_columns;
}

template <typename T>
template <typename T2>
linalg::Matrix<T>& linalg::Matrix<T>::operator+=(const Matrix<T2>& mat) {
	if (m_rows != mat.m_rows || m_columns != mat.m_columns) throw IncorrectDimensions();
	T* self = m_ptr;
	T2* other = mat.m_ptr;

	for (; self != m_ptr + mat.m_rows * mat.m_columns; ++self, ++other) {
		*self += *other;
	}
	return *this;
}

template<typename T>
linalg::Matrix<T>& linalg::Matrix<T>::operator+=(const Matrix& mat) {
	return operator+=<T>(mat);
}

template <typename T>
template <typename T2>
linalg::Matrix<T>& linalg::Matrix<T>::operator-=(const Matrix<T2>& mat) {
	if (m_rows != mat.m_rows || m_columns != mat.m_columns) throw IncorrectDimensions();
	T* self = m_ptr;
	T2* other = mat.m_ptr;

	for (; self != m_ptr + mat.m_rows * mat.m_columns; ++self, ++other) {
		*self -= *other;
	}
	return *this;
}

template<typename T>
linalg::Matrix<T>& linalg::Matrix<T>::operator-=(const Matrix& mat) {
	return operator-=<T>(mat);
}

template <typename T>
template <typename T2>
linalg::Matrix<T>& linalg::Matrix<T>::operator*=(const Matrix<T2>& mat) {
	if (m_columns != mat.m_rows) throw IncorrectDimensions();
	T* tmp_ptr = reinterpret_cast<T*>(operator new(sizeof(T) * m_rows * mat.m_columns));
	T* cur_ptr = tmp_ptr;
	try {
		size_t i = 0;
		while(i != m_rows * mat.m_columns){
			decltype(T() * T2()) val = T() * T2();
			for (size_t j = 0; j < m_columns; ++j) {
				val += (*this)(i / mat.m_columns, j) * mat(j, i % mat.m_columns);
			}
			new(cur_ptr + i) T(val);
			++i;
		}
	}
	catch (...) {
		for (T* ptr = tmp_ptr; ptr != cur_ptr; ++ptr)
			ptr->~T();
		delete reinterpret_cast<void*>(tmp_ptr);
		throw;
	}
	delete m_ptr;
	m_ptr = tmp_ptr;
	m_columns = mat.m_columns;
	return *this;
}

template<typename T>
linalg::Matrix<T>& linalg::Matrix<T>::operator*=(const Matrix& mat) {
	return operator*=<T>(mat);
}

template <typename T>
template <typename T2>
linalg::Matrix<T>& linalg::Matrix<T>::operator*=(const T2& val) {
	T* self = m_ptr;
	for (; self != m_ptr + m_rows * m_columns; ++self) {
		*self *= val;
	}
	return *this;
}

template<typename T>
linalg::Matrix<T>& linalg::Matrix<T>::operator*=(const T& val) {
	return operator*=<T>(val);
}