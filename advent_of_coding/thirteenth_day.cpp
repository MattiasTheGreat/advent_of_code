#include "thirteenth_day.h"

using namespace std;


bool cartComparator::operator()(
	const tuple<int, int, Turn, Direction, Crashed, Rail>* lhs,
	const tuple<int, int, Turn, Direction, Crashed, Rail>* rhs) const{

	if (get<1>(*lhs) == get<1>(*rhs))
	return get<0>(*lhs) < get<0>(*rhs);
	else
	return get<1>(*lhs) < get<1>(*rhs);
}

char cartCurrentRail(vector<string*>& map, int x, int y) {
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
				return '+';
				//map.at(y)->at(x) = '+';
			else
				return '|';
				//map.at(y)->at(x) = '|';
		else if (right == '-' || right == '+' || right == '\\' || right == '/')
			return '\\';
			//map.at(y)->at(x) = '\\';
		else
			return '/';
			//map.at(y)->at(x) = '/';
	else
		return '-';
		//map.at(y)->at(x) = '-';
}



set<tuple<int, int, Turn, Direction, Crashed, Rail>*, struct cartComparator>* findCarts(vector<string*>& map) {
	set<tuple<int, int, Turn, Direction, Crashed, Rail>*, struct cartComparator>* retVal = new set<tuple<int, int, Turn, Direction, Crashed, Rail>*, struct cartComparator>;
	for (int y = 0; y < map.size(); ++y) {
		string* row = map.at(y);
		for (int x = 0; x < row->size(); ++x) {
			if (row->at(x) == '^') {
				//cout << "^" << endl;
				
				retVal->insert(new tuple<int, int, Turn, Direction, Crashed, Rail>{ x, y, -1, 0, false, cartCurrentRail(map, x, y) });
			}
			if (row->at(x) == '>') {
				//cout << ">" << endl;
				retVal->insert(new tuple<int, int, Turn, Direction, Crashed, Rail>{ x, y, -1, 1, false, cartCurrentRail(map, x, y) });
			}
			if (row->at(x) == 'v') {
				//cout << "v" << endl;
				retVal->insert(new tuple<int, int, Turn, Direction, Crashed, Rail>{ x, y, -1, 2, false, cartCurrentRail(map, x, y) });
			}
			if (row->at(x) == '<') {
				//cout << "<" << endl;
				retVal->insert(new tuple<int, int, Turn, Direction, Crashed, Rail>{ x, y, -1, 3, false, cartCurrentRail(map, x, y) });
			}


		}
	}

	return retVal;
}

vector<pair<int, int>*>* tick(set<tuple<int, int, Turn, Direction, Crashed, Rail>*,struct cartComparator>* carts, vector<string*>& map) {
	vector<pair< int, int>*>* collisions = new vector<pair< int, int>*>;

	for (auto cart : (*carts)) {
		auto& cartX = get<0>(*cart);
		auto& cartY = get<1>(*cart);
		Turn& turn = get<2>(*cart);
		Direction& dir = get<3>(*cart);
		Crashed& crashed = get<4>(*cart);
		Rail& currentRail = get<5>(*cart);
				
		map.at(cartY)->at(cartX) = currentRail;
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

		currentRail = map.at(cartY)->at(cartX);
		
		if (currentRail == '^' || currentRail == '>' || currentRail == 'v' || currentRail == '<') {
			crashed = true;
			collisions->push_back(new pair< int, int>{cartX,cartY });
			for (auto crasher : (*carts))
				if (get<0>(*crasher) == cartX && get<1>(*crasher) == cartY) {
					get<4>(*crasher) = true;
					//cout << "pausing cart at:" << cartX << "," << cartY << endl;
				}
		}
		else {
			if (currentRail == '+') {
				dir += turn;
				if (dir > 3)
					dir = 0;
				else if (dir < 0)
					dir = 3;
				turn++;
				if (turn == 2)
					turn = -1;
			}
			else if (currentRail == '\\') {
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
			else if (currentRail == '/') {
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
			if (dir == 0)
				map.at(cartY)->at(cartX) = '^';
			else if (dir == 1)
				map.at(cartY)->at(cartX) = '>';
			else if (dir == 2)
				map.at(cartY)->at(cartX) = 'v';
			else if (dir == 3)
				map.at(cartY)->at(cartX) = '<';
		}	
	}

	//cout << endl;

	// Replace rail where carts have crashed
	for (auto cart : *carts) {
		int cartX = get<0>(*cart);
		int cartY = get<1>(*cart);
		char currentRail = get<5>(*cart);
		if (get<4>(*cart) && currentRail != '^' && currentRail != '>' && currentRail != 'v' && currentRail != '<') { //Only the cart that got to crash location first has the underlying rail stored
			map.at(cartY)->at(cartX) = get<5>(*cart);
			cout << "replacing cart at" << cartX << " " << cartY << " with " << currentRail << endl;
		}
	}


	return collisions;
}

void thirteenth_day_func() {
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

	for (auto m : map) {
		cout << '|' << endl;
	}system("pause");

	/*for (auto m : map) {
		cout << *m << endl;
	}system("pause");*/

	set<tuple<int, int, Turn, Direction, Crashed, Rail>*,struct cartComparator>* carts = findCarts(map);
	cout << carts->size() << endl;;

	vector<pair< int, int>*>* collisions;
	int counter = 0;
	while (carts->size()>1) {

		collisions = tick(carts, map);
		counter++;
		cout << counter << endl;
		if (!collisions->empty()) {
			auto temp = new set<tuple<int, int, Turn, Direction, Crashed, Rail>*, struct cartComparator>;
			for (auto cart : (*carts))
				if (!get<4>(*cart))
					temp->insert(cart);
			delete carts;
			carts = temp;
			for (auto collision : (*collisions)) {
				cout << "Collision at: " << collision->first << ", " << collision->second << ". Carts remaining: " << carts->size() << endl;
			}
			system("pause");
		}
		/*for (auto m : map) {
			cout << *m << endl;
		}system("pause");*/

	}

	for (auto cart : (*carts)) {
		cout << get<0>(*cart) << " " << get<1>(*cart) << endl;
	}
}