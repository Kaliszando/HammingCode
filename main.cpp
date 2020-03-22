#include <iostream>
#include <vector>
#include <bitset>
#include <fstream>

#include "Matrix.h"

typedef std::bitset<8> byte;

int main() {

	std::string option;
	bool exit = false;;
	while (exit != true) {
		std::cout << "1 - encode data" << std::endl;
		std::cout << "2 - decode data" << std::endl;
		std::cout << "3 - exit program" << std::endl;
		std::cout << ">> ";
		std::getline(std::cin, option);
		std::cout << std::endl;

		if (option == "1") {
			std::cout << "enter file name to encode" << std::endl;
			std::cout << ">> ";
			std::string fileName;
			std::getline(std::cin, fileName);

			std::cout << "enter how many characters to encode <1, 256>" << std::endl;
			std::cout << ">> ";
			int size;
			std::cin >> size;
			std::cin.get();
			if (size < 1) size = 1;
			if (size > 256) size = 256;
			std::cout << "characters set to encode: " << size << std::endl;

			std::ifstream infile;
			infile.open(fileName);
			if (!infile.good()) {
				std::cout << "file does not exist\n\n";
				break;
			}

			Matrix H("H.txt");
			Matrix G("G.txt");
			Matrix result(H * G.transpose());
			result.mod(2);
			std::cout << "H*G^T = 0: ";
			if (result.isZero())
				std::cout << "true" << std::endl;
			else {
				std::cout << "false" << std::endl;
				break;
			}

			char* content = new char[size];
			std::cout << "message content: ";
			std::vector<byte> byteContent;
			for (int i = 0; i < size; i++) {
				infile >> content[i];
				std::cout << content[i];
				byteContent.push_back(byte(content[i]));
			}
			infile.close();
			std::cout << std::endl;

			std::vector<Matrix> words;
			array bitsTab;
			std::vector<int> bits;
			for (int i = 0; i < byteContent.size(); i++) {
				for (int j = 0; j < 8; j++) {
					bits.push_back(byteContent[i][j]);
				}
				bitsTab.push_back(bits);
				words.push_back(Matrix(bitsTab));
				bits.erase(bits.begin(), bits.end());
				bitsTab.erase(bitsTab.begin(), bitsTab.end());
			}

			std::vector<Matrix> codewords;
			for (int i = 0; i < words.size(); i++) {
				codewords.push_back(Matrix(words[i] * G));
				codewords[i].mod(2);
			}

			bool failureFlag = false;
			for (int i = 0; i < codewords.size(); i++) {
				Matrix err(H * codewords[i].transpose());
				err.mod(2);
				if (err.isZero() == false) {
					failureFlag = true;
				}
			}

			std::ofstream outfile;
			outfile.open("encoded.txt");
			for (int i = 0; i < codewords.size(); i++) {
				outfile << codewords[i].toString();
			}
			outfile.close();

			if (failureFlag == true)
				std::cout << "Encoding failure" << std::endl;
			else
				std::cout << "Encoding success" << std::endl;

			std::cout << std::endl;
			delete[] content;
		}

		if (option == "2") {
			std::cout << "Decoding..." << std::endl;
		}

		if (option == "3") {
			exit = true;
		}
	}

	return EXIT_SUCCESS;
}