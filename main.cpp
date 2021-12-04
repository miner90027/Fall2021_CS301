#include <iostream>
using std::cout;

extern "C" long getHealth(void);
extern "C" int inventoryPtr[];


int main(){
	
	cout << "Player health: " << getHealth() << std::endl;
	
	for(int i = 0; i< 5; ++i){
			inventoryPtr[i] = i;
	}
	
	std::cout << "Inventory: " ;
	
	for(int i = 0; i < 5; ++i){
			cout << inventoryPtr[i];
			cout << " | ";
	}
	
	cout << std::endl;
	
	
	return 0;
}
