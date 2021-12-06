#include <iostream>
#include <cstdlib>
#include <ctime>
using std::cout;
using std::endl;


extern "C" long getHealth(void);
extern "C" long inventoryPtr[];
extern "C" long attack(long);
extern "C" long useItem(long);
extern "C" void resetEnemy(long, long);
extern "C" long enemyPtr[];

void printItems(long n);
void printInventory(void);
void newEnemy(long n);
long numGen(void);

int main(){
	
	cout << "Player health: " << getHealth() << std::endl;
	
	for(int i = 0; i< 5; ++i){
			inventoryPtr[i] = i;
	}

	printInventory();
	/*
	cout << "Please enter the slot number 0 - 4 for the item you wish to use: " << endl;
	
	long in;
	std::cin >> in;
	
	
	cout << "Using item in slot " << in << " returns: " << useItem(in) << endl;
	cout << "Item in slot" << in << ": ";
	printItems(inventoryPtr[in]);
	cout << endl;
	
	printInventory();
	
	cout << "Player attack enemy. Enemy health remaining: " << attack(0) << endl;
	
	
	//cout << "Generating random num between 0 - 4: " << dropItem() << endl;
	*/
	newEnemy(4);
	cout << "Enemy stats:\nHealth: "<< enemyPtr[0]<< "\nAttack: " << enemyPtr[1] << endl;
	
	return 0;
}


void printInventory(){
	std::cout << "Inventory: " ;
	
	for(long i = 0; i < 5; ++i){
			printItems(inventoryPtr[i]);
			cout << " | ";
	}
	
	cout << std::endl;
}

long numGen(){
	std::srand(std::time(nullptr)); 
	
	long randNum = std::rand()/((RAND_MAX + 1u)/4);
	
	return randNum;
}

void printItems(long n){
	switch (n) {
	case 1:
		cout << "Potion";
		break;
	case 2:
		cout << "Sword";
		break;
	case 3:
		cout << "Dagger";
		break;
	case 4:
		cout << "Bottle";
		break;
	default:
		cout << "Nothing";
		break;
	}
}

void newEnemy(long n){
	switch (n) {
	case 1:
		cout << "A slime appears!" << endl;
		resetEnemy(50,1);
		break;
	case 2:
		cout << "A goblin appears!" << endl;
		resetEnemy(100,10);
		break;
	case 3:
		cout << "An Orc appears!" << endl;
		resetEnemy(150,25);
		break;
	default:
		cout << "No enemyies appear." << endl;
		break;
	}
}
