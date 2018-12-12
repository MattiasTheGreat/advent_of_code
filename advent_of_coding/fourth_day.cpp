#include "fourth_day.h"
#include <fstream>
#include <string>
#include "vector"
#include <array>
#include <iostream>

using namespace std;

void fourth_day_func() {
	ifstream myfile;
	string input;
	myfile.open("fourth_day_input.txt");
	vector<string> inputs;
	int counter = 0;
	while (getline(myfile, input)) {
		inputs.push_back(input);
		//cout << counter << " " << input << endl;
		counter++;
	}
	sort(inputs.begin(), inputs.end());

	array<array<int, 60>*, 4000>* guardSleep = new array<array<int, 60>*, 4000>;
	for (int i = 0; i < 4000; ++i) {
		guardSleep->at(i) = new array<int, 60>;
		guardSleep->at(i)->fill(0);
	}

	array<int, 4000>* amountSleep = new array<int, 4000>;
	amountSleep->fill(0);
	int guardID;
	int fallAsleepTime;
	for (string inp : inputs) {
		//cout << inp << endl;
		if (inp.find("Guard") != string::npos) {
			int startOfNumber = inp.find("#") + 1;
			int endOfNumber = inp.find("b") - 1 - startOfNumber;
			guardID = stoi(inp.substr(startOfNumber, endOfNumber));
			//cout << "Guard: " << guardID << endl;

		}
		else if (inp.find("asleep") != string::npos) {
			int startOfNumber = inp.find(":") + 1;
			int endOfNumber = 2;
			fallAsleepTime = stoi(inp.substr(startOfNumber, endOfNumber));
		}
		else {
			int startOfNumber = inp.find(":") + 1;
			int endOfNumber = 2;
			int awakeTime = stoi(inp.substr(startOfNumber, endOfNumber));
			for (int i = fallAsleepTime; i < awakeTime; ++i) {
				guardSleep->at(guardID)->at(i)++;
				amountSleep->at(guardID)++;
				//cout << "Guard " << guardID << " Asleep " << guardSleep->at(guardID)->at(i) << " at: " << i << endl;
			}
		}
	}

	int mostSlept = 0;
	int mostTimeSlept = 0;
	for (int i = 0; i < 4000; ++i) {
		int guardSlept = amountSleep->at(i);
		if (mostTimeSlept < guardSlept) {
			mostSlept = i;
			mostTimeSlept = guardSlept;
		}
	}

	cout << "Guard " << mostSlept << " slept the most: ";

	int sleepyMinuteCount = 0;
	int sleepyMinute = 0;
	for (int j = 0; j < 60; ++j) {
		int minuteCount = guardSleep->at(mostSlept)->at(j);
		if (minuteCount > sleepyMinuteCount) {
			sleepyMinuteCount = minuteCount;
			sleepyMinute = j;
		}
	}
	cout << sleepyMinute << endl << "A: " << sleepyMinute * mostSlept << endl;

	int sleepyGuard = 0;
	sleepyMinute = 0;
	sleepyMinuteCount = 0;
	for (int i = 0; i < 4000; ++i) {
		for (int j = 0; j < 60; ++j) {
			int minuteCount = guardSleep->at(i)->at(j);
			if (minuteCount > sleepyMinuteCount) {
				//cout << sleepyGuard << endl << sleepyMinute << endl << endl;
				sleepyMinuteCount = minuteCount;
				sleepyGuard = i;
				sleepyMinute = j;
			}
		}
	}

	cout << "The winner is " << sleepyGuard << " at minute " << sleepyMinute << " having fallen asleep " << sleepyMinuteCount << " times!" << endl << "A: " << sleepyGuard * sleepyMinute << endl;
}