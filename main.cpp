#include <iostream>
#include <vector>

#include "Matrix.h"

int main() {
	Matrix m0(3, 5);
	std::cout << m0.toString();

	std::vector< std::vector<int> > arr;
	std::vector<int> row0 = { 1, 2, 3, 4, 5 };
	std::vector<int> row1 = { 1, 2, 3, 4, 5 };
	std::vector<int> row2 = { 1, 2, 3, 4, 5 };
	arr.push_back(row0);
	arr.push_back(row1);
	arr.push_back(row2);

	Matrix m1(arr);
	std::cout << std::endl  << m1.toString();
	try {
		Matrix m2("plik.txt");
	}
	catch (const char* err) {
		std::cout << err;
	}

	getchar();
	return EXIT_SUCCESS;
}