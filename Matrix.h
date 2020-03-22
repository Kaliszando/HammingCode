#pragma once

#include <vector>
#include <string>

class Matrix {
private:
	typedef std::vector< std::vector<int> > array;
	int rows;
	int columns;
	array m;

public:
	Matrix(array);
	Matrix(int _rows, int _columns);
	Matrix(std::string fileName);

	array operator*(array);
	array transpose(array);
	std::string toString();
};

