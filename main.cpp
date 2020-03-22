#include <iostream>
#include <vector>

#include "Matrix.h"

int main() {
	Matrix H("H.txt");
	Matrix G("G.txt");
	Matrix result(H * G.transpose());

	result.mod(2);

	std::cout << result.toString();

	getchar();
	return EXIT_SUCCESS;
}