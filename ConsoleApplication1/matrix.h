#pragma once

#ifndef __MATRIX_H
#define __MATRIX_H

#include <iostream>
#include <string>

// Requirments:			Implemented:		Optimized:
// Default constructor  (X)					(X)
// Copy Constructor		(X)
// Set-Method			(X)					(X)
// Get-Method			(X)					(X)
// Math-operators?	
// Iterator: For all elements
// Row_Iterator: Iterator for all rows
// Column_Iterator
// Exception safe?
// Thread safe???

//This is a resource allocating class. 
template <typename T>
class matrix
{
public:
	matrix(unsigned int x_size, unsigned int y_size, T init) :
		m_x_size(x_size),
		m_y_size(y_size),
		m_size(x_size*y_size),
		pVec(new T[m_size])
	{
		for (auto i = 0; i < m_size; i++) {
			pVec[i] = init;
		}
	};

	~matrix(){
		delete[] pVec;
	};
	matrix(const matrix& rhs) :
		m_x_size(rhs.m_x_size),
		m_y_size(rhs.m_y_size),
		m_size(rhs.m_size),
		pVec(new T[m_size])
	{
		if (this != &rhs) {
			for (auto i = 0; i < m_size; i++) {
				this->pVec[i] = rhs.pVec[i];
			}
		}
	};

	matrix& operator=(const matrix& rhs) {
		this->m_x_size = rhs.m_x_size;
		this->m_y_size = rhs.m_y_size;
		this->m_size = rhs.m_size;
		delete this->pVec;
		this->pVec = new T[m_size];
		for (auto i = 0; i < m_size; i++) {
			this->pVec[i] = rhs.pVec[i];
		}

		return *this;
	};
	void display(void) const{
		for (auto i = 0; i < this->m_y_size; i++){
			std::cout << "[ ";
			for (auto j = 0; j < this->m_x_size; j++) {
				std::cout << pVec[i*m_x_size + j] << " ";
			}
			std::cout << "]" << std::endl;
		}
		std::cout << "------------" << std::endl;
	};
	T get(unsigned int x, unsigned int y) const{
		return pVec[y*m_y_size + x];
	};
	void set(unsigned int x, unsigned int y, T value) {
		pVec[y*m_y_size + x] = value;
	};


	//Vad vill vi ha för beteende på vår interator?
	//1. begin returnerar en ny iterator-klass som i sin tur har en 
	// begin() och end() funktioner. Dessa i sin tur returnerar T*
	//Hur ska denna komma ihåg vad den redan har delat ut?	

	using column_iterator = T*;
	using const_iterator = const T*;
	iterator begin(void) { return pVec; };
	const_iterator begin(void) const { return pVec; };
	iterator end(void) { return pVec + m_size; };
	const_iterator end(void) const { return pVec + m_size; };

	class row_iterator {
	public:
		column_iterator begin() {return pVec[]};
		column_iterator end() {};
	private: 
	};

private:

	unsigned int m_x_size;
	unsigned int m_y_size;
	unsigned int m_size;
	T* pVec;
};

#endif