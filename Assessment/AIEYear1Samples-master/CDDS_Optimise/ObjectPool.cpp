#include "ObjectPool.h"
#include "raylib.h"
#include "ResourceManager.h"

ObjectPool::ObjectPool(const int size): m_size(size)
{
	for (int i = 0; i < size; i++) {
		inactive.push_back(critterPool[i]);
	}

}

Critter* ObjectPool::spawn()
{
	if (inactive.size() > 0) {
		auto critter = inactive.back();
		inactive.pop_back();
		active.push_back(critter);
		return &critter;
	}
	return nullptr;
}

void ObjectPool::despawn(Critter& moved)
{

}
