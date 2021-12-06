#include <iostream>
using std::cout;
using std::endl;

extern "C" long getHealth(void);
extern "C" int inventoryPtr[];
extern "C" int attack(int);


int main(){
	
	cout << "Player health: " << getHealth() << std::endl;
	
	for(int i = 0; i< 5; ++i){
			inventoryPtr[i] = i+1;
	}
	
	std::cout << "Inventory: " ;
	
	for(int i = 0; i < 5; ++i){
			cout << inventoryPtr[i];
			cout << " | ";
	}
	
	cout << std::endl;
	
	cout << "Player attack enemy. Enemy health remaining: " << attack(0) << endl;
	
	return 0;
}
