#pragma once
#include "second_day.h"
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

using namespace std;

void second_day_func() {
	ifstream myfile;
	string input;
	myfile.open("second_day_input.txt");
	int doubles = 0;
	int triples = 0;
	bool doubled = false;
	bool tripled = false;
	vector<string> list;
	while (getline(myfile, input)) {
		//cout << input << endl;
		list.push_back(input);
		auto it = input.begin();
		map<char,int> counter;
		
		while (it != input.end()) {
			//cout << *it  << endl;
			counter[*it]++;
			++it;
		}
		auto mapIt = counter.begin();
		while (mapIt != counter.end()) {
			if (mapIt->second == 2) {
				if(!doubled)
					doubles++;
				doubled = true;
			}
			else if (mapIt->second == 3) {
				if (!tripled)
					triples++;
				tripled = false;
			}
			mapIt++;
		}
		doubled = false;
		tripled = false;
	}
	cout << "Doubles: " << doubles << ", Triples: " << triples << ", product: " << doubles*triples << endl;

	int difference = 0;
	int i = 0;
	int j{ 0 };
	for (i = 0; i < list.size(); ++i) {
		for (j = i + 1; j < list.size(); ++j) {
			for (int k = 0; k < list[i].size(); ++k) {
				if (list[i][k] != list[j][k])
					difference++;
			}
			if (difference == 1)
				break;
			difference = 0;
		}
		if (difference == 1)
			break;
	}
	cout << "Words for i = " << i << ": " << list[i] << " and j = " << j << ": " << list[j] << " are very close!\n" << list[i] << endl << list[j] << endl;
	system("pause");
}