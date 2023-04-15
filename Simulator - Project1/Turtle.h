#pragma once
#include "Animal.h"
class Turtle : public Animal {
public:
	void Draw() const override;
	std::unique_ptr<Animal> Breed() const override;

	Turtle(World& ref_world);
	Turtle(World& ref_world, int set_x, int set_y);

	void Action() override;
	int DefenseResult(Organism& attacker) override;

	char GetSymbol() const override;
	std::string GetName() const override;
};

