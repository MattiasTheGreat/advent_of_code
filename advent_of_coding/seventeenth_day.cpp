#include "seventeenth_day.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>

using namespace std;

const int DEPTH = 2054;// 14; //2054;
const int WIDTH = 186;// 12; //186; 
const int WIDTH_START = 333;// 495; // 333; 

void printSlice(array<array < char, WIDTH >*, DEPTH>* slice) {
	int rowCount = 0;
	system("cls");
	for (auto row : *slice) {
		cout << rowCount << (rowCount < 10 ? "  " : " ");
		rowCount++;
		for (int i = 0; i < row->size(); ++i) {
			cout << row->at(i);
		}cout << endl;
	}
	cout << endl;
	//system("pause");
	
}

void bigPrint(array<array < char, WIDTH >*, DEPTH>* slice, int x, int  y) {

	system("cls");
	for (int i = y - 10; i < y + 2; ++i) {
		if (i >= 0 && i <DEPTH) {
			auto row = slice->at(i);
			for (int j = x - 15; j < x + 15; ++j) {
				if (j >= 0 && j < WIDTH) {
					cout << row->at(j);
				}
				
			}cout << endl;
		}
		
	}
	
	system("pause");
	
}

//Values are: bool = any branch reached bottom? int = number of waters in branch
pair<bool, int> fillWater(int x, int y, array<array < char, WIDTH >*, DEPTH>* slice) {
	bigPrint( slice, x, y);
	if(y == DEPTH - 1){
		slice->at(y)->at(x) = '~';
		//printSlice(slice);
		return pair<bool, int> {true, 1};
	}
	else {
		// Node directly below
		
		slice->at(y)->at(x) = '~';
		//printSlice(slice);
		if (slice->at(y + 1)->at(x) == '.') {

			// check tile below
			//cout << "branching down" << endl;
			pair<bool, int> below = fillWater(x, y + 1, slice);
			if (!below.first) {
				// If below ran into walls we want to branch out too

				// Left:
				pair<bool, int> left{ false,0 };
				if (x > 0) {
					if (slice->at(y)->at(x - 1) == '.') {
						//cout << "branching left" << endl;
						left = fillWater(x - 1, y, slice);
					}
					//else
						//cout << "couldnt branch left" << endl;
				}

				// Right:
				pair<bool, int> right{ false,0 };
				if (x < WIDTH - 1) {
					if (slice->at(y)->at(x + 1) == '.') {
						//cout << "branching right" << endl;
						right = fillWater(x + 1, y, slice);
					}
					//else
						//cout << "couldnt branch right" << endl;
				}
				// If any branch reaches bottom, above should not branch.
				
				return pair<bool, int>{left.first || right.first, left.second + right.second + +below.second + 1};
			}
			return pair<bool, int> {true, below.second + 1};
		}
		else {
			// If at a floor, check to the left and right.
			
			//cout << "couldnt branch down" << endl;
			// Left:
			pair<bool, int> left{false,0};
			if(x > 0){
				if (slice->at(y)->at(x - 1) == '.') {
				//	cout << "branching left" << endl;
					left = fillWater(x - 1, y, slice);
				}
				//else
					//cout << "couldnt branch left" << endl;
			}

			// Right:
 			pair<bool, int> right{ false,0 };
			if (x < WIDTH - 1) {
				if (slice->at(y)->at(x + 1) == '.') {
					//cout << "branching right" << endl;
					right = fillWater(x + 1, y, slice);
				}
				//else
				//cout << "couldnt branch right" << endl;
			}
			// If any branch reaches bottom, above should not branch.
			return pair<bool, int>{left.first || right.first, left.second + right.second + 1};
		}
	}
}

