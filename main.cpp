#include <iostream>
//#include "player.asm"

extern "C" long player(long = 0);
//extern "C" int room();

int main(){
	//std::cout << "player() returns: " << player() << "\nroom() returns: "<< room() << std::endl;
	
	
	std::cout << "Player health: " << player(1) << std::endl;
	
	//std::cout << "inventory ptr: " << player(2) << std::endl;
	
	return 0;
}
