#pragma once

template <typename T>
class ObjectPool
{
public:
	ObjectPool(unsigned int size) : m_size(size), m_data(new T[size]) {}
	~ObjectPool() { delete[] m_data; }

private:
	unsigned int m_size = 0;
	T* m_data = nullptr;
	bool* 


};

