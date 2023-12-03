/*

	Author: Seth Van Hee
	Date: 12/2/2023
	Purpose: relearning C++, thus implementing solutions poorly.
			 This solution is overcomplicated and could be done without the hashmap

*/

#include "CubeGame.h"
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <sstream>
#include <string>
using namespace std;

void createGameResult(unordered_map<int, bool>* gameMap, string line);
bool evaluateGamePossibility(istringstream* lineStream);

const int MAX_RED_CUBES = 12;
const int MAX_GREEN_CUBES = 13;
const int MAX_BLUE_CUBES = 14;

int main() {
	ifstream inputFileStream;
	inputFileStream.open("cubes.txt");
	string line;
	int sum = 0;

	unordered_map<int, bool> gameMap;

	if (inputFileStream.is_open()) {
		while ( getline(inputFileStream, line) ) {
			createGameResult(&gameMap, line);
		}
	}
	else {
		cerr << "File opening failed." << endl;
	}

	unordered_map<int, bool>::iterator iter;
	for (iter = gameMap.begin(); iter != gameMap.end(); iter++) {
		if (iter->second) {
			sum += iter->first;
		}
	}

	cout << sum << endl;
}

void createGameResult(unordered_map<int, bool>* gameMap, string line) {
	istringstream lineStream(line);
	string temp;
	lineStream.ignore(5); // ignores "Game "

	getline(lineStream, temp, ':');

	int gameID = stoi(temp);
	cout << gameID << endl;
	lineStream.ignore(1); // ignores space before data set

	bool isGamePossible = evaluateGamePossibility(&lineStream);

	(*gameMap)[gameID] = isGamePossible;
}

bool evaluateGamePossibility(istringstream* lineStream) {
	int redCubes = 0;
	int greenCubes = 0;
	int blueCubes = 0;

	string game, color, temp;
	int value;

	while (!(*lineStream).eof()) {
		getline(*lineStream, game, ';');
		istringstream gameLineStream(game);

		while (!gameLineStream.eof()) {
			gameLineStream >> temp;
			value = stoi(temp);

			gameLineStream.ignore(1); // ignores the space after the number
			getline(gameLineStream, color, ',');

			if (color == "red" && value > redCubes) {
				redCubes = value;
			}
			else if (color == "green" && value > greenCubes) {
				greenCubes = value;
			}
			else if (color == "blue" && value > blueCubes) {
				blueCubes = value;
			}
		}

	}

	if (redCubes > MAX_RED_CUBES) {
		return false;
	}
	if (greenCubes > MAX_GREEN_CUBES) {
		return false;
	}
	if (blueCubes > MAX_BLUE_CUBES) {
		return false;
	}

	return true;
}
