#pragma once

#include <array>
using namespace std;

const int RULES = 32;
const int INITIAL = 100;
const int GENERATIONS = 200;

array<bool, INITIAL + GENERATIONS>* proceedGeneration(array<bool, INITIAL + GENERATIONS>* pots, array<array<bool, 6>, RULES>& rules);

void twelfth_day_func();