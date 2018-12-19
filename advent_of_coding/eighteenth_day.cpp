#include "eighteenth_day.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <array>

using namespace std;

struct Acre {
	char current;
	char next;
};

int countNeighbours(vector<vector<Acre*>*>& map, int x, int y, char type) {
	int counter = 0;
	for (int i = y - 1; i <= y + 1; ++i) {
		if(i >= 0 && i < map.size()){
			for (int j = x - 1; j <= x + 1; ++j) {
				if (j >= 0 && j < map.at(i)->size()) {
					if (!(i == y && j == x)) {
						if (map.at(i)->at(j)->current == type) {
							counter++;
						}
					}
				}
			}
		}
	}
	return counter;
}

void printMap(vector<vector<Acre*>*> map) {
	for (auto row : map) {
		for (auto acre : *row) {
			cout << acre->current;
		}cout << endl;
	}
}

void eighteenth_day_func() {
	ifstream myfile;
	
	int testCase = 0;

	if (testCase == 0)
		myfile.open("eighteenth_day_input.txt");

	vector<vector<Acre*>*> map;
	string input;

	array<int, 28> recuringResults;
	recuringResults.fill(0);

	while (getline(myfile, input)) {
		cout << input << endl;
		vector<Acre*>* row = new vector<Acre*>;
		for (auto c : input) {
			row->push_back(new Acre{ c,'0' });


		}
		map.push_back(row);
	}

	for (int i = 0; i < 1000000000; ++i) {
		for (int y = 0; y < map.size(); ++y) {
			auto row = map.at(y);
			for (int x = 0; x < row->size(); ++x) {
				auto acre = row->at(x);
				if (acre->current == '.') {
					if (countNeighbours(map, x, y, '|') >= 3) {
						acre->next = '|';
					}
					else {
						acre->next = '.';
					}
				}
				else if (acre->current == '|') {
					if (countNeighbours(map, x, y, '#') >= 3) {
						acre->next = '#';
					}
					else {
						acre->next = '|';
					}
				}
				else if (acre->current == '#') {
					if (countNeighbours(map, x, y, '#') >= 1 && countNeighbours(map, x, y, '|') >= 1) {
						acre->next = '#';
					}
					else {
						acre->next = '.';
					}
				}
			}
		}
		for (auto row : map) {
			for (auto acre : *row) {
				acre->current = acre->next;
			}
		}
		if (i >= 499) {
			//printMap(map);
			
			cout << i << endl;
			int woods = 0;
			int lumberyards = 0;
			for (auto row : map) {
				for (auto acre : *row) {
					if (acre->current == '|') {
						woods++;

					}
					else if (acre->current == '#') {
						lumberyards++;
					}
				}
			}
			recuringResults[i % 28] = woods * lumberyards;
			for (int j = 0; j < 28; ++j)
				cout << recuringResults[j] << endl;
			cout << endl << endl << "ANSWER IS: " << recuringResults[1000000000 % 28] << endl;
			cout << woods << " " << lumberyards << " Combined: " << woods * lumberyards << endl;
			system("pause");
		}
		

	}
	int woods = 0;
	int lumberyards = 0;
	for (auto row : map) {
		for (auto acre : *row) {
			if (acre->current == '|'){
				woods++;

			}
			else if (acre->current == '#') {
				lumberyards++;
			}
		}
	}
	cout << woods << " " << lumberyards << " Combined: " << woods * lumberyards << endl;

	/*
	206987
	207172
	202464
	204559
	202852                                                                                                                  
	206180                                                                                                                  
	204462                                                                                                                  
	207807                                                                                                                 
	206695                                                                                                                  
	210056                                                                                                                  
	208656                                                                                                                  
	211420                                                                                                                  
	212553                                                                                                                  
	216032                                                                                                                  
	215900                                                                                                                  
	221386                                                                                                                  
	221921                                                                                                                  
	227448                                                                                                                  
	226630                                                                                                                  
	233058  //RIGHT!                                                                                                           
	229803 //not right, too low                                                                                                                  
	233772  //not right, too high                                                                                                                 
	231040                                                                                                                  
	232988                                                                                                                  
	226772                                                                                                                  
	225584                                                                                                                  
	215683                                                                                                                  
	213312
	*/
}