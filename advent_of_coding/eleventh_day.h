#pragma once
#include <array>
using namespace std;

const int GRIDSIZE = 300;
const int GRIDSIZE_X = GRIDSIZE;
const int GRIDSIZE_Y = GRIDSIZE;

int calculatePowerLevel(pair<int, int> coordinates, int serialNumber);

int calculateSquarePower(array<array<int, GRIDSIZE_Y>, GRIDSIZE_X>& powerLevels, pair<int, int> start, int squareSize);

void eleventh_day_func();