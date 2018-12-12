#include "eleventh_day.h"
#include <iostream>
#include <vector>

using namespace std;

int calculatePowerLevel(pair<int, int> coordinates, int serialNumber) {
	int rackID = coordinates.first + 10;
	int powerLevel = rackID * coordinates.second;
	powerLevel += serialNumber;
	powerLevel = powerLevel * rackID;
	powerLevel = (powerLevel / 100 % 10);
	return powerLevel - 5;
}

int calculateSquarePower(array<array<int, GRIDSIZE_Y>, GRIDSIZE_X>& powerLevels, pair<int, int> start, int squareSize) {
	int sum = 0;
	for (int x = start.first; x < start.first + squareSize; ++x) {
		for (int y = start.second; y < start.second + squareSize; ++y) {
			sum += powerLevels[x][y];
		}
	}
	return sum;
}

void eleventh_day_func(){

	const int SERIAL_NUMBER = 9995;
	array<array<int, GRIDSIZE_Y>, GRIDSIZE_X> powerLevels;

	int highest = 0;
	for (int i = 0; i < GRIDSIZE_X; ++i) {
		for (int j = 0; j < GRIDSIZE_Y; ++j) {
			powerLevels[i][j] = calculatePowerLevel(pair<int, int>{i + 1, j + 1}, SERIAL_NUMBER);
			if (i > 2 && j > 2) {
				int power = calculateSquarePower(powerLevels, pair<int, int>{i - 3, j - 3}, 3);

				if (power > highest) {
					highest = power;
					cout << "Highest at 3x3 :" << i - 2 << "," << j - 2 << " with value : " << highest << endl;
				}
			}
			//cout << powerLevels[i][j] << " ";
		}
		//cout << endl;
	}
	highest = 0;
	int bestSize = 0;
	array<array<vector<int>*, GRIDSIZE_Y>*, GRIDSIZE_X>* gridPowers = new array<array<vector<int>*, GRIDSIZE_Y>*, GRIDSIZE_X>;
	for (int x = 0; x < GRIDSIZE_X; ++x) {
		cout << x + 1 << " out of " << GRIDSIZE_X << endl;
		gridPowers->at(x) = new array<vector<int>*, GRIDSIZE_Y>;
		for (int y = 0; y < GRIDSIZE_Y; ++y) {
			vector<int>* squares = new vector<int>;
			gridPowers->at(x)->at(y) = squares;
			squares->push_back(0);
			for (int size = 1; size < GRIDSIZE_X - max(x, y); ++size) {
				int square = 0;
				for (int i = x; i < x + size; ++i) {
					square += powerLevels[i][y + size - 1];
				}
				for (int j = y; j < y + size - 1; ++j) {
					square += powerLevels[x + size - 1][j];
				}
				int sum = square + squares->at(size - 1);
				//cout << sum << " " << square << " " << squares->at(size - 1) << endl;
				squares->push_back(sum);
				if (sum > highest) {

					highest = sum;
					bestSize = size;
					cout << "Best square at " << x + 1 << " " << y + 1 << " with size " << bestSize << " and value: " << highest << endl;
				}
			}
			//cout << endl;
		}
		
	}
}