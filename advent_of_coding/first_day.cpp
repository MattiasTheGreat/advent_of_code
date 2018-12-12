#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include "first_day.h"

using namespace std;

void first_day_func() {
	ifstream myfile;
	//myfile.open("input.txt");
	int input;
	int result = 0;
	map<int, int> test;
	bool done = false;
	++test[result];
	while (!done) {
		myfile.open("input.txt");

		while (myfile >> input) {

			printf("%i, %i\n", result, test[result]);
			result += input;
			if (++test[result] == 2) {
				done = true;
				break;
			}

		}
		myfile.close();
		//system("pause");
	}
	printf("%i\n", result);
	system("pause");
}