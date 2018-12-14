#include "thirteenth_day.h"

using namespace std;

/*

bool cartComparator::operator()(const tuple<int, int, Turn, Direction, Updated>* lhs, const tuple<int, int, Turn, Direction, Updated>* rhs) const {
	if (get<1>(*lhs) == get<1>(*rhs))
		return get<0>(*lhs) < get<0>(*rhs);
	else
		return get<1>(*lhs) < get<1>(*rhs);

}

void replaceCart(vector<string*>& map, int x, int y) {
	char up, right, down, left;

	if (x == 0)
		left = map.at(y)->at(x);
	else
		left = map.at(y)->at(x - 1);

	if (x == map.at(y)->size() - 1)
		right = map.at(y)->at(x);
	else
		right = map.at(y)->at(x + 1);

	if (y == 0)
		up = map.at(y)->at(x);
	else
		up = map.at(y - 1)->at(x);

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

set<tuple<int, int, Turn, Direction, Updated>*, cartComparator>* findCarts(vector<string*>& map) {
	set<tuple<int, int, Turn, Direction, Updated>*, cartComparator>* retVal = new set<tuple<int, int, Turn, Direction, Updated>*, cartComparator>;
	for (int y = 0; y < map.size(); ++y) {
		string* row = map.at(y);
		for (int x = 0; x < row->size(); ++x) {
			if (row->at(x) == '^') {
				//cout << "^" << endl;
				replaceCart(map, x, y);
				retVal->insert(new tuple<int, int, Turn, Direction, Updated>{ x, y, -1, 0, false });
			}
			if (row->at(x) == '>') {
				//cout << ">" << endl;
				replaceCart(map, x, y);
				retVal->insert(new tuple<int, int, Turn, Direction, Updated>{ x, y, -1, 1, false });
			}
			if (row->at(x) == 'v') {
				//cout << "v" << endl;
				replaceCart(map, x, y);
				retVal->insert(new tuple<int, int, Turn, Direction, Updated>{ x, y, -1, 2, false });
			}
			if (row->at(x) == '<') {
				//cout << "<" << endl;
				replaceCart(map, x, y);
				retVal->insert(new tuple<int, int, Turn, Direction, Updated>{ x, y, -1, 3, false });
			}


		}
	}

	return retVal;
}

bool isCollision(set<tuple<int, int, Turn, Direction, Updated>*, cartComparator>* carts, int x, int y) {
	int overlap = 0;
	for (auto it = carts->begin(); it != carts->end(); it++) {
		auto& cartX = get<0>(*(*it));
		auto& cartY = get<1>(*(*it));
		if (cartX == x && cartY == y) {
			overlap++;
			if (overlap == 2)
				return true;
		}

	}
	return false;
}

vector<tuple<Collision, int, int>*>* tick(set<tuple<int, int, Turn, Direction, Updated>*, cartComparator>* carts, vector<string*> map) {
	vector<tuple<Collision, int, int>*>* collisions = new vector<tuple<Collision, int, int>*>;
	for (int y = 0; y < map.size(); ++y) {
		string row = *map.at(y);
		for (int x = 0; x < row.size(); ++x) {
			for (auto cart : (*carts)) {
				auto& cartX = get<0>(*cart);
				auto& cartY = get<1>(*cart);
				Turn& turn = get<2>(*cart);
				Direction& dir = get<3>(*cart);
				Updated& updated = get<4>(*cart);
				if (cartX == x && cartY == y && !updated) {
					updated = true;
					//cout << "x was " << cartX << " and y was " << cartY << endl;
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
					char rail = map.at(cartY)->at(cartX);
					//cout << "x is " << cartX << " and y is " << cartY << endl;
					if (isCollision(carts, cartX, cartY)) {
						cout << "COLLISION\n";
						collisions->push_back(new tuple<Collision, int, int>{ true,cartX,cartY });
						for (auto crasher : (*carts))
							if (get<0>(*crasher) == cartX && get<1>(*crasher) == cartY) {
								get<4>(*crasher) = true;
								cout << "pausing cart at:" << cartX << "," << cartY << endl;
							}
					}
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
							cout << "Something went terribly wrong in a \\ turn" << endl;
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
							cout << "Something went terribly wrong in a / turn" << endl;
					}

				}
			}
		}
	}
	for (auto cart : (*carts))
		get<4>(*cart) = false;
	//cout << endl;


	return collisions;
}

void fourteenth_day_func() {
	ifstream myfile;
	int test = 0;
	if (test == 0)
		myfile.open("thirteenth_day_input.txt");
	else if (test == 1)
		myfile.open("thirteenth_test_1.txt");
	else if (test == 2)
		myfile.open("thirteenth_test_2.txt");
	else
		myfile.open("thirteenth_test_3.txt");
	string input;

	vector<string*> map;
	while (getline(myfile, input)) {
		map.push_back(new string{ input });
	}


	set<tuple<int, int, Turn, Direction, Updated>*, cartComparator>* carts = findCarts(map);
	cout << carts->size() << endl;;

	vector<tuple<Collision, int, int>*>* collisions;
	int counter = 0;
	while (carts->size()>1) {

		collisions = tick(carts, map);
		counter++;
		cout << counter << endl;
		if (!collisions->empty()) {
			auto temp = new set<tuple<int, int, Turn, Direction, Updated>*, cartComparator>;
			for (auto collision : (*collisions)) {
				for (auto it = carts->rbegin(); it != carts->rend(); ++it) {
					if (get<1>(*collision) == get<0>(*(*it)) && get<2>(*collision) == get<1>(*(*it))) {
						tuple<int, int, Turn, Direction, Updated>* test = *it;
						get<4>(*(*it)) = true;
					}
				}
			}
			for (auto cart : (*carts))
				if (!get<4>(*cart))
					temp->insert(cart);
			delete carts;
			carts = temp;
			for (auto collision : (*collisions)) {
				if (get<0>(*collision)) {
					cout << "Collision at: " << get<1>(*collision) << ", " << get<2>(*collision) << ". Carts remaining: " << carts->size() << endl;

				}
			}
			system("pause");
		}

	}

	for (auto cart : (*carts)) {
		cout << get<0>(*cart) << " " << get<1>(*cart) << endl;
	}
}*/