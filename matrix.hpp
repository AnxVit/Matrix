#pragma once

linalg::Matrix::Matrix(size_t rows, size_t columns = 1) {
	m_ptr = new double[rows * columns];
	for (size_t i; i < rows * columns; ++i) {
		m_ptr[i] = double();
	}
	m_rows = rows;
	m_columns = columns;
	m_capacity = rows * columns;
}

linalg::Matrix::Matrix(const Matrix& mat) {
	m_ptr = new double[mat.m_rows * mat.m_columns];
	for (size_t i; i < mat.m_rows * mat.m_columns; ++i) {
		m_ptr[i] = mat.m_ptr[i];
	}
	m_rows = mat.m_rows;
	m_columns = mat.m_columns;
	m_capacity = mat.m_capacity;
}

linalg::Matrix::Matrix(Matrix&& mat) noexcept
	: m_ptr(mat.m_ptr), m_rows(mat.m_rows), 
	m_columns(mat.m_columns), m_capacity(mat.m_capacity)
{
	mat.m_ptr = nullptr;
	mat.m_rows = mat.m_columns = 0;
}

linalg::Matrix::Matrix(std::initializer_list<std::initializer_list<double>> list) {
	m_ptr = new double[(*list.begin()).size() * list.size()];
	size_t i = 0;
	for (std::initializer_list<double> row : list) {
		for (double el : row) {
			m_ptr[i] = el;
			++i;
		}
	}
	m_rows = list.size();
	m_columns = (*list.begin()).size();
	m_capacity = m_rows * m_columns;
}

linalg::Matrix::Matrix(std::initializer_list<double> list) {
	m_ptr = new double[list.size()];
	size_t i = 0;
	for (double el : list) {
		
		m_ptr[i] = el;
		++i;
	}
	m_rows = list.size();
	m_columns = 1;
	m_capacity = m_rows;
}

void linalg::Matrix::reshape(size_t rows, size_t columns) {
	if (rows * columns == m_rows * m_columns) {
		m_rows = rows;
		m_columns = columns;
	}
	else {
		throw - 1;
	}
}

void linalg::Matrix::reserve(size_t capacity) {
	if (m_capacity >= capacity) return;

	double* tmp_ptr = new double[capacity];
	for (size_t i = 0; i < m_rows * m_columns; ++i) {
		tmp_ptr[i] = m_ptr[i];
	}
	delete[] m_ptr;
	m_ptr = tmp_ptr;
	m_capacity = capacity;
}

void linalg::Matrix::shrink_to_fit() {
	if (m_capacity == m_rows * m_columns) return;

	double* tmp_ptr = new double[m_rows * m_columns];
	for (size_t i = 0; i < m_rows * m_columns; ++i) {
		tmp_ptr[i] = m_ptr[i];
	}
	m_ptr = tmp_ptr;
	m_capacity = m_rows * m_columns;
}
