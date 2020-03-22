#pragma once

#include <vector>
#include <string>

typedef std::vector< std::vector<int> > array;

class Matrix {
private:
	int rows;
	int columns;
	array m;

public:
	Matrix(array);
	Matrix(int, int);
	Matrix(std::string);

	Matrix transpose();
	Matrix operator*(Matrix);
	std::string toString();
	void mod(int);

	const array getM() const;
	const int getRows() const;
	const int getColumns() const;
};

