// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "storage.h"
#include "matrix.h"

int main() 
{
	matrix<int> m1(4, 2, 3);
	m1.display();

	matrix<int> m2(m1);
	m2.display();

	matrix<int> m3(1,1,1);
	m3 = m1;
	m3.set(0, 1, 4);
	m3.display();

	std::cout << "operator[]" << m3[0][1] << "operator(): " << m3(0, 1) << std::endl;

	m3[0][1] = 2;


	m3.display();

	matrix<int> m4 = m3.transpose();

	m4.display();

	try{
		matrix<int> m5 = m4 + m3;
	}
	catch (...) {
		matrix<int> m5 = m4 + m4;
		m5.display();
	}
	matrix<int> m6(2,2,1);
	m6 += m6;
	m6.display();

	matrix<double> m7 = matrix<double>::eye(4);
	matrix<double> m8(4, 4, 1);
	matrix<double> m9 = m8*m7;
	m8 += m7;
	m8 = m7*m7;
	m8 *= m7;
	m7.display();
	m8.display();
	m9.display();

	matrix<int> m10(3, 2, 1);
	matrix<int> m11(2, 3, 1);
	matrix<int> m12 = m10*m11;
	m12.display();

	matrix<int> m13(30, 40, 1);
	m13 *= m13.transpose();
	m13.display();


	/*
	int* Hej = new(int);
	
	matrix<int> mInt(6, 6, 1);

	matrix<std::string> mStr(2,2,"hej");

	matrix<double> mDouble(4, 2, 13.0);

	mInt.set(0, 0, 7);
	mInt.set(5, 5, 2);
	mInt.set(1, 0, 3);

	mInt.display();
	mStr.display();
	mDouble.display();
	*/
	return 0;
}

