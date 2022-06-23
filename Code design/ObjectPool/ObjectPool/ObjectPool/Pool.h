#pragma once
#include <vector>
template <typename T>
class Pool
{
public:
	Pool(unsigned int size) : m_size(size), m_data(new T[size])
	{
		for (int i = 0; i < size; i++)
		{
			inactive.push_back(m_data[i]);
			m_data[i].SetData(i);
		}
	}
	~Pool() { delete[] m_data; }

	void move(T object);

	std::vector<T> GetActive() { return active; }
	std::vector<T> GetInActive() { return inactive; }
	T GetIndex(int i) { return m_data[i]; }

private:
	unsigned int m_size;
	T* m_data = nullptr;
	std::vector<T> active;
	std::vector<T> inactive;
};

template<typename T>
inline void Pool<T>::move(T object)
{
	std::swap(object ,inactive.back());
	//T thing = inactive.back();
	inactive.pop_back();
	active.push_back(object);
}
