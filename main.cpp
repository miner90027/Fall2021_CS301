#include <iostream>
#include <cstdio>
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
	
	for(int i = 0; i < 5; ++i){
		inventoryPtr[i] = 4;
	}
	
	printInventory();
	cout << endl;
	dropItem();
	cout << endl;
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

void dropItem(){
	long item = numGen();
	cout << "The enemy dropped ";
	
	if(item < 1 || item > 4){
		printItems(item);
		cout << endl;
		return;
	}
	
	cout << "a ";
	printItems(item); 
	cout << "!" << endl;
	
	char keep;
	
	do{
		cout << "Would you like to keep the ";
		printItems(item);
		cout << "? (Y/N)" << endl;
		keep = std::getchar();
		
	}while(keep != 'y' && keep != 'Y' && 
					keep != 'n' && keep != 'N');
					
	if(keep == 'n' || keep == 'N') return;
	
	long full = receiveItem(item);
	if(full != -1) return;
	
	keep = '\0';
	
	do{
		printInventory();
		cout << endl << endl << "You don't have enough room to keep the ";
		printItems(item);
		cout << ".\nDo you wish to replace an item in your inentory? (Y/N)" << endl;
		keep = std::getchar();
		
	}while(keep != 'y' && keep != 'Y' && 
					keep != 'n' && keep != 'N');
	
	if(keep == 'n' || keep == 'N') return;
	
	long slot = -2;
	do{
	cout << "Which item do you wish to replace?\nPlease enter the number for the slot containing the item, or enter -1 to cancel." << endl;
	printInventory();
	cout << "\tSlot 0 | Slot 1| Slot 2 | Slot 3 | Slot 4 |" << endl;
	std::cin >> slot;
	
	}while(slot < -1 && slot >= 5);
	
	inventoryPtr[slot] = 0;
	receiveItem(item);
}

















