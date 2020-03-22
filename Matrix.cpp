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
		throw "File does not exist\n";
	}

	int r, c;
	infile >> r >> c;
	if (r < 1 || c < 1) {
		throw "Incorrect size\n";
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

// Metoda zwraca macierz transponowan¹
Matrix Matrix::transpose() {
	array transposed;
	std::vector<int> row;

	for (int j = 0; j < columns; j++) {
		for (int i = 0; i < rows; i++) {
			row.push_back(m[i][j]);
		}
		transposed.push_back(row);
		row.erase(row.begin(), row.end());
	}

	return Matrix(transposed);
}

// Metoda zwraca macierz która jest wynikiem mno¿enia m prawostronnie przez m2
Matrix Matrix::operator*(Matrix m2) {
	if (columns != m2.getRows()) {
		throw "Attempt to multiplay nonconformable matrices\n";
	}
	
	array result;
	std::vector<int> row;
	int sum;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < m2.getColumns(); j++) {
			sum = 0;
			for (int k = 0; k < columns; k++) {
				sum += m[i][k] * m2.getM()[k][j];
			}
			row.push_back(sum);
		}
		result.push_back(row);
		row.erase(row.begin(), row.end());
	}

	return Matrix(result);
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

// Zastêpuje elementy tablicy resztami z dzielenia modulo 2
void Matrix::mod(int mod) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			m[i][j] %= mod;
		}
	}
}

// Metody dostêpu do pól
const array Matrix::getM() const {
	return m;
}

const int Matrix::getRows() const {
	return rows;
}

const int Matrix::getColumns() const {
	return columns;
}
