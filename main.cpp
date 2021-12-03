#include <iostream>

extern "C" long getHealth(void);
extern "C" long* getInventory(int);
extern "C" void setInventory(int, int);


int main(){
	
	std::cout << "Player health: " << getHealth() << std::endl;
	
	for(int i = 0; i< 5; ++i){
			setInventory(i,i);
	}
	
	std::cout << "Inventory: " ;
	
	for(int i = 0; i < 5; ++i){
			std::cout << getInventory(i) << " | ";
	}
	
	std::cout << std::endl;
	
	
	return 0;
}
