#pragma once
#include "Animal.h"
class Human : public Animal {
public:
	void Action() override;
	void Collision() override;
	void Draw() override;
	Human(World& ref_world);
};

