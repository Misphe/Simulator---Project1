#pragma once
#include "Animal.h"
class Turtle : public Animal {
private:
	void Action() override;
	int DefenseResult(Organism& attacker) override;

public:
	void Draw() const override;
	std::unique_ptr<Animal> Breed() const override;

	Turtle(World& ref_world);
	Turtle(World& ref_world, int set_x, int set_y);


	char GetSymbol() const override;
	std::string GetName() const override;
	int GetColor() const override;
};

