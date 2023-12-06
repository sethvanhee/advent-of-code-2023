#include "SchematicSorter.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_set>
using namespace std;

struct Part {
	int partNumber;
	vector<int> index;

	Part(int partNumber, vector<int> index) {
		this->partNumber = partNumber;
		this->index = index;
	}
};

const string FILE_PATH = "schematic.txt";

vector<Part> partList; 
unordered_set<int> symbolList;
unordered_set<char> uniqueSymbols;
int totalIndex = 0;

void parseLine(string line);
void printPartNumbers();
void printSymbols();
void addSymbol(int index, int length);
int calculatePartNumberSum();
bool isAdjacent(int index);

int main() {
	ifstream file;
	string line;

	file.open(FILE_PATH);

	if (file.is_open()) {
		while (getline(file, line)) {
			parseLine(line);
		}
	}
	else {
		cout << "File opening failed" << endl;
	}

	for (char c : uniqueSymbols) {
		cout << c << endl;
	}

	//printPartNumbers();
	//printSymbols();
	cout << calculatePartNumberSum() << endl;
}

void parseLine(string line) {
	int length = line.length();
	string partString = "";
	vector<int> index;

	for (int i = 0; i < length; i++) {
		//cout << totalIndex << endl;

		//debug
		if (uniqueSymbols.find(line.at(i)) == uniqueSymbols.end()) {
			uniqueSymbols.insert(line.at(i));
		}

		//debug

		if (line.at(i) == '.') {
			continue;
		}

		if ( (line.at(i) >= 33 && line.at(i) <= 47) || (line.at(i) >= 61 && line.at(i) <= 64) ) { // checks if char is a symbol ( ! to / ) or @
			addSymbol(i + totalIndex, length);
			//cout << endl << line.at(i) << endl;
			continue;
		}

		for (int k = 0; k < 3; k++) {
			if (isdigit(line.at(i))) {
				partString += line.at(i);
				//cout << partString << endl;
				index.push_back(i + totalIndex);
				i++;
			}
			else {
				break;
			}
		}
		if ( !(partString.empty()) ) {
			partList.push_back( Part(stoi(partString), index) );
			partString = "";
			index.clear();
			i--;
		}
		//cout << endl;
	}

	totalIndex += length;
}

void printPartNumbers() {
	cout << "Part Numbers" << endl;
	for (const Part& part : partList) {
		cout << "Part Number: " << part.partNumber << endl;

		cout << "Index: ";

		for (int index : part.index) {
			cout << index << " ";
		}

		cout << endl << endl;
	}
	cout << endl;
}

void printSymbols() {
	//unordered_set<int>::iterator itr;
	cout << "Symbols" << endl;
	for (int index : symbolList) {
		cout << index << endl;
	}
}

void addSymbol(int index, int length) {
	symbolList.insert(index - length - 1);
	symbolList.insert(index - length);
	symbolList.insert(index - length + 1);

	symbolList.insert(index - 1);
	symbolList.insert(index);
	symbolList.insert(index + 1);

	symbolList.insert(index + length - 1);
	symbolList.insert(index + length);
	symbolList.insert(index + length + 1);
}


int calculatePartNumberSum() {
	int sum = 0;
	for (const Part& part : partList) {
		for (int index : part.index) {
			if (isAdjacent(index)) {
				//cout << "Part Number: " << part.partNumber << endl;
				sum += part.partNumber;
				break;
			}
		}
	}
	return sum;
}

bool isAdjacent(int index) {
	if (symbolList.find(index) != symbolList.end()) {
		return true;
	}

	return false;
}