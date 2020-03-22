#include <iostream>
#include <vector>

#include "Matrix.h"

int main() {
	array m1;
	std::vector<int> row1 = { 1, 0, 2 };
	std::vector<int> row2 = { -1, 3, 1 };
	m1.push_back(row1);
	m1.push_back(row2);
	Matrix M1(m1);

	array m2;
	std::vector<int>row3 = { 3, 2, 1 };
	std::vector<int>row4 = { 1, 1, 0 };
	m2.push_back(row3);
	m2.push_back(row4);
	Matrix M2(Matrix(m2).transpose());

	std::cout << M1.toString() << std::endl;
	std::cout << M2.toString() << std::endl;

	bool flag = false;
	try {
		M1 * M2;
	}
	catch (const char* err) {
		std::cout << err;
		flag = true;
	}

	if (flag == true) {
		std::cout << "error";
	}
	else {
		Matrix result(M1 * M2);
		std::cout << result.toString() << std::endl;
		result.mod(3);
		std::cout << result.toString();
	}


	getchar();
	return EXIT_SUCCESS;
}