void seventeenth_day_func() {
	ifstream myfile;

	int testCase = 0;

	if (testCase == 0)
		myfile.open("seventeenth_day_input.txt");
	else if (testCase == 1)
		myfile.open("seventeenth_test.txt");

	char dimension;
	vector <pair<int, pair<int, int>>> hashtags;
	int value, valueRange1, valueRange2;
	char equalSign;
	char spacer;

	int highestX = 0;
	int highestY = 0;
	int lowestX = 1000;


	// Lowest c is 333, highest x is 518 => x-dim should be 185 large. Highest y is 2053, so we make it one larger in each dimension: 186:2054;
	array<array < char, WIDTH >*, DEPTH>* slice = new array<array < char, WIDTH >*, DEPTH>;
	for (int i = 0; i < slice->size(); ++i) {
		slice->at(i) = new array<char, WIDTH>;
		slice->at(i)->fill('.');
	}

	while (myfile >> dimension) {
		//cout << dimension << " ";

		myfile >> equalSign;
		myfile >> value;

		/*if (dimension == 'x') {
			if (value > highestX)
				highestX = value;

			if (value < lowestX)
				lowestX = value;
		}
		else {
			if (value > highestY)
				highestY = value;
		}*/

		myfile >> spacer;

		myfile >> dimension;
		myfile >> equalSign;
		myfile >> valueRange1;
		myfile >> spacer;
		myfile >> spacer;
		myfile >> valueRange2;
		//cout << value << " " << dimension << " " << valueRange1 << " " << valueRange2 << endl;
		if (dimension == 'x') {
			for (int i = valueRange1; i <= valueRange2; ++i) {
				//cout << "dim is x: " << value << " " << i - WIDTH_START << endl;
				slice->at(value)->at(i - WIDTH_START) = '#';
			}
		}
		else {
			for (int i = valueRange1; i <= valueRange2; ++i) {
				//cout << "dim is y: " << i << " " << value - WIDTH_START << endl;
				auto test = slice->at(i)->at(value - WIDTH_START) = '#';
			}
		}
		/*if (dimension == 'x') {
			if (valueRange2 > highestX)
				highestX = valueRange2;
			if (valueRange1 < lowestX)
				lowestX = valueRange1;
		}
		else {
			if (valueRange2 > highestY)
				highestY = valueRange2;
		}
		^*/
	}
	cout << "inputed" << endl;

	for (int i = 0; i < 22; ++i) {
		cout << "|" << endl;
	}
	system("pause");
	//printSlice(slice);
	/*
	struct Node {
		Node* previous;

		int x;
		int y;

		bool aboveNode;
		int value;
		int done; //0 nothing done, //1: below branch done, 2: right branch also done, 3: all branches
		bool doned;
	};

	Node* start = new Node;
	start->previous = start;
	
	start->x = 500 - WIDTH_START;
	start->y = 0;
	start->value = 1;
	start->done = 0;
	
	start->doned = false;
	
	Node* current = start;
	bool doneBranch = false;

	int printer = 0;
	bool bottom = false;

	while (start->done != 3) {
		if (printer % 50 == 0 && bottom) {
			bigPrint(slice, current->y);
			printer++;
		}
		//printSlice(slice);
		//cout << "current location: " << current->x << " " << current->y << " with done value: " << current->done << " and branchdone: " << doneBranch << " and value: " << current->value << endl;
		if (current->done == 3) {
			current->previous->value += current->value;
			if (current->doned)
				doneBranch = true;

			if (current->previous->aboveNode && doneBranch) {
				//cout << "setting above to done" << endl;
				current->previous->done = 3;
				current->previous->doned = true;
			}
			Node* temp = current;
			current = current->previous;
			delete temp;
			
		}
		else {
			int x = current->x;
			int y = current->y;
			
			if (current->y == DEPTH - 1) {
				slice->at(y)->at(x) = '~';
				current = current->previous;
				current->value = 2;
				doneBranch = true;
			}
			else {

				// Below
				if (current->done == 0) {
					slice->at(y)->at(x) = '~';
					//cout << "sat value to ~" << endl;
					if (slice->at(y + 1)->at(x) == '.') {
						current->aboveNode = true;
						current->done++;
						Node* newNode = new Node{current, x, y+1, false, 1, 0, false};
						current = newNode;
						printer++;
						//cout << "changed node" << endl;

					}
					else {
						current->done++;
					}
				}
				else {
					// If ive only branched downards, and he's done done, we shouldnt branch left and right.
					current->aboveNode = false;
					if (current->previous->aboveNode && doneBranch) {
						//cout << "setting above to done" << endl;
						current->previous->done = 3;
						current->previous->doned = true;
					}
					if (doneBranch && current->done == 1) {
						current->previous->value += current->value;
						current = current->previous;
					}
					else {

						if (current->done == 1) {
							if (x < WIDTH - 1) {
								if (slice->at(y)->at(x + 1) == '.') {
									current->done++;
									Node* newNode = new Node{ current, x + 1, y, false, 1, 0, false };
									current = newNode;
									printer++;
								}
								else {
									current->done++;
								}
							}
							if (doneBranch) {
								//cout << "donebranch is and we're branching left. Should NOT happen\n";
							}
						}
						else if (current->done == 2) {
							if (x > 0) {
								if (slice->at(y)->at(x - 1) == '.') {
									current->done++;
									Node* newNode = new Node{ current, x - 1, y, false, 1, 0, false};
									current = newNode;
									doneBranch = false;
									printer++;
								}
								else {
									current->done++;
								}
							}
						}
						
					}

				}
			}
		}
		//cout << "Is start done? 3 == " << start->done << endl;
		if (current->y % 100 == 0) {
			cout << current->y << endl;
		}
		if ( current->y > 1900) {
			bottom = true;
		}
		
	}
	cout << "Answer: " << start->value << endl;
	*/


	//pair<bool, int> result = fillWater(499 - WIDTH_START, 0, slice);
	//cout << endl <<  result.second << endl;

	struct Delver {
		int x;
		int y;
		char mode;
		bool doneBranch;
		int delves;
		};

	Delver delly{ 498 - WIDTH_START, 1, 'v', false, 0};

	int stopMotion = 0;
	while (delly.x != 500 - WIDTH_START || delly.y != 0) {
		int x = delly.x;
		int y = delly.y;
		//cout << "done branch: " << delly.doneBranch << endl;
		if (slice->at(y)->at(x) != '.') {
			char current = slice->at(y)->at(x);
			
			if (current == 'v') {
				//cout << "backing up" << endl;
				if (delly.doneBranch) {
					if (delly.x > 0 && slice->at(y)->at(x - 1) == '.' && delly.x < WIDTH - 1 && slice->at(y)->at(x + 1) == '>') {
						//cout << "Left!\n";
						delly.x--;
						delly.mode = '<';
					}
					else
						delly.y--;
				}else if (delly.x < WIDTH - 1 && slice->at(y)->at(x + 1) == '.' && !delly.doneBranch) {
					//cout << "Right!\n";
					delly.x++;
					delly.mode = '>';
				}else if (delly.x > 0 && slice->at(y)->at(x - 1) == '.') {
					//cout << "Left!\n";
					delly.x--;
					delly.mode = '<';
				}
				else {
					delly.y--;
				}
			}
			else if (current == '<') {
				cout << "backing up into >" << endl;
				system("pause");
				if (delly.x < WIDTH - 1 && slice->at(y)->at(x - 1) == '.') {
					delly.x--;
					delly.mode = '>';
				}
				else
					delly.x++;

			}
			else if (current == '>') {
				cout << "backing up into >" << endl;
				system("pause");
				if (delly.x > 0 && slice->at(y)->at(x + 1) == '.') {
					delly.x++;
					delly.mode = '>';
				}
				else
					delly.x--;
			}
			else {
				cout << "Unspecified mode, delvy confused\n";
				cout << "Delvy stats:\n";
				cout << "x: " << delly.x << endl;
				cout << "y: " << delly.y << endl;
				cout << "mode: " << delly.mode << endl;
				cout << "doneBranch: " << delly.doneBranch << endl;
				cout << "delves: " << delly.delves << endl;
				system("pause");
			}
			
		}
		else {
			
			delly.delves++;
			slice->at(y)->at(x) = delly.mode;
			if (y < DEPTH - 1) {
				if (slice->at(y + 1)->at(x) == '.') {
					//cout << "Below!\n";
					delly.y++;
					delly.mode = 'v';
				}
				else {
					//cout << "not below..\n";
					if (delly.x < WIDTH - 1 && slice->at(y)->at(x + 1) == '.') {
						//cout << "Right!\n";
						
						delly.x++;
						delly.mode = '>';
					}
					else if (delly.x > 0 && slice->at(y)->at(x - 1) == '.') {
						//cout << "Left!\n";
						delly.x--;
						delly.mode = '<';
					}
				}
				
			}
			else {
				delly.doneBranch = true;
			}
		}
		
		if (stopMotion % 1 == 0) {
			char temp = slice->at(delly.y)->at(delly.x);
			slice->at(delly.y)->at(delly.x) = 'x';
			bigPrint(slice, delly.x, delly.y);
			slice->at(delly.y)->at(delly.x) = temp;

			
		}
		stopMotion++;
	}
	cout << "delves: " << delly.delves << endl;
	
	//25804 too low
	
}