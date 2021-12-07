#include <iostream>
#include <string>
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
extern "C" long & enemyHealth(void);
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

int main(){
	
	receiveItem(numGen());
	
	do{
		std::this_thread::sleep_for (std::chrono::seconds(2));
		std::system("clear");
		prompt(1);
		printInventory();
		cout << endl;
		
		if(enemyHealth() <= 0) 
			newEnemy();
		
		prompt(2);
		cout << endl << endl;
		
		switch (action()){
			case 0:
				enemyHealth() = 0;
				break;
			case 1:
			{
				cout << endl << endl;
				
				long slot = -2;
				do{
				cout << "Which item do you wish to use?\n"
				"Please enter the number for the slot containing the item, or enter -1 to cancel." << endl;
				printInventory();
				cout << "\tSlot 0 | Slot 1| Slot 2 | Slot 3 | Slot 4 |" << endl;
				std::cin >> slot;
				
				}while(slot < -1 && slot >= 5);
				if(slot == -1) continue;
				
				useItem(slot);
				
				cout << "You used the ";
				printItems(inventoryPtr[slot]);
				cout << "." << endl;
				
				if(enemyHealth() <= 0) continue;
				break;
				}
			case 2:
				cout << "You attack the enemy dealing " << attack(0) << " damage." << endl;
				if(enemyHealth() <= 0){
					cout << "You defeated the enemy!" << endl;
					gainXP();
				}
				break;
			default:
				if(enemyHealth < 0){
					enemyHealth() = 0;
				}
				continue;
		}
		
		if(enemyHealth() > 0){
			cout << endl << "The enemy attacks you! You take "<< attack(1) << " damage!" << endl;
			//attack(1);
		}
		else{
		cout << endl;
			dropItem();
		}
		
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
			std::cin >> act;
	}while (act < 0 && act >= 3);

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










