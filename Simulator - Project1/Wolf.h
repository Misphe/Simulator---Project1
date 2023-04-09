#pragma once
#include "Animal.h"
class Wolf : public Animal {
public:
	void Draw() override;
	Wolf(World& ref_world);
};

