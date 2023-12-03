/*

	Author: Seth Van Hee
	Date: 12/2/2023
	Purpose: relearning C++, thus implementing solutions poorly.
			 Part 1: This solution is overcomplicated and could be done without the hashmap.
			 Part 2: This solution is now even worse because of the hashmap as I need to evaluate a different result besides game possibility.

*/

#include "CubeGame.h"
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <sstream>
#include <string>
#include <climits>
using namespace std;

struct Cubes {
	int maxRed, maxGreen, maxBlue;
};

void createGameResult(unordered_map<int, bool>* gameMap, string line);
Cubes createCubes(istringstream* lineStream);
bool isGamePossible(Cubes cubes);

const int MAX_RED_CUBES = 12;
const int MAX_GREEN_CUBES = 13;
const int MAX_BLUE_CUBES = 14;

int sumMinCubes = 0; // this is bad

int main() {
	ifstream inputFileStream;
	inputFileStream.open("cubes.txt");
	string line;
	int sumGameID = 0;

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
			sumGameID += iter->first;
		}
	}

	cout << sumGameID << endl;
	cout << sumMinCubes << endl;
}

void createGameResult(unordered_map<int, bool>* gameMap, string line) {
	istringstream lineStream(line);
	string temp;
	lineStream.ignore(5); // ignores "Game "

	getline(lineStream, temp, ':');

	int gameID = stoi(temp);
	lineStream.ignore(1); // ignores space before data set

	Cubes cubes = createCubes(&lineStream);

	(*gameMap)[gameID] = isGamePossible(cubes);
}

Cubes createCubes(istringstream* lineStream) {
	int maxRedCubes = 0;
	int maxGreenCubes = 0;
	int maxBlueCubes = 0;
	Cubes newCubes;

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

			if (color == "red") {
				if (value > maxRedCubes) {
					maxRedCubes = value;
				}
			}
			else if (color == "green") {
				if (value > maxGreenCubes) {
					maxGreenCubes = value;
				}
			}
			else if (color == "blue") {
				if (value > maxBlueCubes) {
					maxBlueCubes = value;
				}
			}
		}
		
	}

	newCubes.maxRed = maxRedCubes;
	newCubes.maxGreen = maxGreenCubes;
	newCubes.maxBlue = maxBlueCubes;

	// this section gives the results for part2, still bad
	sumMinCubes += maxRedCubes * maxGreenCubes * maxBlueCubes;

	return newCubes;
}

bool isGamePossible(Cubes cubes) {
	if (cubes.maxRed > MAX_RED_CUBES) {
		return false;
	}
	if (cubes.maxGreen > MAX_GREEN_CUBES) {
		return false;
	}
	if (cubes.maxBlue > MAX_BLUE_CUBES) {
		return false;
	}

	return true;
}
