// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "storage.h"

int main()
{
	
	storage<double> dStorage(17);
	std::cout << dStorage.size() << std::endl;

	return 0;
}

