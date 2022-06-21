#pragma once
#include <vector>
#include "Critter.h"

class ObjectPool {
public:
	ObjectPool(const int size);

	Critter* GetPool(int value) { return &critterPool[value]; }
	std::vector<Critter> GetActive() { return active; }
	std::vector<Critter> GetInactive() { return inactive; }

	Critter* spawn();
	void despawn(Critter& mover);


private:
	std::vector<Critter> inactive;
	std::vector<Critter> active;
	const int m_size;
	Critter* critterPool = new Critter[m_size];

};
