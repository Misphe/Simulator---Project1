#pragma once
#include "Animal.h"
class Wolf : public Animal {
public:
	void Draw() const override;
	std::unique_ptr<Animal> Breed() const override;

	Wolf(World& ref_world);
	Wolf(World& ref_world, int set_x, int set_y);

	char GetSymbol() const override;
};

