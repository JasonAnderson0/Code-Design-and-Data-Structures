#include <functional>

namespace HashTable {
	typedef std::function< unsigned int(const char*, unsigned int)> HashFunc;

	//do addition hash
	unsigned int badHash(const char* data, unsigned int length);
	//do function

	static HashFunc default = badHash;
}