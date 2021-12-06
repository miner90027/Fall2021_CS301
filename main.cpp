#include <iostream>
using std::cout;
using std::endl;

extern "C" long getHealth(void);
extern "C" long playerPtr[];
extern "C" int inventoryPtr[];
extern "C" int attack(int);
extern "C" int useItem(int);


void printInventory(){
	std::cout << "Inventory: " ;
	
	for(int i = 0; i < 5; ++i){
			cout << inventoryPtr[i];
			cout << " | ";
	}
	
	cout << std::endl;
}

int main(){
	
	cout << "Player health: " << getHealth() << std::endl;
	
	for(int i = 0; i< 5; ++i){
			inventoryPtr[i] = i+1;
	}

	printInventory();
	
	cout << "Please enter the slot number 0 - 4 for the item you wish to use: " << endl;
	
	int in;
	std::cin >> in;
	
	
	cout << "Using item in slot " << in << " returns: " << useItem(in) << endl;
	cout << "Item in slot" << in << ": " << inventoryPtr[in] << endl;
	
	printInventory();
	
	cout << "Player attack enemy. Enemy health remaining: " << attack(0) << endl;
	
	return 0;
}
