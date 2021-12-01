#include <iostream>

extern "C" long getHealth(void);
extern "C" long* getInventory(int n=0);


int main(){
	//std::cout << "player() returns: " << player() << "\nroom() returns: "<< room() << std::endl;
	
	
	std::cout << "Player health: " << getHealth() << std::endl;
	
	std::cout << "Inventory: " ;
	
	for(int i = 0; i < 5; ++i){
			std::cout << getInventory(i) << " | ";
	}
	
	std::cout << std::endl;
	
	
	return 0;
}
