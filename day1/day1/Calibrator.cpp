/*
	
	Author: Seth Van Hee
	Date: 12/2/2023
	Purpose: relearning C++, thus implementing solutions poorly

*/

#include "Calibrator.h"
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
using namespace std;

int getCalibrationValues(string line);
string formatLine(string inputLine);
string parseString(string inputLine, int index);
string getNumber(string substring);

unordered_map<string, int> numbers;

int main() {
	int sum = 0;
	string line;
	ifstream file;
	file.open("calibrationValues.txt"); 

	// Populate the hashmap
	numbers["zero"] = 0;
	numbers["one"] = 1;
	numbers["two"] = 2;
	numbers["three"] = 3;
	numbers["four"] = 4;
	numbers["five"] = 5;
	numbers["six"] = 6;
	numbers["seven"] = 7;
	numbers["eight"] = 8;
	numbers["nine"] = 9;

	if (file.is_open()) {
		while ( getline(file, line) ) {
			string newLine = formatLine(line);
			int newNum = getCalibrationValues(newLine);
			sum += newNum;
			
			//cout << line + " " << endl;
			//cout << "newline: " + newLine + " " << endl;
			//cout << newNum << endl;
		}
		file.close();
	}
	else {
		cerr << "File opening failed." << endl;
	}

	cout << sum << endl;

	return 0;
}

string formatLine(string inputLine) {
	string newString = "";
	for (int i = 0; i < inputLine.length(); i++) {
		newString += parseString(inputLine, i);
	}
	return newString;
}

string parseString(string inputLine, int index) {
	string substring = "";
	for (int f = index; f < inputLine.length(); f++) {
		if (isdigit(inputLine.at(f)) && f == index) {
			return string(1, tolower(inputLine.at(f)));
		}
		else {
			substring += inputLine.at(f);
		}
		if (substring.length() > 5) {
			return string(1, tolower(inputLine.at(index)));
		}
		else if (substring.length() >= 3) {
			if (numbers.find(substring) != numbers.end()) {
				return getNumber(substring);
			}
		}
	}

	return string(1, tolower(inputLine.at(index)));
}

string getNumber(string substring) {
	unordered_map<string, int>::iterator iter = numbers.find(substring);
	string result = "";

	if (iter != numbers.end()) {
		result = to_string(iter->second);
	}
	return result;
}

int getCalibrationValues(string line) {
	int firstNum = -1;
	int secondNum = -1;
	
	for (int i = 0; i < line.length(); i++) {
		if ( isdigit( line.at(i) ) ) {
			firstNum = ( line.at(i) - '0' );
			break;
		}
	}
	for (int i = line.length() - 1; i >= 0; i--) {
		if (isdigit(line.at(i))) {
			secondNum = (line.at(i) - '0');
			break;
		}
	}

	return firstNum * 10 + secondNum;
}
