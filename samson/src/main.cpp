
// Project SAMSON 
// Author: Scott Sullivan
// A robotic project
// Hardware: ATSAMD21G18A

#include <iostream>;

//#define LOG(x) std::cout << x << std::endl;

int main() 
{
	// input from user
	int var = 8;
	void* ptr = &var;

	std::cout << var << std::endl;
	std::cout << ptr << std::endl;
	
	std::cin.get();

}