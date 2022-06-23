#include "HashTable.h"
#include <iostream>


int main() {
	Hashtable<int, std::string> texture(20);

	std::string flumph = "gluntch";
	std::cout << texture[flumph];
} 