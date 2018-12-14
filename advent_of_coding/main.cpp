#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <array>

#include "first_day.h"
#include "second_day.h"
#include "third_day.h"
#include "fourth_day.h"
#include "fifth_day.h"
#include "sixth_day.h"
#include "seventh_day.h"
#include "eight_day.h"
#include "ninth_day.h"
#include "tenth_day.h"
#include "eleventh_day.h"
#include "twelfth_day.h"
using namespace std;

void replaceCart(vector<string*>& map, int x, int y) {
	char up, right, down, left;

	if (x == 0)
		left = map.at(y)->at(x);
	else
		left = map.at(y)->at(x-1);

	if(x == map.at(y)->size()-1)
		right = map.at(y)->at(x);
	else
		right = map.at(y)->at(x+1);

	if(y == 0)
		up = map.at(y)->at(x);
	else
		up = map.at(y-1)->at(x);

	if (y == map.size() - 1)
		down = map.at(y)->at(x);
	else
		down = map.at(y + 1)->at(x);

	if (up == '|' || up == '+' || up == '\\' || up == '/')
		if (down == '|' || down == '+' || down == '\\' || down == '/')
			if (right == '-' || right == '+' || right == '\\' || right == '/')
				map.at(y)->at(x) = '+';
			else
				map.at(y)->at(x) = '|';
		else if (right == '-' || right == '+' || right == '\\' || right == '/')
			map.at(y)->at(x) = '\\';
		else
			map.at(y)->at(x) = '/';
	else
		map.at(y)->at(x) = '-';
}

#define Direction int
#define Turn int
#define Updated bool
vector < tuple<int, int, Turn, Direction, Updated>*> findCarts(vector<string*>& map) {
	vector<tuple<int, int, Turn, Direction, Updated>*> retVal;
	for (int y = 0; y < map.size(); ++y) {
		string* row = map.at(y);
		for (int x = 0; x < row->size(); ++x) {
			if (row->at(x) == '^') {
				replaceCart(map, x, y);
				retVal.push_back(new tuple<int, int, Turn, Direction, Updated>{x, y, -1, 0, false});
			}
			if (row->at(x) == '>') {
				replaceCart(map, x, y);
				retVal.push_back(new tuple<int, int, Turn, Direction, Updated>{x, y, -1, 1, false});
			}
			if (row->at(x) == 'v') {
				replaceCart(map, x, y);
				retVal.push_back(new tuple<int, int, Turn, Direction, Updated>{x, y, -1, 2, false});
			}
			if (row->at(x) == '<') {
				replaceCart(map, x, y);
				retVal.push_back(new tuple<int, int, Turn, Direction, Updated>{x, y, -1, 3, false});
			}
			
			
		}
	}
	
	return retVal;
}

void tick(vector<tuple<int, int, Turn, Direction, Updated>*> carts, vector<string*> map) {
	for (int y = 0; y < map.size(); ++y) {
		string row = *map.at(y);
		for (int x = 0; x < row.size(); ++x) {
			for (auto cart : carts) {
				auto& cartX = get<0>(*cart);
				auto& cartY = get<1>(*cart);
				Turn& turn = get<2>(*cart);
				Direction& dir = get<3>(*cart);
				Updated& updated = get<4>(*cart);
				if (cartX == x && cartY == y && !updated) {
					updated = true;
					cout << "x was " << cartX << " and y was " << cartY << endl;
					if (dir == 0) {
						cartY--;
					}
					if (dir == 1) {
						cartX++;
					}
					if (dir == 2) {
						cartY++;
					}
					if (dir == 3) {
						cartX--;
					}
					char rail = map.at(cartX)->at(cartY);
					cout << "x is " << cartX << " and y is " << cartY << endl;
					if (rail == '+') {
						dir += turn;
						if (dir > 3)
							dir = 0;
						else if (dir < 0)
							dir = 3;
						turn++;
						if (turn == 2)
							turn = -1;
					}
					else if (rail == '\\') {
						if (dir == 3)
							dir = 0;
						else if (dir == 2)
							dir = 1;
						else if (dir == 1)
							dir = 2;
						else if (dir == 0)
							dir = 3;
						else
							cout << "Something went terribly wrong in a \\ intersection" << endl;
					}
					else if (rail == '/') {
						if (dir == 0)
							dir = 1;
						else if (dir == 1)
							dir = 0;
						else if (dir == 2) {
							dir = 3;
						}
						else if (dir == 3)
							dir = 2;
						else
							cout << "Something went terribly wrong in a / intersection" << endl;
					}

				}
			}
		}
	}
	for (auto cart : carts)
		get<4>(*cart) = false;
	cout << endl;
}

int main() {
	//twelfth_day_func();

	ifstream myfile;
	myfile.open("thirteenth_test_1.txt");
	string input;

	vector<string*> map;
	while (getline(myfile, input)) {
		map.push_back(new string{ input });
	}
	
	vector<tuple<int,int,Turn,Direction, Updated>*> carts = findCarts(map);
	
	for (auto row : map)
		cout << *row << endl;

	tick(carts, map);
	//tick(carts, map);
	//tick(carts, map);
	//tick(carts, map);

	system("pause");
	return 0;
}