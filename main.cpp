#include <iostream>

extern "C" int player();
extern "C" int room();

int main(){

	std::cout << "player() returns: " << player() 
							<< "\nroom() returns: "<< room() << std::endl;
	return 0;
}
