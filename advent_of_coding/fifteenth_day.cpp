#include "fifteenth_day.h"
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <array>

using namespace std;

enum Affinity{Elf, Goblin};

const int MAXHP = 200;
int rounds = 0;

struct Warrior {
	int x;
	size_t y;
	Affinity affinity;
	int hp;
	int atk;
};

struct warriorComparator {
	bool operator()( const Warrior* lhs, const Warrior* rhs) const {
		if (lhs->y == rhs->y)
			return lhs->x < rhs->x;
		else
			return lhs->y < rhs->y;
	}
};

struct Node {
	char type;
	Node*previous;
	int distance;
	const int x; 
	const size_t y;
	bool visited;
};

struct nodeComparator {
	bool operator()( const Node* lhs, const Node* rhs) const {
		if (lhs->distance == rhs->distance) {
			if (lhs->y == rhs->y) {
				return lhs->x < rhs->x;
			}
			else {
				return lhs->y < rhs->y;
			}
		}
		else {
			return lhs->distance < rhs->distance;

		}
	}
};


bool isEnd(Node* node, const set<Warrior*, warriorComparator>* end) {
	for (auto warrior : *end) {
		if (node->x == warrior->x && node->y == warrior->y)
			return true;
	}
	return false;
}

Node* pathfinder(const vector<vector<Node*>*>& map, Node* start, const set<Warrior*,warriorComparator>* end, set<Node*, nodeComparator>& queue) {
	if (isEnd(start, end)) {
		for (auto node : queue) {
			node->visited = false;
		}
		start->visited = false;
		return start;
	}
	else if (map.at(start->y)->at(start->x)->type == 'E' || map.at(start->y)->at(start->x)->type == 'G') {

	}
	else {
		int x = start->x - 1;
		int y = start->y;
		Node* neighbour = map.at(y)->at(x);

		char type = neighbour->type;
		bool visited = neighbour->visited;
		if (!visited && type != '#') {
			
			neighbour->visited = true;
			neighbour->previous = start;
			neighbour->distance = start->distance + 1;
			queue.insert(neighbour);
		}

		x = start->x + 1;
		y = start->y;
		
		neighbour = map.at(y)->at(x);
		type = neighbour->type;
		visited = neighbour->visited;
		if (!visited && type != '#') {
			
			neighbour->visited = true;
			neighbour->previous = start;
			neighbour->distance = start->distance + 1;
			queue.insert(neighbour);
		}

		x = start->x;
		y = start->y - 1;
		
		neighbour = map.at(y)->at(x);
		type = neighbour->type;
		visited = neighbour->visited;
		if (!visited && type != '#') {
			
			neighbour->visited = true;
			neighbour->previous = start;
			neighbour->distance = start->distance + 1;
			queue.insert(neighbour);
		}

		x = start->x;
		y = start->y + 1;
		
		neighbour = map.at(y)->at(x);
		type = neighbour->type;
		visited = neighbour->visited;
		if (!visited && type != '#') {
			
			neighbour->visited = true;
			neighbour->previous = start;
			neighbour->distance = start->distance + 1;
			queue.insert(neighbour);

		}
	}
	
	Node* retVal = nullptr;
	if (!queue.empty()) {
		Node* next = (*queue.begin());
		queue.erase(queue.begin());
		/*if (rounds = 23) {
			for (auto row : map) {
				for (auto node : *row) {
					cout << (node->visited ? '!' : node->type);
				}cout << endl;
			}
			system("pause");
		}*/
		retVal = pathfinder(map, next, end, queue);
		
	}
	start->visited = false;
	return retVal;

}

Node* findNextStep(set<Warrior*,warriorComparator>* enemy, Warrior* warrior, const vector<vector<Node*>*>& map) {
	set<Node*, nodeComparator> queue;

	Node* start = map.at(warrior->y)->at(warrior->x);
	start->visited = true;
	int x = start->x - 1;
	int y = start->y;
	Node* neighbour = map.at(y)->at(x);
	

	//setup first neighbours
	{
		char type = neighbour->type;
		bool visited = neighbour->visited;
		if (!visited && type != '#') {
			neighbour->visited = true;
			neighbour->previous = start;
			neighbour->distance = start->distance + 1;
			queue.insert(neighbour);
		}

		x = start->x + 1;
		y = start->y;
		neighbour = map.at(y)->at(x);
		type = neighbour->type;
		visited = neighbour->visited;
		if (!visited && type != '#') {
			neighbour->visited = true;
			neighbour->previous = start;
			neighbour->distance = start->distance + 1;
			queue.insert(neighbour);
		}

		x = start->x;
		y = start->y - 1;
		neighbour = map.at(y)->at(x);
		type = neighbour->type;
		visited = neighbour->visited;
		if (!visited && type != '#') {
			neighbour->visited = true;
			neighbour->previous = start;
			neighbour->distance = start->distance + 1;
			queue.insert(neighbour);
		}

		x = start->x;
		y = start->y + 1;
		neighbour = map.at(y)->at(x);
		type = neighbour->type;
		visited = neighbour->visited;
		if (!visited && type != '#') {
			neighbour->visited = true;
			neighbour->previous = start;
			neighbour->distance = start->distance + 1;
			queue.insert(neighbour);
		}
	}
	Node* next = *(queue.begin());
	queue.erase(queue.begin());
	Node* goal = pathfinder(map, next, enemy, queue);
	start->visited = false;

	Node* retVal = nullptr;
	if (goal) {
		retVal = goal;
		while (retVal->previous != start) {
			retVal = retVal->previous;
		}
		//cout << retVal->x << " " << backtrack->y << " " << endl;
	}
	return retVal;
}

