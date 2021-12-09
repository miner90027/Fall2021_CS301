#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <chrono>
#include <thread>
using std::cout;
using std::endl;


extern "C" long getHealth(void);
extern "C" long inventoryPtr[];
extern "C" long attack(long);
extern "C" long useItem(long);
extern "C" void resetEnemy(long, long, long);
extern "C" long enemyHealth(void);
extern "C" long receiveItem(long);
extern "C" long score(void);
extern "C" void gainXP(void);

void printItems(long n);
void printInventory(void);
void newEnemy(void);
long numGen(void);
void prompt(int n);
void dropItem(void);
long action(void);
long getLong(void);

int main(){
	
	receiveItem(numGen());
	
	do{
		//std::this_thread::sleep_for (std::chrono::seconds(2));
		std::system("clear");
		prompt(1);
		printInventory();
		cout << endl;
		
		if(enemyHealth() <= 0) 
			newEnemy();
		
		prompt(2);
		cout << endl << endl;
		
		switch (action()){
			case 1:
			{
				cout << endl << endl;
				
				long slot = -2;
				do{
				cout << "Which item do you wish to use?\n"
				"Please enter the number for the slot containing the item, or enter -1 to cancel." << endl;
				printInventory();
				cout << "\tSlot 0 | Slot 1| Slot 2 | Slot 3 | Slot 4 |" << endl;
				slot = getLong();
				
				}	while(!(slot >= -1 && slot < 5));
				if(slot == -1) {
					cout << "No items were used" << endl;
					continue;
				}
				
				cout << "You used the ";
				printItems(inventoryPtr[slot]);
				cout << "." << endl;
				
				useItem(slot);
				
				if(enemyHealth() <= 0) continue;
				break;
				}
			case 2:
			
				if(enemyHealth() <= 0){
					cout << "You encountered no enemies to attack. You continue on your way." << endl;
					break;
				}

				cout << "You attack the enemy dealing " << attack(0) << " damage." << endl;
				if(enemyHealth() <= 0){
					cout << "You defeated the enemy!" << endl;
					gainXP();
					cout << endl;
					dropItem();
				}

				break;
			default:
				if(enemyHealth() <= 0){
					cout << "Nothing eventful happens as you continue your journey." << endl;
				}
				else{
					cout << "You recognize that you are not equiped to defeat the enemy before you.\n"
								"You decide to flee and live to fight another day." << endl;
				}
				resetEnemy(0,0,0);
				
				continue;
		}
		
		if(enemyHealth() > 0){
			cout << endl << "The enemy attacks you! You take "<< attack(1) << " damage!" << endl;
		}
		
		std::this_thread::sleep_for (std::chrono::seconds(2));
	}while(getHealth() > 0);
	
	std::system("clear");
	prompt(1);
	cout << "\n\n\t\t\tYou Died!\n\t\t\tGame Over" << endl;
	
	cout << "\n\n\n\t\t\tScore: " << score() << endl;
	
	return 0;
}

long action(){
	long act = -1;
	
	do{
			cout << "What action would you like to take?\n"
							"Enter the number associated with the action you wish to take.\n"
							"0: Run Away / Continue Journey\n1: Use an Item or Equip Weapon\n2: Attack" << endl;
			act = getLong();
	}while (!(act >= 0 && act < 3));

	return act;
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
		resetEnemy(50,1, 50);
		break;
	case 2:
		cout << "A goblin appears!" << endl;
		resetEnemy(100,10, 100);
		break;
	case 3:
		cout << "An Orc appears!" << endl;
		resetEnemy(150,25, 300);
		break;
	default:
		cout << "No enemyies appear." << endl;
		resetEnemy(0,0,0);
		break;
	}
}

void prompt(int n){
	switch (n){
	case 1:
		cout << "Player Health: " << getHealth() << endl;
		break;
	case 2:
		cout << "Enemy Health: " << enemyHealth() << endl;
		break;
	}
}

void dropItem(){
	long item = numGen();
	cout << "You found ";
	
	if(item < 1 || item > 4){
		printItems(item);
		cout << endl;
		return;
	}
	
	cout << "a ";
	printItems(item); 
	cout << "!" << endl;
	
	char keep = '\0';
	
	while(keep != 'y' && keep != 'Y' && 
					keep != 'n' && keep != 'N'){
		cout << "Would you like to keep the ";
		printItems(item);
		cout << "? (Y/N)" << endl;
		keep = std::getchar();
	}
					
	if(keep == 'n' || keep == 'N') return;
	
	long full = receiveItem(item);
	if(full != -1) return;
	
	keep = '\0';
	
	while(keep != 'y' && keep != 'Y' && 
					keep != 'n' && keep != 'N'){
		printInventory();
		cout << endl << endl << "You don't have enough room to keep the ";
		printItems(item);
		cout << ".\nDo you wish to replace an item in your inentory? (Y/N)" << endl;
		keep = std::getchar();
		
	}
	
	if(keep == 'n' || keep == 'N') return;
	
	long slot = -2;
	while(slot < -1 && slot >= 5){
		cout << "Which item do you wish to replace?\n"
			"Please enter the number for the slot containing the item, or enter -1 to cancel." << endl;
		printInventory();
		cout << "\tSlot 0 | Slot 1| Slot 2 | Slot 3 | Slot 4 |" << endl;
		slot = getLong();
	
	}
	
	inventoryPtr[slot] = 0;
	receiveItem(item);
}


// Take from Stack Overflow & modified for longs
// https://stackoverflow.com/questions/9455501/c-getint-function-have-a-java-equivalent-attached
long getLong(){

	long i;
	while (!(std::cin >> i)) {
			cout << "Invalid input. Please enter a number." << endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<long>::max(), '\n');
	}

	return i;
}








