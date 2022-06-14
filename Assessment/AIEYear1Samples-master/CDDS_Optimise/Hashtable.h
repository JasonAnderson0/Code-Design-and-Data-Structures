#pragma once

template<typename KeyType, typename T>
class Hashtable
{
public:
	Hashtable(unsigned int size) : m_size(size), m_data(new T[size]) {}

	~Hashtable() { delete[] m_data; }

	T& operator [](const KeyType& key) {
		auto hashedKey = hash(key) % m_size;
		return m_data[hashedKey];
	}

	const T& operator [] (const KeyType& key) const {
		auto hashedKey = hash(key) % m_size;
		return m_data[hashedKey];
	}

private:
	unsigned int hashFunction(const KeyType& key);

	T* m_data;
	unsigned int m_size;
};

