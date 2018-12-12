#include "tenth_day.h"
#include "sixth_day.h"

using namespace std;

bool isMessage(vector<pair<int, int>*> position) {
	for (int i = 0; i < position.size(); ++i) {
		for (int j = i + 1; j < position.size(); ++j) {
			if (manhattanDistance(position.at(i), position.at(j)) > 90) {
				return false;
			}
		}
	}
	return true;
}

void tick(vector<pair<int, int>*>& position, vector<pair<int, int>*>& vector) {
	for (int i = 0; i < position.size(); ++i) {
		position.at(i)->first += vector.at(i)->first;
		position.at(i)->second += vector.at(i)->second;

		if (i == 0) {
			//cout << "First dot moves: " << position.at(i)->first << " " << position.at(i)->second << endl;
		}
	}
}

void tenth_day_func(){
	ifstream myfile;
	string input;
	myfile.open("tenth_day_input.txt");
	int posX, posY;
	int velX, velY;
	int test, test2;
	char comma;

	vector<pair<int, int>*> position;
	vector<pair<int, int>*> velocity;
	myfile.seekg(10, ios::cur);
	while (myfile >> posX >> comma >> posY) {
		myfile.seekg(12, ios::cur);
		myfile >> velX >> comma >> velY;
		myfile.seekg(13, ios::cur);

		position.push_back(new pair<int, int>{ posX,posY });
		velocity.push_back(new pair<int, int>{ velX,velY });
	}
	int counter = 0;
	while (!isMessage(position)) {
		tick(position, velocity);
		counter++;
	}

	int leastX{ 100000 }, leastY{ 1000000 }, mostX{ 0 }, mostY{ -1000000 };
	for (auto pos : position) {
		if (pos->first > mostX) {
			mostX = pos->first;
		}
		if (pos->first < leastX) {
			leastX = pos->first;
		}
		if (pos->second > mostY) {
			mostY = pos->second;
		}
		if (pos->second < leastY) {
			leastY = pos->second;
		}
	}

	bool printed = false;
	while (true) {
		for (int i = leastX; i < mostX; ++i) {
			for (int j = leastY; j < mostY; ++j) {
				for (auto pos : position) {
					if (pos->first == i && pos->second == j && !printed) {
						cout << "#";
						printed = true;
					}
				}
				if (!printed) {
					cout << ".";
				}
				printed = false;

			}
			cout << endl;
		}
		cout << counter << endl;
		system("pause");
		tick(position, velocity);
		counter++;
	}

	cout << leastX << ":" << mostX << " " << leastY << ":" << mostY;
}