#include "third_day.h"
#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void third_day_func() {


	array<array<int, 2000>*, 2000>* fabric = new array<array<int, 2000>*, 2000>;
	for (int i = 0; i < 2000; ++i) {
		fabric->at(i) = new array<int, 2000>;
		for (int j = 0; j < 2000; ++j) {
			fabric->at(i)->at(j) = 0;
		}
	}
	ifstream myfile;
	string input;
	myfile.open("third_day_input.txt");
	char distances[10];
	char dimentions[10];
	char garbage;
	int ID;
	int distX, distY;
	int dimX, dimY;

	struct claim {
		int ID;
		int distX;
		int distY;
		int dimX;
		int dimY;
	};
	vector<claim*> claims;

	while (myfile >> garbage) {
		
		myfile >> ID;
		myfile >> garbage; //@
		myfile >> distX;
		myfile >> garbage; //,
		myfile >> distY;
		myfile >> garbage; //:
		myfile >> dimX;
		myfile >> garbage; //x
		myfile >> dimY;

		claim* c = new claim{ID,distX,distY,dimX,dimY};
		claims.push_back(c);

		//cout  << dimX << " " << dimY << endl;
		//cout << distX << " " << distY << endl;


		for (int i = distX; i < distX + dimX; ++i) {
			for (int j = distY; j < distY + dimY; ++j) {
				fabric->at(i)->at(j)++;


			}
		}
	}
	int noOverlapID = -1;
	for (auto c : claims) {
		bool overlap = false;
		for (int i = c->distX; i < c->distX + c->dimX; ++i) {
			for (int j = c->distY; j < c->distY + c->dimY; ++j) {
				if (fabric->at(i)->at(j) != 1) {
					overlap = true;
				}


			}
		}
		if (!overlap) {
			noOverlapID = c->ID;
			cout << noOverlapID << endl;
		}
	}
	
	int counter{ 0 };
	for (int i = 0; i < 1000; ++i) {
		for (int j = 0; j < 1000; ++j) {
			if (fabric->at(i)->at(j) > 1)
				counter++;
		}
	}
	cout << "overlaps: " << counter << " and the claim with no overlap is: " << noOverlapID << endl;


}