Warrior* adjacentEnemy(Warrior* unit, set<Warrior*, warriorComparator >* enemies, vector<vector<Node*>*>& map) {
	int unitX = unit->x;
	int unitY = unit->y;
	int lowestHp = MAXHP +1;
	Warrior* closestEnemy = nullptr;


	for (auto enemy : *enemies) {
		if (unit->x == enemy->x  && unit->y -1 == enemy->y && enemy->hp < lowestHp && enemy->hp > 0) {
			lowestHp = enemy->hp;
			closestEnemy = enemy;
		}
		if (unit->x -1 == enemy->x  && unit->y == enemy->y && enemy->hp < lowestHp && enemy->hp > 0) {
			lowestHp = enemy->hp;
			closestEnemy = enemy;
		}
		if (unit->x + 1 == enemy->x  && unit->y == enemy->y && enemy->hp < lowestHp && enemy->hp > 0) {
			lowestHp = enemy->hp;
			closestEnemy = enemy;
		}
		if (unit->x == enemy->x  && unit->y + 1 == enemy->y && enemy->hp < lowestHp && enemy->hp > 0) {
			lowestHp = enemy->hp;
			closestEnemy = enemy;
		}
	}

	/*if (unit->x == 22 && unit->y == 5) {
		if (closestEnemy) {
			cout << "closest to retarded elf" << closestEnemy->x << " " << closestEnemy->y << endl;
		}
		else
			cout << "retarded elf doesnt have closest enemy...\n";
		if (rounds == 34) {
			cout << "Enemy to retarded elf: ";
			for (auto enemy : *enemies) {
				cout << enemy->x << " " << enemy->y << " : ";
			}cout << endl;
		}
	}*/
	return closestEnemy;
}

void takeTurn(Warrior* unit, set<Warrior*, warriorComparator>* enemies, vector<vector<Node*>*>& map) {
	if (!adjacentEnemy(unit, enemies, map)) {
		Node* nextStep = findNextStep(enemies, unit, map);
		if (nextStep) {
			map.at(unit->y)->at(unit->x)->type = '.';
			unit->x = nextStep->x;
			unit->y = nextStep->y;
			nextStep->type = (unit->affinity == Elf ? 'E':'G');
		}
	}
	Warrior* closestEnemy = adjacentEnemy(unit, enemies, map);

	if (closestEnemy) {
		closestEnemy->hp -= unit->atk;
		//cout << "Dealt dmg: " << unit->atk << " hp left: " << closestEnemy->hp << endl;
		if (closestEnemy->hp <= 0) {
			//cout << "Killed enemy, hp left: " << closestEnemy->hp << endl;
			//cout << "Enemies left before kill: " << enemies->size() << endl;
			for (auto enemy : *enemies) {
				if (enemy->hp >= 0) {
					enemies->erase(enemy);
					break;
				}
			}
			
			map.at(closestEnemy->y)->at(closestEnemy->x)->type = '.';
			
			//enemies->erase(closestEnemy);
			//cout << "Enemies left after kill: " << enemies->size();
			//cout << endl;
			//cout << "Erasing: " << closestEnemy->x << " " << closestEnemy->y << endl;

		}
	}
}

void printmap(vector<vector<Node*>*> map, set<Warrior*, warriorComparator>* warriors, set<Warrior*, warriorComparator>* elfs, set<Warrior*, warriorComparator>* goblins) {
	for (auto row : map) {
		for (auto node : *row) {
			cout << node->type;

		}

		for (auto node : *row) {
			for (auto warrior : *warriors) {
				if (warrior->x == node->x && warrior->y == node->y) {
					cout << (warrior->affinity == Elf ? "E " : "G ") << warrior->hp << " ";
				}
			}
		}
		cout << endl;

	}
	cout << "warriors: " << warriors->size() << " Elfs: " << elfs->size() << " Goblins: " << goblins->size() << endl;

	system("pause");
}

