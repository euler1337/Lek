// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "storage.h"
#include "matrix.h"

int main() 
{

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

	return 0;
}

