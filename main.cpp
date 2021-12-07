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
extern "C" long enemyHealth(void);
extern "C" long receiveItem(long);

void printItems(long n);
void printInventory(void);
void newEnemy(void);
long numGen(void);
void prompt(int n);
void dropItem(void);

int main(){
	
	prompt(1);
	cout << "ReceiveItem returns: " << receiveItem(2) << endl;
	printInventory();
	
	return 0;
}


void printInventory(){
	cout << "Inventory: " ;
	
	for(long i = 0; i < 5; ++i){
			printItems(inventoryPtr[i]);
			cout << " | ";
	}
	
	cout <<endl;
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

void newEnemy(){
	long n = numGen();
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

void prompt(int n){
	switch (n){
	case 1:
		cout << "Player health: " << getHealth() << endl;
		break;
	}
}

