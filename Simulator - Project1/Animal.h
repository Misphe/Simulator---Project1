#pragma once
#include "Organism.h"

class Animal : public Organism {
public:
	virtual void Action() override;
	virtual void Collision() override;
	virtual void Draw() override = 0;
	Animal(World& ref_world) : Organism(ref_world) {}
};

