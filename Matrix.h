#pragma once

#include <vector>
#include <string>

typedef std::vector< std::vector<int> > array;

class Matrix {
public:
	int rows;
	int columns;
	array m;

	Matrix(array);
	Matrix(int, int);
	Matrix(std::string);

	Matrix transpose();
	Matrix operator*(Matrix);
	std::string toString();
	bool isZero();
	void mod(int);
	
	const array getM() const;
	const int getRows() const;
	const int getColumns() const;
};

