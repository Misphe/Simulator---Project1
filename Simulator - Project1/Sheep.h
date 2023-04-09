#pragma once
#include "Animal.h"
class Sheep : public Animal {
public:
	void Draw() override;
	Sheep(World& ref_world);
};

