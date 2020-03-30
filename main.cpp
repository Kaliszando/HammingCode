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

		// Data encoding
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
				std::cout<<content[i];
				byteContent.push_back(byte(content[i]));
			}
			infile.close();
			std::cout << std::endl;

			std::vector<Matrix> words;
			array bitsTab;
			std::vector<int> bits;
			for (unsigned int i = 0; i < byteContent.size(); i++) {
				for (int j = 0; j < 8; j++) {
					bits.push_back(byteContent[i][j]);
				}
				bitsTab.push_back(bits);
				words.push_back(Matrix(bitsTab));
				bits.erase(bits.begin(), bits.end());
				bitsTab.erase(bitsTab.begin(), bitsTab.end());
			}

			std::vector<Matrix> codewords;
			for (unsigned int i = 0; i < words.size(); i++) {
				codewords.push_back(Matrix(words[i] * G));
				codewords[i].mod(2);
			}

			bool failureFlag = false;
			for (unsigned int i = 0; i < codewords.size(); i++) {
				Matrix err(H * codewords[i].transpose());
				err.mod(2);
				if (err.isZero() == false) {
					failureFlag = true;
				}
			}

			std::ofstream outfile;
			outfile.open("encoded.txt");
			for (unsigned int i = 0; i < codewords.size(); i++) {
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

		// Data decoding
		if (option == "2") {
			std::cout << "enter file name to decode" << std::endl;
			std::cout << ">> ";
			std::string fileName;
			std::getline(std::cin, fileName);

			std::cout << "enter how many characters to decode <1, 256>" << std::endl;
			std::cout << ">> ";
			int size;
			std::cin >> size;
			std::cin.get();
			if (size < 1) size = 1;
			if (size > 256) size = 256;
			std::cout << "characters set to decode: " << size << std::endl;

			std::ifstream infile;
			infile.open(fileName);
			if (!infile.good()) {
				std::cout << "file does not exist\n\n";
				break;
			}

			Matrix H("H.txt");


			std::vector<Matrix> codewords;
			array bitsTab;
			std::vector<int> bits;
			int bit;
			for(int j=0;j<size;j++){
                for(int j=0;j<16;j++){
                    infile>>bit;
                    bits.push_back(bit);
                }
                bitsTab.push_back(bits);
                codewords.push_back(Matrix(bitsTab));
				bits.erase(bits.begin(), bits.end());
				bitsTab.erase(bitsTab.begin(), bitsTab.end());
			}
			infile.close();

			std::vector<byte> msg;
			msg.resize(size);
			bool failureFlag = false;
			int errorCounts = 0;

			for (unsigned int i = 0; i < codewords.size(); i++) {
				Matrix err(H * codewords[i].transpose());
				err.mod(2);
				errorCounts = 0;

				if (err.isZero() == false) {
					errorCounts = 3;
                    failureFlag = true;
                    bool columnFlag;

                    for(int c=0;c<16;c++){
                        columnFlag=true;
                        for(int r=0;r<8;r++){
							if (err.m[r][0] != H.m[r][c]) {
                                columnFlag = false;
							}
                        }

                        if(columnFlag){
                            codewords[i].m[0][c]=(codewords[i].m[0][c]+1)%2;
							errorCounts = 1;
                        }
                    }

					if (errorCounts > 1) {
						int tab[8];

						int col = H.m[0].size();
						int row = H.m.size();

						for (int l = 0; l < col - 1; l++) {
							for (int j = l + 1; j < col; j++) {
								bool stop = false;
								for (int k = 0; k < row; k++) {
									tab[k] = H.m[k][l] + H.m[k][j];
									tab[k] %= 2;
									if (tab[k] != err.m[k][0]) {
										stop = true;
									}
								}

								if (stop == false) {
									// Wyswietlenie pozycji na których wyst¹pi³ b³¹d
									//std::cout << l << " " << j << std::endl;
									codewords[i].m[0][j] = (codewords[i].m[0][j] + 1) % 2;
									codewords[i].m[0][l] = (codewords[i].m[0][l] + 1) % 2;
									errorCounts = 2;
								} 
							}
						}
						
					}

				}
            }

            for(int i=0;i<size;i++){
                for(int j=0;j<8;j++){
                        msg[i][j]=codewords[i].m[0][j];
                }
                unsigned long n = msg[i].to_ulong();
                unsigned char c = static_cast<unsigned char>( n );
                std::cout<<c;
            }
            std::cout << std::endl;

			if (failureFlag == true && errorCounts == 1) {
				std::cout << "Decoding success: single error corretion(s)" << std::endl;
			}

			if (failureFlag == true && errorCounts == 2) {
				std::cout << "Decoding success: double error corretion(s)" << std::endl;
			}

			if (failureFlag == false && errorCounts == 0) {
				std::cout << "Decoding success: No errors detected" << std::endl;
			}

			std::cout << std::endl;

		}

		if (option == "3") {
			exit = true;
		}
	}

	return EXIT_SUCCESS;
}
