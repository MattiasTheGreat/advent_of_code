#include "fifteenth_day.h"
#include <vector>
#include <iostream>

using namespace std;

void fifteenth_day_func() {
	vector<int> recipies;
	const int inputSize = 509671;
	int input2[6] = { 5,1,5,8,9 };//{ 5,0,9,6,7,1 };
	int elf1 = 0;
	int elf2 = 1;

	recipies.push_back(3);
	recipies.push_back(7);

	while (recipies.size() < inputSize + 10) {
		int recipie1 = recipies.at(elf1);
		int recipie2 = recipies.at(elf2);
		int sum = recipie1 + recipie2;
		if (sum >= 10) {
			recipies.push_back(sum / 10);
			recipies.push_back(sum - 10);
		}
		else {
			recipies.push_back(sum);
		}
		elf1 = ((elf1 + recipie1 + 1) % recipies.size()) ;
		elf2 = ((elf2 + recipie2 + 1) % recipies.size()) ;

		// Part 2
		int size = recipies.size();
		if (size > 6) {
			if (size == 15 || size == 16) {
				cout << (recipies[size - 6] == input2[0]) << " " <<
					(recipies[size - 5] == input2[1]) << " " <<
					(recipies[size - 4] == input2[2]) << " " <<
					(recipies[size - 3] == input2[3]) << " " <<
					(recipies[size - 2] == input2[4]) << " " <<
					(recipies[size - 1] == input2[5]) << " " <<
					(recipies[size - 7] == input2[0]) << " " <<
					(recipies[size - 6] == input2[1]) << " " <<
					(recipies[size - 5] == input2[2]) << " " <<
					(recipies[size - 4] == input2[3]) << " " <<
					(recipies[size - 3] == input2[4]) << " " <<
					(recipies[size - 2] == input2[5]) << endl;
			}
			if ((recipies[size - 6] == input2[0] &&
				recipies[size - 5] == input2[1] &&
				recipies[size - 4] == input2[2] &&
				recipies[size - 3] == input2[3] &&
				recipies[size - 2] == input2[4] &&
				recipies[size - 1] == input2[5]) ||
				(recipies[size - 7] == input2[0] &&
				recipies[size - 6] == input2[1] &&
				recipies[size - 5] == input2[2] &&
				recipies[size - 4] == input2[3] &&
				recipies[size - 3] == input2[4] &&
				recipies[size - 2] == input2[5]))
				break;
		}
	}
	cout << recipies.size() << endl;
	
	/*
	for (int i = recipies.size() - 10;  i < recipies.size(); ++i) {
		cout << recipies.at(i) << " ";
	}
	cout << endl;*/

}