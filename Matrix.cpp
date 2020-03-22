#include <fstream>

#include "Matrix.h"

// Tworzenie macierzy z instniej¹cego obiektu typu array
Matrix::Matrix(array origin) : rows(origin.size()), columns(origin[0].size()) {
	std::vector<int> row;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			row.push_back(origin[i][j]);
		}
		m.push_back(row);
		row.erase(row.begin(), row.end());
	}
}

// Tworzenie macierzy o rozmiarach _rows x _columns o elementach równych 1
Matrix::Matrix(int _rows, int _columns) : rows(_rows), columns(_columns) {
	std::vector<int> row;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			row.push_back(1);
		}
		m.push_back(row);
		row.erase(row.begin(), row.end());
	}
}

// Wczytywanie macierzy z pliku fileName
// pierwszy wiersz zawiera iloœæ wierszy i iloœæ kolumn odpowiednio
Matrix::Matrix(std::string fileName) {
	std::ifstream infile;
	infile.open(fileName);
	if (!infile.good()) {
		throw "\nFile does not exist\n";
	}

	int r, c;
	infile >> r >> c;
	if (r < 1 || c < 1) {
		throw "\nIncorrect size\n";
	}

	rows = r;
	columns = c;
	std::vector<int> row;
	int value;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			infile >> value;
			row.push_back(value);
		}
		m.push_back(row);
		row.erase(row.begin(), row.end());
	}

	infile.close();
}

// Zapisanie macierzy do klasy string
std::string Matrix::toString() {
	std::string str;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			str += std::to_string(m[i][j]) + " ";
		}
		str += "\n";
	}
	return str;
}
