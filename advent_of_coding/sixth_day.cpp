#include "sixth_day.h"


int manhattanDistance(pair<int, int>* a, pair<int, int>* b) {
	return abs(a->first - b->first) + abs(a->second - b->second);
}

void sixth_day_func() {
	ifstream myfile;
	string input;
	myfile.open("sixth_day_input.txt");
	int x, y;
	char comma;
	vector<pair<int, int>*> locations;

	//myfile >> z;
	while (myfile >> x) {
		myfile >> comma;
		myfile >> y;
		//cout << x << " " << comma << " " << y << endl;
		locations.push_back(new pair<int, int>{ x,y });


	}

	//Biggest x and y values are: x = 313, y = 342
	const int xDim = 313;
	const int yDim = 342;
	array<array < pair<int, int>, yDim>*, xDim>* field = new array<array < pair<int, int>, yDim>*, xDim>;
	for (int i = 0; i < xDim; ++i) {
		field->at(i) = new array < pair<int, int>, yDim>;
		//field->at(i)->fill(pair<int, int>{1000, 1000});
		field->at(i)->fill(pair<int, int>{0, 0});
		for (int j = 0; j < yDim; ++j) {
			bool tied = false;
			for (int k = 0; k < locations.size(); ++k) {
				pair<int, int> temp{ i,j };
				pair<int, int> highest = field->at(i)->at(j);
				int distance = manhattanDistance(locations.at(k), &temp);
				/*if (distance < highest.second) {
					field->at(i)->at(j).first = k + 1;
					field->at(i)->at(j).second = distance;
					tied = false;
				}
				else if (distance <= highest.second){
					field->at(i)->at(j).first = k + 1;
					field->at(i)->at(j).second = distance;
					tied = true;
				}*/
				field->at(i)->at(j).first += distance;
			}
			/*if (tied) {
				field->at(i)->at(j).first = locations.size()+1;
				field->at(i)->at(j).second = 0;
			}*/
			//cout << (char)field->at(i)->at(j).first;// << endl;
		}
		//cout << endl;
	}

	array<int, 51> count;
	count.fill(0);
	int highscore = 0;
	for (int i = 0; i < xDim; ++i) {
		for (int j = 0; j < yDim; ++j) {
			/*
			if (i == 0 || i == xDim - 1 || j == 0 || j == yDim - 1) {
				count[field->at(i)->at(j).first - 1] -= 10000;

			}
			else {
				count[field->at(i)->at(j).first - 1]++;
			}*/
			if (field->at(i)->at(j).first < 10000) {
				highscore++;
			}
		}
	}
	/*cout << "mapped" << endl;

	for (auto a : count) {
		if (a > highscore) {
			highscore = a;
		}
	}*/
	cout << highscore << endl;
}