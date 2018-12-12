#include "eight_day.h"

#include <iostream>
#include <vector>

void eight_day_func() {

	ifstream *myfile = new ifstream;
	myfile->open("eight_day_input.txt");

	cout << endl << "Metadata total is: " << treeHandlingWithIndex(myfile) << endl;

}

int treeHandling(ifstream* input) {
	int children;
	int metadataEntries;
	int sum = 0;
	if (*input >> children) {
		cout << children << " ";
		*input >> metadataEntries;
		cout << metadataEntries << " ";
		if (children > 0) {
			for (int i = 0; i < children; ++i) {
				sum += treeHandling(input);
			}
		}
		for (int i = 0; i < metadataEntries; ++i) {
			int metadata;
			*input >> metadata;
			cout << metadata << " ";
			sum += metadata;
		}
		return sum;
	}
	return 0;
}
int treeHandlingWithIndex(ifstream* input) {
	int children;
	int metadataEntries;
	int sum = 0;

	if (*input >> children) {

		*input >> metadataEntries;
		vector<int> childValues;
		if (children > 0) {
			for (int i = 0; i < children; ++i) {
				childValues.push_back(treeHandlingWithIndex(input));
			}
			for (int i = 0; i < metadataEntries; ++i) {
				int metadata;
				*input >> metadata;
				if (metadata > 0) {
					metadata--;
					if (metadata < childValues.size()) {
						sum += childValues[metadata];
					}
				}
			}
		}
		else {
			for (int i = 0; i < metadataEntries; ++i) {
				int metadata;
				*input >> metadata;
				sum += metadata;
			}
		}
		cout << sum << " ";
		return sum;
	}
	return 0;
}
