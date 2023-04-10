#pragma once
#include "Animal.h"
class Sheep : public Animal {
public:
	void Draw() override;
	std::unique_ptr<Animal> Breed() const override;

	Sheep(World& ref_world);
};