void fifteenth_day_func() {
	ifstream myfile;
	
	int testCase = 0;

	//There was a weird case with movement for one elf at atkpwr ==17 or 19 where it moved away from goblins.. a goblin had recently died close by, so might be a problem there.

	string input;

	vector<vector<Node*>*> map;
	set<Warrior*,warriorComparator>* goblins;
	set<Warrior*, warriorComparator>* elfs;
	set<Warrior*, warriorComparator>* warriors;
	
	int survivingElfs = 0;
	int startingElfs = -1;

	int elvesAtk = 1;
	if (testCase == 0)
		elvesAtk = 15;

	while (survivingElfs != startingElfs) {

		goblins = new set<Warrior*, warriorComparator>;
		elfs = new set<Warrior*, warriorComparator>;
		warriors = new set<Warrior*, warriorComparator>;

		if (testCase == 0)
			myfile.open("fifteenth_day_input.txt");
		else if (testCase == 1)
			myfile.open("fifteenth_test_1.txt");
		else if (testCase == 2)
			myfile.open("fifteenth_test_2.txt");
		else if (testCase == 3)
			myfile.open("fifteenth_test_3.txt");
		else if (testCase == 4)
			myfile.open("fifteenth_test_4.txt");
		else if (testCase == 5)
			myfile.open("fifteenth_test_5.txt");
		else if (testCase == 6)
			myfile.open("fifteenth_test_6.txt");
		
		const int GOBLIN_ATK = 3;

		while (getline(myfile, input)) {
			vector<Node*>* row = new vector<Node*>;
			for (int x = 0; x < input.size(); ++x) {
				char c = input[x];

				if (c == 'E') {
					Warrior* elf = new Warrior{ x, map.size(), Affinity::Elf, MAXHP,elvesAtk };
					elfs->insert(elf);
					warriors->insert(elf);
				}
				else if (c == 'G') {
					Warrior* goblin = new Warrior{ x, map.size(), Affinity::Goblin, MAXHP, GOBLIN_ATK };
					goblins->insert(goblin);
					warriors->insert(goblin);
				}
				row->push_back(new Node{ c, nullptr, 0, x, map.size(), false });
			}
			map.push_back(row);
			cout << input << endl;
		}
		startingElfs = elfs->size();
		cout << "Elfs from the start: " << startingElfs << endl;

		for (auto warrior : *warriors) {
			cout << (warrior->affinity == Elf ? "Elf    " : "Goblin ") << warrior->x << (warrior->x < 10 ? "  " : " ") << warrior->y << endl;
		}
		for (auto elf : *elfs) {
			cout << elf->y << " " << elf->x << endl;
		}

		while (!elfs->empty() && !goblins->empty()) {

			for (auto warrior : *warriors) {
				if (warrior->hp > 0) {
					set<Warrior*, warriorComparator>* enemies = (warrior->affinity == Elf ? goblins : elfs);
					takeTurn(warrior, enemies, map);

				}
				//printmap(map, warriors, elfs, goblins);

			}
			/*for (auto it = warriors->begin(); it != warriors->end(); ++it) {
				if ((*it)->hp <= 0) {
					warriors->erase(it);
					break;
				}
			}*/




			/*cout << "elfs size before moving: " << elfs->size();
			set<Warrior*, warriorComparator>*temp = new set<Warrior*, warriorComparator>;
			for (auto warrior : *elfs) {
				temp->insert(warrior);
			}
			delete elfs;
			elfs = temp;
			cout << " after moving: " << elfs->size() << endl;


			cout << "goblins size before moving: " << goblins->size();
			temp = new set<Warrior*, warriorComparator>;
			for (auto warrior : *goblins) {
				temp->insert(warrior);
			}
			delete goblins;
			goblins = temp;
			cout << " after moving: " << goblins->size() << endl;*/
			//cout << "goblins size before moving: " << goblins->size() << endl;
			//cout << "elfs size before moving: " << elfs->size() << endl;
			//cout << "warriors size before moving: " << warriors->size() << endl;
			set<Warrior*, warriorComparator>* goblinTemp = new set<Warrior*, warriorComparator>;
			set<Warrior*, warriorComparator>* elfTemp = new set<Warrior*, warriorComparator>;
			set<Warrior*, warriorComparator>* temp = new set<Warrior*, warriorComparator>;
			for (auto warrior : *warriors) {
				if (warrior->hp > 0) {
					temp->insert(warrior);
					if (warrior->affinity == Elf)
						elfTemp->insert(warrior);
					if (warrior->affinity == Goblin)
						goblinTemp->insert(warrior);
				}
			}
			delete warriors;
			delete elfs;
			delete goblins;
			goblins = goblinTemp;
			elfs = elfTemp;
			warriors = temp;

			//cout << "warriors after moving: " << warriors->size() << endl;
			//cout << "elfs after moving: " << elfs->size() << endl;
			//cout << "goblins after moving: " << goblins->size() << endl;
			rounds++;

			printmap(map, warriors, elfs, goblins);

		}
		int hpLeft = 0;
		for (auto warrior : *warriors) {
			hpLeft += warrior->hp;
		}

		cout << "Elfs left: " << elfs->size() << " Goblins left: " << goblins->size() << " Warriors left: " << warriors->size() << endl;
		cout << "Elfs dmg " << elvesAtk << " Rounds: " << rounds << " Total HP left: " << hpLeft << " Answer (=(rounds - 1)*hpLeft): " << hpLeft * (rounds - 1) << endl;
		rounds = 0;
		
		
		survivingElfs = elfs->size();
		delete warriors;
		delete elfs;
		delete goblins;
		elvesAtk++;
		myfile.close();
		system("pause");
	}
	//48790 too low
	//53000 too low
	//2088212 too high lol
}