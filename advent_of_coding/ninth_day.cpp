#include "ninth_day.h"
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <array>


using namespace std;

struct marble {
	int number;
	marble* next;
	marble* previous;
};

struct score {
	int points;
	marble* current;
};

void printMarbleCircle(marble* current) {
	marble* looper = current;
	cout << looper->number << " ";
	looper = looper->next;
	while (looper != current) {
		cout << looper->number << " ";
		looper = looper->next;
	}
	cout << endl;
}

score* placeMarble(marble* current, marble* newMarble) {
	if (newMarble->number % 23 != 0) {
		marble* insertsNext = current->next->next;
		marble* insertsPrevious = current->next;

		newMarble->next = insertsNext;
		insertsNext->previous = newMarble;

		newMarble->previous = insertsPrevious;
		insertsPrevious->next = newMarble;

		//printMarbleCircle(newMarble);
		return new score{ 0,newMarble };
	}
	else {
		marble* remove = current->previous->previous->previous->previous->previous->previous->previous;

		remove->next->previous = remove->previous;
		remove->previous->next = remove->next;

		score* returnVal = new score{ remove->number + newMarble->number, remove->next };
		delete remove;
		delete newMarble;

		//printMarbleCircle(returnVal->current);
		return returnVal;
	}
}

void ninth_day_func() {

	const int PLAYERS = 405;//405;
	const int LAST_MARBLE = 7095300;//70953;
	const int HIGHSCORE = 8317;
	array <long long int, PLAYERS> scores;
	scores.fill(0);

	marble* currentMarble = new marble{ 0, nullptr, nullptr };
	currentMarble->next = currentMarble;
	currentMarble->previous = currentMarble;

	score* currentScore;
	currentScore = placeMarble(currentMarble, new marble{ 1 });

	currentMarble = currentScore->current;

	int currentPlayer = 1;

	int marbleValue = 2;
	//int highscore = 0;
	while (marbleValue <= LAST_MARBLE) {
		currentScore = placeMarble(currentMarble, new marble{ marbleValue });
		currentMarble = currentScore->current;


		marbleValue++;
		currentPlayer++;
		if (currentPlayer >= PLAYERS) {
			currentPlayer = 0;
		}
		scores[currentPlayer] += currentScore->points;


	}


	for (int i = 0; i < PLAYERS; ++i) {
		cout << "Player " << i << " got " << scores[i] << " points." << endl;
	}
	long long int highscore = 0;
	for (int i = 0; i < PLAYERS; ++i) {
		if (scores[i] > highscore) {
			highscore = scores[i];
		}
	}
	cout << "Highscore was: " << highscore << endl;
}