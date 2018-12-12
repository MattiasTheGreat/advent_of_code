#include "seventh_day.h"
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <array>

using namespace std;
void seventh_day_func() {

	ifstream myfile;
	string input;
	myfile.open("seventh_day_input.txt");

	struct Connections {
		set<char>* before;
	};
	const int WORKERS = 5;
	const int TIME = 60;
	int workers[5] = { 0,0,0,0,0 };
	char work[5];
	set<char> nodes;
	map <char, Connections*> connections;
	while (getline(myfile, input)) {
		char first = input[5];
		char second = input[36];
		nodes.insert(first);
		nodes.insert(second);
		//cout << input << " " << input[5] << " " << input[36] << " " << (input[5] < input[36]) << (second == 'H' ? " BBBB":"") << endl;
		if (connections.count(second) > 0) {
			connections.at(second)->before->insert(first);
		}
		else {
			connections.insert(pair<char, Connections*>{second, new Connections{ new set<char> }});
			connections.at(second)->before->insert(first);
		}
	}
	int seconds = 0;
	while (!nodes.empty()) {
		for (int i = 0; i < WORKERS; ++i) {
			if (workers[i] <= 0) {
				for (auto p : nodes) {
					if (connections.find(p) != connections.end()) {
					}
					else {


						workers[i] = p - 'A' + 1 + TIME;
						//cout << "started working on " << p << " which is gonna take " << workers[i] << endl;
						work[i] = p;
						nodes.erase(p);
						break;
					}

				}
			}
		}
		seconds++;
		cout << "second " << seconds;
		for (int j = 0; j < WORKERS; ++j) {
			cout << " worker" << j << " " << (workers[j] > 0 ? work[j] : '.');
		}
		cout << endl;
		for (int i = 0; i < WORKERS; ++i) {
			workers[i]--;
			if (workers[i] == 0) {
				cout << work[i];// << endl;

				for (auto it = connections.begin(); it != connections.end();) {
					/*cout << it->first << ": ";
					for (auto i : *(it->second->before)) {

						cout << i;
					}
					cout << endl;*/
					it->second->before->erase(work[i]);
					if (it->second->before->empty()) {
						connections.erase(it++);
					}
					else {
						++it;
					}
				}
			}
		}
	}
	cout << endl;
	for (int i = 0; i < WORKERS; ++i) {
		if (workers[i] > 0) {
			cout << work[i] << " didn't finish with " << workers[i] << " seconds left";
		}
	}
	while (workers[0] > 0 || workers[1] > 0 || workers[2] > 0 || workers[3] > 0 || workers[4] > 0) {
		workers[0]--;
		workers[1]--;
		workers[2]--;
		workers[3]--;
		workers[4]--;

	}
	cout << endl;

}