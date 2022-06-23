#pragma once
class GameObject
{
public:
	GameObject();
	~GameObject();

	void SetData(int data) { m_data = data; }
	int GetData() { return m_data; }

private:

	int m_data;
};

