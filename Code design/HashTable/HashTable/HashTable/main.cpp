#include "HashTable.h"
#include <iostream>


int main() {
	Hashtable<std::string, int> texture(20);

	std::string flumph = "gluntch";
	std::cout << texture[flumph];
} 