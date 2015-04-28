#pragma once

#ifndef __MATRIX_H
#define __MATRIX_H

#include <iostream>
#include <string>
#include <vector>

// Requirments:			Implemented:		Optimized:
// Default constructor  (X)					
// Copy Constructor		(X)
// Set-Method			(X)					
// Get-Method			(X)					
// Math-operators?	
// Iterator: For all elements
// Row_Iterator: Iterator for all rows
// Column_Iterator
// Exception safe?
// Thread safe???
// SVD 
// Eigenvalue

//This is a resource allocating class. 
template <typename T>
class matrix
{
public:
	matrix(const unsigned int& x_size, const unsigned int& y_size, const T& init) :
		m_x_size(x_size),
		m_y_size(y_size),
		m_size(x_size*y_size),
		imatrix(x_size)
		{
			//imatrix.resize(x_size);
			for (auto i = 0; i < x_size; i++) {
				imatrix[i].resize(y_size, init);
			}
		};
	 
	~matrix(){};

	matrix(const matrix& rhs) :
		m_x_size(rhs.m_x_size),
		m_y_size(rhs.m_y_size),
		m_size(rhs.m_size),
		imatrix(rhs.imatrix)
	{
	};

	matrix& operator=(const matrix& rhs) {
		if (this == &rhs)
			return *this;

		this->m_x_size = rhs.m_x_size;
		this->m_y_size = rhs.m_y_size;
		this->m_size = rhs.m_size;
		this->imatrix = rhs.imatrix;

		return *this;
	};

	void display(void) const{
		for (auto i = 0; i < this->m_y_size; i++){
			std::cout << "[ ";
			for (auto j = 0; j < this->m_x_size; j++) {
				std::cout << imatrix[j][i] << " ";
			}
			std::cout << "]" << std::endl;
		}
		std::cout << "------------" << std::endl;
	};

	void set(const unsigned int& x, const unsigned int& y, T value) {	
		this->imatrix[x][y] = value;
	};

	// This is used for non-const objects. Both RHS and LHS.
	std::vector<T>& operator[](const unsigned int& x) {
		return this->imatrix[x];
	};

	// This function is allowed to be called for matrix-objects that are declared const. (this is the second const)
	// The function have to return a const reference, since it returns a reference to a member of the class itself, which is const.
	// The compiler will not let you return a non-const reference to the class itself, in this version when the function is const.
	const std::vector<T>& operator[](const unsigned int& x) const {
		return this->imatrix[x];
	};

	T& operator()(const unsigned int& x, const unsigned int& y) {
		return imatrix[x][y];
	}

	//This version is used for const declared instances of the matrix class. See operator[] for motivation.
	const T& operator()(const unsigned int& x, const unsigned int& y) const {
		return imatrix[x][y];
	}


	// This function dont transpose the object itself, but returns a transposed copy of the matrix.
	// Is this the kind of API that we want? or shall we transpose the object itself?
	matrix<T> transpose(void) {
		matrix<T> result(this->m_y_size, this->m_x_size, 0);

		//Loop over return matrix
		for (auto i = 0; i < result.m_y_size; i++) {
			for (auto j = 0; j < result.m_x_size; j++) {
				result(j,i) = this->imatrix[i][j];
			}
		}
		return result;
	};

	matrix<T> operator+(const matrix<T>& rhs) {
		matrix<T> result(this->m_x_size, this->m_y_size, 0);

		//Check if size is equal first. throw excption if not.
		if (this->m_x_size != rhs.m_x_size || this->m_y_size != rhs.m_y_size) {
			throw std::length_error("Matrices must be of the same size");
			//No returns after throw
			//This object is in a valid state
		}

		for (auto i = 0; i < this->m_y_size; i++) {
			for (auto j = 0; j < this->m_x_size; j++) {
				result(j, i) = this->imatrix[j][i] + rhs(j,i);
			}
		}
		return result;
	};

	matrix<T>& operator+=(const matrix<T>& rhs) {

		//Check if size is equal first. throw excption if not.
		if (this->m_x_size != rhs.m_x_size || this->m_y_size != rhs.m_y_size) {
			throw std::length_error("Matrices must be of the same size");
			//No returns after throw
			//This object is in a valid state
		}
		matrix<T> exception_safe_tmp = *this + rhs; 
		(*this) = exception_safe_tmp;
		return *this;
	};

	static matrix<T> eye(const unsigned int& size) {
		matrix<T> result(size, size, 0);
		for (auto i = 0; i < size; i++) {
			result(i, i) = T(1);
		}
		return result;
	};

	matrix<T> operator-(const matrix<T>& rhs) {
		matrix<T> result(this->m_x_size, this->m_y_size, 0);

		//Check if size is equal first. throw excption if not.
		if (this->m_x_size != rhs.m_x_size || this->m_y_size != rhs.m_y_size) {
			throw std::length_error("Matrices must be of the same size");
			//No returns after throw
			//This object is in a valid state
		}

		for (auto i = 0; i < this->m_y_size; i++) {
			for (auto j = 0; j < this->m_x_size; j++) {
				result(j, i) = this->imatrix[j][i] - rhs(j, i);
			}
		}
		return result;
	};

	matrix<T>& operator-=(const matrix<T>& rhs) {

		//Check if size is equal first. throw excption if not.
		if (this->m_x_size != rhs.m_x_size || this->m_y_size != rhs.m_y_size) {
			throw std::length_error("Matrices must be of the same size");
			//No returns after throw
			//This object is in a valid state
		}
		matrix<T> exception_safe_tmp = *this - rhs;
		(*this) = exception_safe_tmp;
		return *this;
	};

	matrix<T> operator*(const matrix<T> rhs) {
		if (this->m_x_size != rhs.m_y_size) {
			throw std::length_error("Wrong matrix dimensions");
		}

		matrix<T> result(rhs.m_x_size, this->m_y_size, 0);
		for (auto i = 0; i < this->m_y_size; i++) {
			for (auto j = 0; j < rhs.m_x_size; j++) {
				T value(0);
				for (auto k = 0; k < this->m_x_size; k++) {
					value += this->imatrix[k][i]*rhs(j, k);
				}
				result(j,i) = value;
			}
		}
		return result;
	};

	matrix<T> operator*=(const matrix<T>& rhs) {
		matrix<T> result(rhs.m_x_size, this->m_y_size, 0);

		result = *(this) * rhs;
		*(this) = result;
		return *this;
	};

private:

	unsigned int m_x_size;
	unsigned int m_y_size;
	unsigned int m_size;
	std::vector<std::vector<T>> imatrix;
};

#endif