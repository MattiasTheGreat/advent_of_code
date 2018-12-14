#include "twelfth_day.h"
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <array>
using namespace std;

array<bool, INITIAL + GENERATIONS>* proceedGeneration(array<bool, INITIAL + GENERATIONS>* pots, array<array<bool, 6>, RULES>& rules) {
	array<bool, INITIAL + GENERATIONS>* returnPots = new array<bool, INITIAL + GENERATIONS>;
	returnPots->fill(false);
	for (int i = 2; i < INITIAL + GENERATIONS - 2; ++i) {
		bool fits = true;
		for (auto rule : rules) {
			fits = true;
			for (int j = -2; j < 3; ++j) {
				if ((*pots)[i + j] != rule[j + 2]) {
					fits = false;
					break;
				}
			}
			if (fits) {
				fits = false;
				(*returnPots)[i] = rule[5];
				break;
			}
		}if (fits) {
			(*returnPots)[i] = false;
		}
	}
	delete pots;
	return returnPots;

}


void twelfth_day_func() {

	ifstream myfile;
	myfile.open("twelfth_day_input.txt");
	string input;

	array<array<bool, 6>, RULES> rules; // rules contain the combination of 5 pots and the resulting plant in that pot
	array<bool, INITIAL + GENERATIONS>* pots = new array<bool, INITIAL + GENERATIONS>; // 200 because there are 100 pots noted in input that might have plants, and then they might grow at most 40 in each direction during 20 generations.
	pots->fill(false);

	getline(myfile, input); // start state
	for (int i = 15; i < INITIAL + 15; ++i) {
		(*pots)[i - 13] = (input[i] == '#');
	}

	getline(myfile, input); // empty line
	for (int i = 0; i < RULES; ++i) {
		getline(myfile, input); // rule
		for (int j = 0; j < 5; ++j) {
			rules[i][j] = (input[j] == '#');
		}
		rules[i][5] = input[9] == '#';
	}

	for (int i = 0; i < GENERATIONS; ++i) {
		cout << "generation: " << i << endl;
		for (int j = 0; j < INITIAL + GENERATIONS; ++j) {

			cout << (*pots)[j];
		}
		cout << endl;
		pots = proceedGeneration(pots, rules);
		if (i == 98)
			break;

	}
	long long int test = 0;
	int counter = 0;
	cout << "generation: " << GENERATIONS << endl;
	for (int i = 0; i < 300; ++i) {
		if ((*pots)[i]) {
			test += i - 1 + (50000000000 - 98);
			counter++;
		}
	}
	cout << counter << endl;

	//181, 184, 190

	long long int answer = 57 * ((50000000000 - 98 + 2 + 50000000000 - 98 + 173)) / 2;
	answer += 181 + (50000000000 - 98);
	answer += 184 + (50000000000 - 98);
	answer += 190 + (50000000000 - 98);
	cout << answer << endl;
	cout << test << endl;

	//249374999511225 not right
	//277124999456835 not right
	//4524999996673 not right
	//3049999999774 not right
	//3049999999713 not right
	//3049999999652  not right
	//3000000000232 not right
	//2999999999662 not right
}