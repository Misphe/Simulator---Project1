#pragma once
#include "Animal.h"
class Sheep : public Animal {
public:
	void Draw() const override;
	std::unique_ptr<Animal> Breed() const override;

	Sheep(World& ref_world);
	Sheep(World& ref_world, int set_x, int set_y);

	char GetSymbol() const override;
	std::string GetName() const override;
	int GetColor() const override;
};

