#pragma once
#include "Animal.h"
class Wolf : public Animal {
public:
	void Draw() override;
	std::unique_ptr<Animal> Breed() const override;

	Wolf(World& ref_world);
};

