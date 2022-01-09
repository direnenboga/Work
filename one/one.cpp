// one.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <boost/filesystem.hpp>
#include "chess.h"
using namespace std;
int main(int argc, char* argv[])
{
	for (int i = 1; i < argc; i++) {
	/*	std::string str(argv[i]);
		string aa = "C:\\Users\\serha\\source\\repos\\one\\Debug\\"+str ;
		boost::filesystem::ifstream fileHandler(aa);*/

		boost::filesystem::ifstream fileHandler(argv[i]);
		std::string line;
		vector<string> words{};
		size_t pos = 0;
		string space_delimiter = " ";
		while (getline(fileHandler, line)) {
			while ((pos = line.find(space_delimiter)) != string::npos) {
				words.push_back(line.substr(0, pos));
				line.erase(0, pos + space_delimiter.length());
			}
			words.push_back(line);
		}
		Chess* chess = new Chess();
		cout << argv[i] << "\t";
		getMans(words, chess);
		chess->getPoint();
		delete chess;
	}

}


