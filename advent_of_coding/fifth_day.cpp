#include "fifth_day.h"
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <iostream>
#include <set>
#include <map>

using namespace std;

bool reactingPolymer(char a, char b) {
	if (islower(a)) {
		return toupper(a) == b;
	}
	else {
		return tolower(a) == b;
	}
}

void fifth_day_func() {
	ifstream myfile;
	string input;
	myfile.open("fifth_day_input.txt");
	myfile >> input;
	array<char, 50000>* output = new array<char, 50000>;
	output->fill('\0');

	
	set<char> polymers;
	for (char c : input) {
		polymers.insert(tolower(c));
	}

	map<char, int> length;

	for (char c : polymers) {
		cout << c << endl;
		int outputPointer{ 0 };
		int inputPointer{ 0 };
		while (tolower(input[inputPointer]) == c) {
			inputPointer++;
		}
		output->at(outputPointer) = input[inputPointer];
		inputPointer++;

		while (inputPointer < input.size()) {
			while (tolower(input[inputPointer]) == c) {
				inputPointer++;
			}
			char inp = input[inputPointer];
			char outp = output->at(outputPointer);
			bool reacting = reactingPolymer(inp, outp);
			if (reacting) {
				output->at(outputPointer) = '\0';
				outputPointer--;
			}
			else {
				outputPointer++;
				output->at(outputPointer) = inp;
			}
			inputPointer++;

			//In case there's no element left in the output, we need to forcibly input one thing to have something to react with
			if (outputPointer == -1) {
				outputPointer++;
				while (tolower(input[inputPointer]) == c) {
					inputPointer++;
				}
				output->at(outputPointer) = input[inputPointer];
				inputPointer++;
			}
			/*if (inputPointer % 1000 == 0) {
				cout << inp << " " << outp << " " << inputPointer << endl;

				for (char c : *output)
					if (c != '\0')
						cout << c;
				cout << endl;
				system("pause");
			}*/

		}
		int counter = 0;
		for (char c : *output) {
			if (c != '\0') {

				//cout << c;
				counter++;
			}
		}
		length.insert(pair<char, int>(c, counter));
		int i = 0;
		for (i = 0; output->at(i) != '\0'; ++i) {
			if (reactingPolymer(output->at(i), output->at(i + 1))) {
				cout << "REACTS";
				system("pause");
			}
		}
		cout << endl << i << " " << counter << " " << input.size() << endl;
	}
	
	
}